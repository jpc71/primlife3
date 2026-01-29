# Primordial Life - Windows 11 Modernization Guide

## Overview
This document tracks the modernization of Primordial Life from Visual Studio 6.0 (1998) to work on modern Windows 11 systems.

## Target Environment
- **OS**: Windows 10/11 (64-bit)
- **IDE**: Visual Studio 2022 Community Edition or later
- **Platform Toolset**: v143 (VS2022)
- **SDK**: Windows 10/11 SDK
- **MFC**: Modern MFC (dynamically linked for ease of deployment)

## Key Changes Required

### 1. Project Structure ✅ IN PROGRESS
- [ ] Create new Visual Studio 2022 solution (.sln)
- [ ] Create new project file (.vcxproj) to replace .dsp
- [ ] Update include paths and library dependencies
- [ ] Add x64 platform configuration (in addition to Win32)

### 2. Windows API Compatibility
- [ ] Add Windows version targeting (#define WINVER, _WIN32_WINNT)
- [ ] Update deprecated registry APIs if needed
- [ ] Check for 16-bit API usage (should be minimal in this codebase)
- [ ] Verify GDI and multimedia API compatibility

### 3. 64-bit Compatibility Issues
**Critical**: The codebase uses Hungarian notation extensively with potential 32/64-bit issues:
- [ ] Review all DWORD usage for pointer-sized values (should be DWORD_PTR)
- [ ] Check LONG usage for pointer arithmetic (should be LONG_PTR)
- [ ] Verify int/pointer casts in Environment::Skip(), Biot collision detection
- [ ] Check serialization code for size assumptions

### 4. Winsock Modernization
- [ ] Update from Winsock 1.1 to Winsock 2.2 APIs
- [ ] Replace dynamic loading of Winsock with static linking
- [ ] Update Sock.h and Sock.cpp for modern socket APIs
- [ ] Test networking features (world-to-world connections)

### 5. Compiler Compliance
Modern C++ compilers are stricter:
- [ ] Fix narrowing conversions (int to BYTE, etc.)
- [ ] Add explicit casts where needed
- [ ] Fix any const-correctness issues
- [ ] Update deprecated CRT functions (_s variants)
- [ ] Remove or update precompiled header dependencies

### 6. MFC Updates
- [ ] Switch from statically linked MFC to dynamic linking
- [ ] Update AfxMessageBox and other MFC calls if signatures changed
- [ ] Verify CArchive serialization compatibility
- [ ] Test Document/View architecture on modern MFC

### 7. Build System
- [ ] Remove zlib dependency or update to modern version
- [ ] Remove/replace TeeChart dependency (very old ActiveX control)
- [ ] Update output directories (Build, Bin folders)

### 8. DPI Awareness & Modern Windows Features
- [ ] Add application manifest for DPI awareness
- [ ] Set DPI awareness in project properties
- [ ] Test on high-DPI displays
- [ ] Update any hard-coded pixel sizes

## Known Dependencies to Address

### External Libraries
1. **zlib** - Referenced in project but may not be needed for core functionality
2. **TeeChart** - Graphing ActiveX control from 1990s, likely needs replacement
3. **Winsock** - Replace dynamic loading with modern static linking

### Deprecated APIs
- Registry functions - Should still work but verify
- Multimedia timer functions - May need updates
- Screen saver APIs - Verify compatibility

## Build Instructions (After Modernization)

### Prerequisites
1. Install Visual Studio 2022 Community Edition
2. Install "Desktop development with C++" workload
3. Install "MFC and ATL support" component

### Building
1. Open `Life\PrimordialLife.sln` in Visual Studio 2022
2. Select configuration (Debug/Release) and platform (x64 recommended)
3. Build → Build Solution (Ctrl+Shift+B)
4. Output: `Bin\x64\Release\Primordial Life.exe`

### Running
- Double-click executable to run simulation
- Command line options still supported (see original documentation)
- Screen saver mode: Copy to `C:\Windows\System32` with `.scr` extension

## Testing Checklist
- [ ] Application launches without crashes
- [ ] Simulation starts and runs (OnIdle loop)
- [ ] Biots appear and move correctly
- [ ] Collision detection works (spatial optimization)
- [ ] File open/save (serialization)
- [ ] Mouse operations (examine, feed, terminate, etc.)
- [ ] Keyboard shortcuts work
- [ ] Statistics window displays correctly
- [ ] Magnify window works
- [ ] Networking features (if preserved)
- [ ] Screen saver mode (if preserved)
- [ ] Registry settings load/save
- [ ] Sound events play

## Potential Gotchas

1. **Spatial Optimization**: BRectSort system with four sorted arrays is performance-critical
2. **Idle Loop**: Simulation depends on MFC OnIdle() - verify modern MFC calls it appropriately
3. **Bitmap Caching**: Biots cache their bitmaps - memory usage on 64-bit may differ
4. **Random Number Generator**: Uses custom Randomizer class - verify algorithm still works
5. **Neural Networks**: ProductTerm/ProductSum logic may have precision differences
6. **Serialization**: CArchive format compatibility between 32-bit and 64-bit

## Phase 1 Priority (Minimum Viable Build)
1. ✅ Create VS2022 project files
2. Add Windows 11 targeting
3. Fix critical 64-bit issues
4. Get Release/x64 build working
5. Test basic simulation functionality

## Phase 2 (Full Modernization)
1. Update all deprecated APIs
2. Modernize Winsock networking
3. Add DPI awareness
4. Replace TeeChart if needed
5. Full x64 testing
6. Performance optimization

## Phase 3 (Polish)
1. Modern installer
2. Updated documentation
3. GitHub Actions CI/CD
4. Unicode support (currently MBCS)
5. Code cleanup and modernization
