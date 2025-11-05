# Selaura Client - Replit Project

## Overview
This is the Selaura Client project, a mod/client for Minecraft Bedrock Edition (MCPE). The project has been configured to support Android APK building with compatibility for both paid and cracked MCPE versions.

## Recent Changes
**Date: 2025-11-02**
- Added full Android build support with Gradle and CMake configuration
- Created GitHub Actions workflow for automated APK building
- Added JNI bridge for Android native library loading
- Created build scripts for easy local and CI/CD compilation
- Updated CMakeLists.txt to support Android ARM64 builds
- Documentation updated with build instructions

## Project Architecture

### Directory Structure
```
.
├── src/                    # C++ source code (core runtime)
│   ├── api/               # Minecraft API interfaces
│   ├── hooks/             # Game hooks and memory management
│   ├── event/             # Event system
│   ├── android_jni.cpp    # Android JNI bridge
│   └── runtime.cpp        # Core runtime logic
├── android/               # Android project
│   ├── app/
│   │   ├── src/main/
│   │   │   ├── java/     # Java/Kotlin launcher code
│   │   │   ├── res/      # Android resources
│   │   │   └── AndroidManifest.xml
│   │   └── build.gradle  # App-level Gradle config
│   ├── build.gradle      # Project-level Gradle config
│   └── settings.gradle
├── .github/workflows/    # GitHub Actions CI/CD
│   └── build-apk.yml     # APK build workflow
├── build-android.sh      # Android build script
├── build-linux.sh        # Linux build script
└── CMakeLists.txt        # Root CMake configuration

```

### Key Components

#### Native Library (C++)
- **Runtime**: Core client functionality and mod loading system
- **Hooks**: Memory manipulation and game function hooking
- **API**: Minecraft Bedrock Edition internal API interfaces
- **JNI**: Android Java Native Interface bridge

#### Android Launcher (Java)
- **MainActivity**: Detects and launches Minecraft with modifications
- **Package Detection**: Automatically finds both paid and cracked MCPE versions
- **Native Library Loader**: Loads and initializes the C++ runtime

#### Build System
- **CMake**: Cross-platform C++ build configuration
- **Gradle**: Android build system
- **GitHub Actions**: Automated CI/CD for APK building

## Platform Support

### Android
- Minimum SDK: 28 (Android 9+)
- Target SDK: 34
- Architecture: ARM64-v8a only
- **MCPE Compatibility**: Works with both paid (Google Play) and cracked versions

### Linux
- Compiler: Clang (required)
- Standard Library: libc++
- Architecture: x86_64

### Windows
- Compiler: MSVC or Clang-cl
- Architecture: x86_64

## Building

### Local Development
Use the provided build scripts:
- `./build-android.sh` - Build Android APK
- `./build-linux.sh` - Build Linux shared library
- `./build.sh` - Display build information

### CI/CD
GitHub Actions automatically builds APKs on:
- Push to master/main/develop branches
- Pull requests to master/main
- Manual workflow dispatch

Artifacts are uploaded and available for download.

## Features

### Multi-Version MCPE Support
The build system creates libraries compatible with:
- `com.mojang.minecraftpe` (Official paid version)
- `com.mojang.minecraftpe.beta` (Beta version)
- `com.mojang.minecraftpe.preview` (Preview version)
- `com.mojang.minecraftpe.demo` (Demo version)
- `com.mojang.minecraftpe.trial` (Trial version)

### Native Library Build System
The C++ runtime compiles to a native library providing:
- Custom UI rendering capabilities
- Event system
- Mod loading infrastructure
- Memory manipulation and function hooking support

**Important**: Full integration requires APK repackaging or Xposed module implementation. See INSTALL.md for integration methods.

## Dependencies

### C++ Libraries (via CPM)
- fmt: String formatting
- EnTT: Entity Component System
- spdlog: Logging
- libhat: Memory scanning and pattern matching
- SafetyHook: Safe function hooking
- GLM: Math library
- Glaze: JSON serialization
- magic_enum: Enum reflection

### Android
- AndroidX AppCompat
- Material Components
- ConstraintLayout

## Development Notes

### C++ Standard
- Currently using C++20 (downgraded from C++23 to avoid module scanning issues)
- C++ Standard Library: libc++ on Unix, MSVC STL on Windows

### Android NDK
- NDK version: r25+
- STL: c++_shared
- Position Independent Code (PIC) enabled

### Code Conventions
- Follow existing coding style in the codebase
- Use modern C++ features appropriately
- Ensure cross-platform compatibility

## Workflow Configuration
A Replit workflow has been configured to display build system information. This is a library project, so there's no running server.

## User Preferences
None specified yet.

## Implementation Status

### ✅ Completed
- Android build system (Gradle + CMake)
- Native library compilation for ARM64
- JNI bridge implementation
- GitHub Actions CI/CD workflow
- Build scripts for local development
- Multi-package MCPE detection

### ⚠️ Requires Additional Implementation
- **Process injection mechanism**: The native library builds successfully but requires APK repackaging or Xposed framework to inject into Minecraft
- **APK modification tools**: Automated patcher to integrate the library into Minecraft APK
- **Xposed module variant**: Alternative implementation using Xposed/LSPosed hooks

See INSTALL.md for detailed integration instructions.

## Known Issues
- LSP diagnostics show some errors due to missing Windows headers (normal on Linux environment)
- Some dependencies require proper include path configuration
- Test files (test/main.cpp) reference Windows-specific APIs
- Gradle wrapper JAR not included (downloaded automatically by GitHub Actions)
