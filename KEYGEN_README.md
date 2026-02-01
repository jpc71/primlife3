# Primordial Life 4.0 - Registration Key Generator

This is a command-line utility that generates valid registration keys for Primordial Life 4.0.

## Features

- Generate keys for different license types:
  - Standard License
  - Temporary License (15-day trial)
  - Work and Home License
  - Site License
  - Combined Site + Work and Home License

- Automatic verification of generated keys
- Simple interactive menu interface

## Building

### Using g++ (MinGW/MSYS2 on Windows)

```bash
g++ -std=c++11 -O2 -o keygen.exe keygen.cpp
```

### Using MSVC (Visual Studio)

```bash
cl /EHsc /O2 keygen.cpp
```

### Using the Makefile

```bash
make
```

## Usage

Run the executable:

```bash
./keygen.exe
```

Or on Windows:

```bash
keygen.exe
```

### Example Session

```
Primordial Life 4.0 Registration Key Generator
===============================================

Enter the registration name (3+ characters): John Smith

============================================
 Primordial Life 4.0 - Key Generator
============================================

License Types:
  1. Standard License
  2. Temporary License (15 days)
  3. Work and Home License
  4. Site License
  5. Site + Work and Home
  0. Exit

============================================
Select license type: 4

--------------------------------------------
Registration Information:
--------------------------------------------
Name:         John Smith
License Type: Site License
Key:          12345678
--------------------------------------------
Verification: PASSED ✓
--------------------------------------------
```

## How It Works

The key generator implements the same validation algorithm used by Primordial Life:

1. **Name-based Checksum**: A 16-bit checksum is calculated from the user's name (case-insensitive)
2. **License Flags**: Specific bits indicate the license type:
   - Bit 16 (0x00010000): Temporary license
   - Bit 17 (0x00020000): Work and Home license
   - Bit 18 (0x00040000): Site license
3. **Validation Bits**: Upper bits are calculated to pass the `IsValid()` check

The algorithm ensures that when the key is validated:
- The name checksum equals `0xFADE`
- Additional validation equations are satisfied

## Technical Details

### Key Format (32-bit)

```
Bits 31-19: Validation bits
Bit 18:     Site License flag
Bit 17:     Work and Home flag
Bit 16:     Temporary flag
Bits 15-0:  Name checksum
```

### Validation Algorithm

```cpp
// Name checksum must equal 0xFADE after processing
uint16_t result = keyLower16Bits;
for (int i = 0; i < name.length(); i++)
    result -= (((uint16_t)upperName[i]) << ((i + 3) % 7));
// result must equal 0xFADE

// Additional validation
(((key & 0x0007FFFF) * 3) / 5) << 19) & 0xFFF80000 == (key & 0xFFF80000)
```

## License Types Explained

- **Standard License**: Basic registration, single computer
- **Temporary License**: 15-day trial period, requires timestamp validation
- **Work and Home License**: Can be used on two computers (work and home)
- **Site License**: Can be used on multiple computers within an organization
- **Combined**: Site license with work and home privileges

## Notes

- Generated keys are compatible with Primordial Life 4.0
- Name must be at least 3 characters long
- Keys are case-insensitive
- Temporary keys require a timestamp to be set on first use

## Disclaimer

This tool is provided for educational and archival purposes for the Primordial Life software, which is now open source under the GNU Affero General Public License v3+.
