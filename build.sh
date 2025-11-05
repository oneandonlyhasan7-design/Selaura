#!/bin/bash
# Selaura Client Build Script

echo "=== Selaura Client Build System ==="
echo "This is a C++ library project for Minecraft Bedrock Edition"
echo ""
echo "Build Status: Ready"
echo "Version: $(cat CMakeLists.txt | grep 'RUNTIME_VERSION' | head -1 | cut -d'"' -f2)"
echo "Branch: $(git rev-parse --abbrev-ref HEAD 2>/dev/null || echo 'unknown')"
echo ""
echo "To build for Android, see the build-android.sh script"
echo "To build for Linux, run: cd build && cmake .. -G Ninja && ninja"
echo "For GitHub Actions builds, push to trigger the workflow"
echo ""
echo "Build system initialized."
