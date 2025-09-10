#!/bin/bash
# just_build_helper.sh
# Cleans and builds meeting_dates, suppressing external/ warnings

set -e  # Exit immediately if a command fails
set -o pipefail

BUILD_DIR="${PWD}/build"

echo "=== Removing previous build directory ==="
rm -rf "${BUILD_DIR}"

echo "=== Creating build directory ==="
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

echo "=== Configuring project ==="
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo

echo "=== Building project ==="
cmake --build . -- -j$(nproc)

echo "=== Build finished ==="

