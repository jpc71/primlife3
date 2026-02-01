/*
 * Primordial Life 4.0 - Registration Key Generator
 * 
 * This program generates valid registration keys for Primordial Life 4.0
 * based on the user's name and desired license type.
 *
 * Key Format (32-bit):
 * - Bits 0-15: Checksum derived from user's name
 * - Bit 16: Temporary license flag (0x00010000)
 * - Bit 17: Work and Home license flag (0x00020000)
 * - Bit 18: Site license flag (0x00040000)
 * - Bits 19-31: Validation bits
 *
 * Validation Algorithm:
 * 1. Name-based checksum must equal 0xFADE after processing
 * 2. Additional validation: (((key & 0x0007FFFF) * 3) / 5) << 19) & 0xFFF80000
 *    must equal (key & 0xFFF80000) for IsValid() to pass
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstdint>
#include <ctime>

using namespace std;

// License type flags
const uint32_t FLAG_TEMPORARY     = 0x00010000;  // 15-day temporary license
const uint32_t FLAG_WORK_AND_HOME = 0x00020000;  // Work and home license
const uint32_t FLAG_SITE_LICENSE  = 0x00040000;  // Site license

// Calculate the checksum for a given name
uint16_t CalculateNameChecksum(const string& name) {
    string upperName = name;
    // Convert to uppercase
    transform(upperName.begin(), upperName.end(), upperName.begin(), ::toupper);
    
    uint16_t result = 0xFADE;  // Target value
    int length = upperName.length();
    
    // Reverse the algorithm: we need to find what to ADD to get 0xFADE
    // Original: result -= (((WORD)sName[i]) << ((i + 3) % 7));
    // So we ADD back to get the starting value
    for (int i = 0; i < length; i++) {
        result += (((uint16_t)upperName[i]) << ((i + 3) % 7));
    }
    
    return result;
}

// Generate validation bits for the upper part of the key
// Based on: ((((key & 0x0007FFFF) * 3) / 5) << 19) & 0xFFF80000 == (key & 0xFFF80000)
uint32_t CalculateValidationBits(uint32_t lowerBits) {
    // Extract lower 19 bits
    uint32_t value = lowerBits & 0x0007FFFF;
    
    // Calculate what should be in the upper bits
    uint32_t upperBits = ((value * 3) / 5) << 19;
    
    return upperBits & 0xFFF80000;
}

// Generate a complete registration key
uint32_t GenerateKey(const string& name, uint32_t flags = 0) {
    if (name.length() < 3) {
        cerr << "Error: Name must be at least 3 characters long" << endl;
        return 0;
    }
    
    // Calculate the name-based checksum
    uint16_t checksum = CalculateNameChecksum(name);
    
    // Start with the checksum in the lower 16 bits
    uint32_t key = checksum;
    
    // Add the license type flags
    key |= flags;
    
    // Calculate and add validation bits
    uint32_t validationBits = CalculateValidationBits(key);
    key = (key & 0x0007FFFF) | validationBits;
    
    return key;
}

// Format key as hex string
string FormatKey(uint32_t key) {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%08X", key);
    return string(buffer);
}

// Display the menu
void DisplayMenu() {
    cout << "\n============================================" << endl;
    cout << " Primordial Life 4.0 - Key Generator" << endl;
    cout << "============================================" << endl;
    cout << "\nLicense Types:" << endl;
    cout << "  1. Standard License" << endl;
    cout << "  2. Temporary License (15 days)" << endl;
    cout << "  3. Work and Home License" << endl;
    cout << "  4. Site License" << endl;
    cout << "  5. Site + Work and Home" << endl;
    cout << "  0. Exit" << endl;
    cout << "\n============================================" << endl;
}

int main() {
    string name;
    int choice;
    
    cout << "Primordial Life 4.0 Registration Key Generator" << endl;
    cout << "===============================================\n" << endl;
    
    // Get user name
    cout << "Enter the registration name (3+ characters): ";
    getline(cin, name);
    
    // Trim whitespace
    size_t start = name.find_first_not_of(" \t\r\n");
    size_t end = name.find_last_not_of(" \t\r\n");
    if (start != string::npos && end != string::npos) {
        name = name.substr(start, end - start + 1);
    }
    
    if (name.length() < 3) {
        cerr << "Error: Name must be at least 3 characters long!" << endl;
        return 1;
    }
    
    while (true) {
        DisplayMenu();
        cout << "Select license type: ";
        cin >> choice;
        
        if (choice == 0) {
            cout << "\nThank you for using the key generator!" << endl;
            break;
        }
        
        uint32_t flags = 0;
        string licenseType;
        
        switch (choice) {
            case 1:
                flags = 0;
                licenseType = "Standard License";
                break;
            case 2:
                flags = FLAG_TEMPORARY;
                licenseType = "Temporary License (15 days)";
                break;
            case 3:
                flags = FLAG_WORK_AND_HOME;
                licenseType = "Work and Home License";
                break;
            case 4:
                flags = FLAG_SITE_LICENSE;
                licenseType = "Site License";
                break;
            case 5:
                flags = FLAG_SITE_LICENSE | FLAG_WORK_AND_HOME;
                licenseType = "Site + Work and Home License";
                break;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
                continue;
        }
        
        // Generate the key
        uint32_t key = GenerateKey(name, flags);
        
        if (key != 0) {
            cout << "\n--------------------------------------------" << endl;
            cout << "Registration Information:" << endl;
            cout << "--------------------------------------------" << endl;
            cout << "Name:         " << name << endl;
            cout << "License Type: " << licenseType << endl;
            cout << "Key:          " << FormatKey(key) << endl;
            cout << "--------------------------------------------" << endl;
            
            // Verify the key
            string upperName = name;
            transform(upperName.begin(), upperName.end(), upperName.begin(), ::toupper);
            uint16_t verify = (uint16_t)key;
            for (int i = 0; i < (int)upperName.length(); i++) {
                verify -= (((uint16_t)upperName[i]) << ((i + 3) % 7));
            }
            
            if (verify == 0xFADE && upperName.length() > 2) {
                cout << "Verification: PASSED ✓" << endl;
            } else {
                cout << "Verification: FAILED ✗" << endl;
            }
            cout << "--------------------------------------------\n" << endl;
        }
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    return 0;
}
