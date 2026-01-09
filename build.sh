#!/usr/bin/env bash
set -euo pipefail

# How to use:
# -----------------------------
# ./build.sh                 # Debug build
# ./build.sh --debug         # Explicit debug
# ./build.sh --release       # Optimized release
# ./build.sh --clean         # Nuke build dir
# ./build.sh --clean --run   # Clean → build → run
# ./build.sh --release --run

# Config
BUILD_DIR="build"
BUILD_TYPE="Debug"
RUN_AFTER_BUILD=0
CLEAN=0

# IMPORTANT: set this to your CMake target name / binary name
TARGET="digital-pet"

# Args
for arg in "$@"; do
  case "$arg" in
    --release) BUILD_TYPE="Release" ;;
    --debug)   BUILD_TYPE="Debug" ;;
    --run)     RUN_AFTER_BUILD=1 ;;
    --clean)   CLEAN=1 ;;
    *)
      echo "Unknown option: $arg"
      echo "Usage: ./build.sh [--debug] [--release] [--clean] [--run]"
      exit 1
      ;;
  esac
done

# Clean
if [[ "$CLEAN" -eq 1 ]]; then
  echo ":P Cleaning build directory"
  rm -rf "$BUILD_DIR"
fi

# Build
echo ":D Building ($BUILD_TYPE)"
cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
cmake --build "$BUILD_DIR" -j"$(nproc)"

# Run (optional)
if [[ "$RUN_AFTER_BUILD" -eq 1 ]]; then
  BIN="./$BUILD_DIR/$TARGET"
  echo ":O Running binary... ($BIN)"
  if [[ ! -x "$BIN" ]]; then
    echo ":X Binary not found or not executable: $BIN"
    echo ":i If your target name differs, update TARGET in build.sh"
    exit 1
  fi
  exec "$BIN"
fi

