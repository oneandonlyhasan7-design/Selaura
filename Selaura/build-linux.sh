#!/bin/bash
# Build script for Linux

set -e

echo "=== Selaura Client - Linux Build Script ==="
echo ""

# Check for required tools
if ! command -v cmake &> /dev/null; then
    echo "ERROR: CMake not found. Please install CMake 3.28 or later."
    exit 1
fi

if ! command -v ninja &> /dev/null && ! command -v make &> /dev/null; then
    echo "ERROR: Neither Ninja nor Make found. Please install one of them."
    exit 1
fi

# Determine build system
if command -v ninja &> /dev/null; then
    GENERATOR="Ninja"
    BUILD_CMD="ninja"
else
    GENERATOR="Unix Makefiles"
    BUILD_CMD="make -j$(nproc)"
fi

echo "Build system: $GENERATOR"
echo ""

# Create and enter build directory
mkdir -p build
cd build

# Configure
echo "Configuring project..."
cmake .. -G "$GENERATOR" -DCMAKE_BUILD_TYPE=Release

echo ""
echo "Building..."
$BUILD_CMD

echo ""
echo "=== Build Complete! ==="
echo ""
echo "Library location:"
find . -name "libselaura_runtime.so" -type f

echo ""
echo "To use this library, place it in the appropriate Minecraft directory."
