# Primordial Life

*An experiment in computer-based evolution*

Primordial Life is an artificial life simulation where autonomous creatures called "biots" evolve through genetic algorithms. Each biot has a visual morphology defined by genetic segments, a neural network brain for behavior control, and physical properties that determine how it interacts with its environment and other biots.

![License](https://img.shields.io/badge/license-AGPL%20v3+-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows%2010%2F11-lightgrey.svg)
![C++](https://img.shields.io/badge/language-C%2B%2B-orange.svg)

## Overview

Watch as populations of digital organisms compete for resources, reproduce, and evolve over generations in a continuous simulation. Biots display emergent behaviors through their neural networks, develop distinct species, and adapt to their environment through mutation and natural selection.

**Key Features:**
- Autonomous creatures with genetic morphology (up to 80 body segments)
- Neural network brains using product-term logic
- Real-time evolution with mutation and sexual/asexual reproduction
- Spatial optimization for efficient collision detection
- Population statistics and visualization tools
- Save/load simulations and individual biots
- Network capabilities for connecting multiple simulation worlds

## Quick Start

### Prerequisites
- **OS**: Windows 10 or Windows 11 (64-bit)
- **IDE**: Visual Studio 2022 or later (with C++ desktop development and MFC support)
- **SDK**: Windows 10/11 SDK

### Building

1. Open `Life\PrimordialLife.sln` in Visual Studio 2022
2. Select **Release** configuration and **x64** platform
3. Build → Build Solution (Ctrl+Shift+B)
4. Executable will be in `Bin\x64\Release\Primordial Life.exe`

### Running

Simply double-click the executable to start the simulation. On first run, you'll be prompted to configure the initial environment size and population.

**Basic Controls:**
- **Ctrl+M**: Start/stop simulation
- **Ctrl+N**: Create new simulation
- **Ctrl+S**: Save current simulation
- **F11**: Optimal window size
- **F12**: Full screen mode
- **Number keys 1-8**: Biot interaction tools (cure, examine, feed, mutate, etc.)

## Project Status

This is a modernization of the original Primordial Life 4.0 (1996-1998) for modern Windows systems. The core simulation engine and architecture remain faithful to the original design.

**Recent Improvements:**
- Rendering fixes for modern Windows (see [program-fixes.md](program-fixes.md))
- Updated for Windows 10/11 compatibility
- Modernization in progress (see [MODERNIZATION.md](MODERNIZATION.md))

## Architecture

Primordial Life is built using the Microsoft Foundation Classes (MFC) framework with a Document/View architecture:

- **Environment**: Central simulation engine managing the world space, resource distribution, and biot lifecycle
- **Biot**: Individual creatures with genetic segments, neural networks, and physical properties
- **BRectSort**: Spatial indexing system for efficient collision detection
- **Brain**: Neural network implementation using product terms and sum-of-products logic
- **Genotype**: Genetic information defining biot morphology, colors, and segment structure

For technical implementation details and recent bug fixes, see [program-fixes.md](program-fixes.md).

For modernization progress and compatibility notes, see [MODERNIZATION.md](MODERNIZATION.md).

## Documentation

- **[program-fixes.md](program-fixes.md)** - Technical documentation of recent rendering fixes
- **[MODERNIZATION.md](MODERNIZATION.md)** - Guide for updating the codebase to modern Windows
- **[.github/copilot-instructions.md](.github/copilot-instructions.md)** - Project architecture reference
- **Help/** - Original help files (HTML format)

## Usage Examples

### Creating a New Simulation
1. Launch Primordial Life
2. Select environment size (use entire screen, maximized window, or custom)
3. Configure initial population (default: 20 biots)
4. Set genetic parameters (arm types, segments per arm)
5. Click OK to start the simulation

### Interacting with Biots
Press the number keys to select interaction modes:
- **1**: Cure/Sicken a biot
- **2**: Examine biot statistics
- **3**: Feed a biot (increase energy)
- **4**: Mutate a biot's genetics
- **5**: Load a saved biot into the environment
- **6**: Relocate a biot
- **7**: Save a biot to a file
- **8**: Terminate a biot

Click on a biot while in the selected mode to perform the action.

### Viewing Statistics
- **View → Environmental Statistics**: Population graphs, age distribution, energy levels
- **Examination tool (key 2)**: Detailed info about individual biots (genetics, energy, lineage)

## Contributing

Contributions are welcome! Since this project is licensed under the GNU Affero General Public License v3 or later, any contributions must also be compatible with this license.

**Areas for Contribution:**
- Completing the Windows 11 modernization (see MODERNIZATION.md)
- Bug fixes and performance improvements
- Documentation improvements
- Cross-platform support (Linux, macOS via compatible frameworks)
- Enhanced visualization features
- Network protocol updates

Please ensure code follows the existing conventions (see .github/copilot-instructions.md for architecture details).

## Copyright and License

**Primordial Life** - an experiment in computer based evolution.

Copyright (C) 1996-1998 Jason Spofford <spofford@io.com>

This program is free software: you can redistribute it and/or modify it under the terms of the **GNU Affero General Public License** as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but **WITHOUT ANY WARRANTY**; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

**Full license text**: See [COPYING](COPYING) file.

### License Notice

The GNU Affero General Public License (AGPL) is a copyleft license that requires anyone who modifies and uses this software on a network server to make the complete source code available to users of that server. This ensures that improvements to the software benefit the entire community.

## Credits

**Original Author**: Jason Spofford (1996-1998)
- Email: spofford@io.com
- Original artificial life simulation design and implementation

**Current Maintainer**: jondo
- Repository: primlife
- Modernization for Windows 10/11

## References

- **Original Release**: Primordial Life 4.0 (1998)
- **Technology**: C++ with Microsoft Foundation Classes (MFC)
- **Architecture**: Document/View with idle-time processing loop
- **License**: GNU Affero General Public License v3+
- **Website**: <http://www.gnu.org/licenses/> (license information)

## History

Primordial Life was originally developed in 1996-1998 as an exploration of artificial life and evolutionary algorithms. The simulation demonstrates emergent behaviors from simple rules:

- Biots have colored segments with different properties (green for energy collection, red for attack, blue for defense)
- Sexual and asexual reproduction with genetic crossover and mutation
- Energy-based lifecycle (biots must "eat" to survive and reproduce)
- Emergent species formation through genetic isolation
- Complex behaviors from neural network brains

The current version maintains the original simulation engine while modernizing the codebase for contemporary Windows systems.

---

**Note**: This is an active modernization project. Some features may not yet work on modern systems. Check [MODERNIZATION.md](MODERNIZATION.md) for current status and known issues.
