<h1 align="center">
Selaura Client
</h1>
<p align="center">
 <a href="https://selauraclient.com/discord" target="_blank">Discord</a>
 •
 <a href="https://selauraclient.com/" target="_blank">Website</a>
 •
 <a href="https://docs.selauraclient.com/" target="_blank">Scripting Documentation</a>
</p>

This repository contains the full source code for Selaura Client. Selaura Client is a mod that aims to improve user experience of Minecraft: Bedrock Edition.

## 🖥️ Compatibility
Selaura Client aims to support:
- Windows 10/11 (64-bit Only)
- Android 9+ (ARM64 Only) - **Works with both paid and cracked MCPE versions**
- Any device supporting [mcpelauncher-linux](https://github.com/minecraft-linux/mcpelauncher-manifest)

### ✅ MCPE Version Support
The build system supports creating libraries for:
- Official Google Play version (com.mojang.minecraftpe)
- Beta/Preview versions
- Demo/Trial versions
- Cracked/Modified versions

**Note**: Full integration requires additional steps (APK repackaging or Xposed module). See [INSTALL.md](INSTALL.md) for details.

## 🔨 Building from Source

### Building for Android
**Requirements:**
- Android SDK (API 28+)
- Android NDK (r25+)
- Gradle 8.1+
- CMake 3.22+

**Quick Build:**
```bash
./build-android.sh
```

**Manual Build:**
```bash
cd android
./gradlew assembleRelease
```

The APK will be located at: `android/app/build/outputs/apk/release/`

### Building for Linux
**Requirements:**
- Clang compiler
- CMake 3.28+
- Ninja or Make

**Quick Build:**
```bash
./build-linux.sh
```

**Manual Build:**
```bash
mkdir build && cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja
```

### Building for Windows
Refer to the original project documentation for Windows build instructions.

### GitHub Actions
This repository includes automated APK building via GitHub Actions:
- Builds are triggered on push to main branches
- APK artifacts are automatically generated
- Works with both paid and cracked MCPE versions

## ✨ Open Source Technologies Used
- [fmtlib/fmt](https://github.com/fmtlib/fmt)
- [skypjack/entt](https://github.com/skypjack/entt)
- [foonathan/type_safe](https://github.com/foonathan/type_safe)
- [BasedInc/libhat](https://github.com/BasedInc/libhat)
- [Neargye/magic_enum](https://github.com/Neargye/magic_enum)
- [g-truc/glm](https://github.com/g-truc/glm)
- [ocornut/imgui](https://github.com/ocornut/imgui)

## 📈 Star History
[![Star History Chart](https://api.star-history.com/svg?repos=selauraclient/client&type=Date)](https://www.star-history.com/#selauraclient/client&Date)

## 📄 License
Selaura Client currently falls under the [GPL-3.0 License](LICENSE). Feel free to use this code as a fork in your own project. Thank you!
