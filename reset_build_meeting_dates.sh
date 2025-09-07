#!/bin/bash
# reset_build_meeting_dates.sh
# Cleans, re-fetches xlnt, applies fixes, configures, and builds meeting_dates

set -e

echo "=== Cleaning old xlnt source and build directories ==="
rm -rf external/xlnt-src build

echo "=== Cloning clean xlnt source ==="
mkdir -p external
git clone https://github.com/tfussell/xlnt.git external/xlnt-src
cd external/xlnt-src
git checkout 568ac85346bc37757b0cd16464e7e1ea7656df91
cd ../..

echo "=== Fixing bad version file in libstudxml ==="
echo "1.1.0-b.8" > external/xlnt-src/third-party/libstudxml/version.txt
rm -f external/xlnt-src/third-party/libstudxml/version

echo "=== Patching xlnt CMake files safely ==="
find external/xlnt-src -name "CMakeLists.txt" | while read f; do
    echo "Patching $f"
    sed -i 's/cmake_minimum_required([^)]*)/cmake_minimum_required(VERSION 3.16)/g' "$f"
done

echo "=== Creating fresh build directory ==="
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
cd ..

echo "=== Building meeting_dates ==="
cmake --build build --config RelWithDebInfo -j$(nproc)

echo "=== Build finished successfully ==="

