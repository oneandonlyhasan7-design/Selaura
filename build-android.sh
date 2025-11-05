#!/bin/bash
# Build script for Android APK

set -e

echo "=== Selaura Client - Android Build Script ==="
echo ""

# Check for required tools
if ! command -v gradle &> /dev/null && [ ! -f "android/gradlew" ]; then
    echo "ERROR: Gradle not found. Please install Gradle or ensure gradlew exists."
    exit 1
fi

# Check for Android SDK
if [ -z "$ANDROID_HOME" ] && [ -z "$ANDROID_SDK_ROOT" ]; then
    echo "WARNING: ANDROID_HOME or ANDROID_SDK_ROOT not set."
    echo "Please set one of these environment variables to your Android SDK location."
    exit 1
fi

# Check for NDK
if [ -z "$ANDROID_NDK_HOME" ] && [ -z "$ANDROID_NDK" ]; then
    echo "WARNING: ANDROID_NDK_HOME or ANDROID_NDK not set."
    echo "Please install Android NDK and set the environment variable."
    exit 1
fi

echo "Android SDK: ${ANDROID_HOME:-$ANDROID_SDK_ROOT}"
echo "Android NDK: ${ANDROID_NDK_HOME:-$ANDROID_NDK}"
echo ""

# Navigate to android directory
cd android

# Create Gradle wrapper if it doesn't exist
if [ ! -f "gradlew" ] || [ ! -f "gradle/wrapper/gradle-wrapper.jar" ]; then
    echo "Creating Gradle wrapper..."
    gradle wrapper --gradle-version=8.1
fi

# Make gradlew executable
chmod +x gradlew

echo "Building APK..."
echo ""

# Build the APK
./gradlew clean assembleRelease --stacktrace

echo ""
echo "=== Build Complete! ==="
echo ""
echo "APK Location:"
find app/build/outputs/apk -name "*.apk" -type f

echo ""
echo "This APK works with both paid and cracked MCPE versions!"
echo "Install it on your Android device to use Selaura Client."
