#!/bin/bash
# just_rebuild_helper.sh
# Rebuild only the meeting_dates target if needed

BUILD_DIR="build"
TARGET="meeting_dates"

if [ ! -d "$BUILD_DIR" ]; then
    echo "Error: Build directory '$BUILD_DIR' does not exist."
    echo "Please run the full build script first."
    exit 1
fi

# Check if the target is already up-to-date
UP_TO_DATE=$(cmake --build "$BUILD_DIR" --target "$TARGET" -- -n 2>&1)

if echo "$UP_TO_DATE" | grep -q "nothing to be done"; then
    echo "Target '$TARGET' is already up-to-date. Skipping build."
else
    echo "=== Rebuilding $TARGET ==="
    cmake --build "$BUILD_DIR" --target "$TARGET" -- -j$(nproc)
    echo "=== Done ==="
fi

