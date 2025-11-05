# Android Build

## First-Time Setup

Before building, you need to create the Gradle wrapper:

```bash
cd android
gradle wrapper --gradle-version=8.1
chmod +x gradlew
```

This will download `gradle-wrapper.jar` and create the wrapper scripts.

## Building

Once the wrapper is set up, build the APK:

```bash
./gradlew assembleRelease
```

Or use the convenience script from the project root:

```bash
../build-android.sh
```

## Requirements

- Java 17
- Android SDK (API 28+)
- Android NDK (r25+)
- Gradle 8.1+ (to create the wrapper)

## Output

The APK will be located at:
```
app/build/outputs/apk/release/app-release.apk
```

## Note

The `gradle-wrapper.jar` is not included in the repository. It will be automatically downloaded when you run `gradle wrapper` or during the GitHub Actions build process.
