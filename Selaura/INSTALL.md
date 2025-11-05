# Installation and Build Guide

## Important Notice

This build system creates an Android launcher app with native library support. However, for full MCPE integration, additional implementation is required:

### Current Implementation
✅ Android launcher app that detects MCPE installations  
✅ Native C++ library compilation for ARM64  
✅ JNI bridge for Android  
✅ GitHub Actions CI/CD for automated builds  
✅ Support for multiple MCPE package names

### Additional Work Needed for Full Functionality
❌ **Process injection mechanism** - The native library needs to be injected into the running Minecraft process  
❌ **APK repackaging** - OR the Minecraft APK needs to be modified to load the library  
❌ **Xposed/LSPosed support** - OR implement as an Xposed module for runtime hooking

## Installation Methods

### Method 1: APK Repackaging (Recommended)
This requires modifying the original Minecraft APK to include the Selaura runtime:

1. Build the native library: `./build-android.sh`
2. Extract the original Minecraft APK
3. Add `libselaura_runtime.so` to `lib/arm64-v8a/`
4. Modify the APK to load the library on startup
5. Repackage and sign the APK

**Tools needed:** apktool, jarsigner, zipalign

### Method 2: Xposed/LSPosed Module
Convert this project to an Xposed module:

1. Implement Xposed hooks instead of direct memory access
2. Use Xposed API to inject into Minecraft process
3. Package as an Xposed module
4. Install using LSPosed framework

**Requirements:** Rooted device with LSPosed installed

### Method 3: System-Level Integration
For devices with root access:

1. Build the library
2. Use ptrace or /proc/mem to inject into running Minecraft
3. Requires root access and SELinux permissive mode

## Building

### Prerequisites

#### For Android (Local Build)
```bash
# Install Android SDK
export ANDROID_HOME=/path/to/android-sdk
export ANDROID_NDK_HOME=/path/to/ndk

# Install required tools
sudo apt-get install -y openjdk-17-jdk gradle

# Build
./build-android.sh
```

#### For Android (GitHub Actions)
Simply push to the repository - the GitHub Actions workflow will:
- Set up Android SDK/NDK
- Build the native library
- Create the APK
- Upload artifacts

### Build Outputs

After building, you'll find:
- **Native Library**: `android/app/build/intermediates/cmake/release/obj/arm64-v8a/libselaura_runtime.so`
- **APK**: `android/app/build/outputs/apk/release/app-release.apk`

## Manual Integration Steps

### Integrating into Minecraft APK

1. **Build the library**:
   ```bash
   ./build-android.sh
   ```

2. **Extract Minecraft APK**:
   ```bash
   apktool d com.mojang.minecraftpe.apk -o minecraft_unpacked
   ```

3. **Copy the native library**:
   ```bash
   cp android/app/build/intermediates/cmake/release/obj/arm64-v8a/libselaura_runtime.so \
      minecraft_unpacked/lib/arm64-v8a/
   ```

4. **Modify to load library** (edit `minecraft_unpacked/smali/.../MainActivity.smali`):
   ```smali
   # Add in onCreate method:
   const-string v0, "selaura_runtime"
   invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
   ```

5. **Repackage**:
   ```bash
   apktool b minecraft_unpacked -o minecraft_modded.apk
   ```

6. **Sign**:
   ```bash
   jarsigner -sigalg SHA1withRSA -digestalg SHA1 \
     -keystore my-release-key.keystore minecraft_modded.apk alias_name
   zipalign -v 4 minecraft_modded.apk minecraft_final.apk
   ```

7. **Install**:
   ```bash
   adb install minecraft_final.apk
   ```

## Compatibility

### Supported MCPE Versions
The code is designed to work with:
- Official Google Play version (`com.mojang.minecraftpe`)
- Beta versions (`com.mojang.minecraftpe.beta`)
- Preview versions (`com.mojang.minecraftpe.preview`)  
- Demo/Trial versions (`com.mojang.minecraftpe.demo`, `com.mojang.minecraftpe.trial`)

### Device Requirements
- Android 9.0+ (API 28+)
- ARM64-v8a architecture
- At least 2GB RAM
- Minecraft Bedrock Edition installed

## Troubleshooting

### "Library not loaded" errors
- Ensure the library is in the correct `lib/arm64-v8a/` directory
- Check that the load call is in the correct location in the APK

### Build failures
- Verify Android SDK and NDK are properly installed
- Check that environment variables are set correctly
- Ensure Java 17 is installed

### APK signing issues
- Create a keystore if you don't have one:
  ```bash
  keytool -genkey -v -keystore my-release-key.keystore \
    -alias alias_name -keyalg RSA -keysize 2048 -validity 10000
  ```

## Contributing

To add full injection support, consider implementing one of:
1. APK patcher tool (automates the repackaging process)
2. Xposed module version
3. Root-based process injection

See the main README for contribution guidelines.
