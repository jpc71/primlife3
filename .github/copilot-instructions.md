# Primordial Life - Copilot Instructions

## Project Overview
Primordial Life is a Windows MFC application implementing an artificial life simulation where autonomous creatures ("biots") evolve through genetic algorithms. The simulation runs continuously with biots competing for resources, reproducing, and evolving over generations.

## Architecture

### Core Components
- **Environment** ([Environ.h](../Life/Source/Environ.h), [Environ.cpp](../Life/Source/Environ.cpp)): Central simulation engine managing the world space, resource distribution, and biot lifecycle. Inherits from `BRect` and `Randomizer`.
- **Biot** ([Biots.h](../Life/Source/Biots.h), [Biots.cpp](../Life/Source/Biots.cpp)): Individual creatures with visual morphology defined by genetic segments, neural network brains, and physical properties. Inherits from `BRectItem`.
- **Brain** ([Brain.h](../Life/Source/Brain.h)): Neural network implementation using product terms and sum-of-products logic for behavior control.
- **Genotype** ([Genotype.h](../Life/Source/Genotype.h)): Genetic information defining biot morphology, colors, segment structure (up to `MAX_SEGMENTS` per line, `MAX_SYMMETRY` lines).

### Document/View Architecture
- **CPLifeApp** ([Primordial Life.cpp](../Life/Source/Primordial Life.cpp)): Main application class managing registry, sound events, and initialization.
- **CPLifeDoc** ([PLifeDoc.h](../Life/Source/PLifeDoc.h)): Document class holding the `Environment` instance.
- **View Classes**: `CPLifeView` (normal), `CSaverView` (screensaver), `CSmallView` (compact) - all inherit from `CGeneralView`.
- **CMainFrame** ([MainFrm.h](../Life/Source/MainFrm.h)): Main window managing status bar, cursors, and user interactions.

### Simulation Loop
The simulation uses MFC's idle processing model:
1. `CPLifeApp::OnIdle()` calls active view's `OnIdle()` method
2. View's `OnIdle()` calls `Environment::Skip()` when `m_bStarted` is true
3. `Skip()` iterates through all biots in `m_biotList` using `NextBiot()`
4. Each biot processes movement, collision detection, energy consumption, reproduction, and death

### Spatial Optimization
- **BRectSort** ([Etools.h](../Life/Source/Etools.h)): Spatial indexing system with four sorted arrays (left, right, top, bottom) for efficient collision detection.
- **BRectItem**: Base class for spatial objects with bounding rectangles.
- Biots call `MoveBiot()` to update spatial indices when position changes.

## Key Patterns

### Naming Conventions
- Member variables use Hungarian notation: `m_` prefix (e.g., `m_biotList`, `m_hMemoryDC`)
- Pointers use `p` prefix: `pBiot`, `pDC`, `pView`
- Static class members use `s_` prefix: `s_pMainFrame`
- Booleans use `b` prefix: `bNetworkSettingsChange`, `m_bStarted`
- Handles use `h` prefix: `m_hMemPadDC`, `m_hBitPad`

### Global Access Helpers
Use inline helper functions instead of direct access:
- `AfxGetPLife()` - Access CPLifeApp instance
- `AfxMainFrame()` - Access CMainFrame (via `CMainFrame::s_pMainFrame`)
- `AfxKeyRegistry()` / `AfxUserRegistry()` - User settings registry
- `AfxCommonRegistry()` - Machine-wide settings registry

### Registry & Settings
- User settings: `HKEY_CURRENT_USER\Software\Ultravast\Primordial Life\4`
- Machine settings: `HKEY_LOCAL_MACHINE\Software\Ultravast\Primordial Life\4`
- Use `CKeyRegistry` wrapper class, not raw Win32 registry APIs
- Settings are in `CSettings options` member of Environment

### Sound Events
- System sounds registered in `InitInstance()` with prefix `PL.` (e.g., `PL.Birth`, `PL.Extinction`)
- Played via `Environment::PlayResource()`
- Default location: `%WINDIR%\Media\Primordial Life\`

### Memory Management
- Biots allocated with `new`, owned by `CBiotList` in Environment
- Call `FreeAll()` on CBiotList to delete all biots
- Off-screen drawing uses scratch pad DC: `GetBitPadDC()` / `FreeBitPadDC()`
- Bitmaps cached per biot: `FreeBitmaps()` cleans up

## Building & Debugging

### Build System
- Visual Studio 6.0 project files: [Primordial Life.dsw](../Life/Make/Primordial Life.dsw), [.dsp](../Life/Make/Primordial Life.dsp)
- MFC application with precompiled headers via [StdAfx.h](../Life/Source/StdAfx.h)
- Resources in [Primordial Life.rc](../Life/Source/Primordial Life.rc), custom resources in [RES/](../Life/RES/) folder

### Dependencies
- MFC (Microsoft Foundation Classes) - statically linked
- TeeChart for graphing ([TEE/TeeChartDefines.h](../Life/TEE/TeeChartDefines.h))
- Windows Multimedia (`mmsystem.h`) for sound
- Winsock for networking features ([Sock.h](../Life/Source/Sock.h), [Connect.h](../Life/Source/Connect.h))

### Common Tasks
- **Start simulation**: Set `m_bStarted = true` in view, idle loop handles rest
- **Add new biot**: Call `Environment::AddBiot()`, automatically added to spatial index
- **Access current biot in iteration**: Use `CBiotList::NextBiot()` with `Looped()` check
- **Modify genetics**: Edit `Genotype` class, rebuild biot bitmaps with `FormBitmap()`

## Statistics & Monitoring
- `CEnvStats` samples every `SAMPLE_TIME` (512 generations)
- Tracked metrics: births, deaths, population, extinctions, age distribution, energy levels, color percentages
- Statistics window: `CEnvStatsWnd` (mini frame window)
- Magnify window: `CMagnifyWnd` for detailed biot inspection

## License
GNU Affero General Public License v3+ - see [COPYING](../COPYING)
Copyright (C) 1996-1998 Jason Spofford
