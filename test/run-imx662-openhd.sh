#!/bin/bash
set -euo pipefail
source_dir=$(cd "$(dirname "$0")/.." && pwd)
build_dir=$(realpath "${1:?Usage: run-imx662-openhd.sh MATCHING_LIBCAMERA_CORE_BUILD OUTPUT_DIR}")
validation_dir=${2:?Usage: run-imx662-openhd.sh MATCHING_LIBCAMERA_CORE_BUILD OUTPUT_DIR}
mkdir -p "$validation_dir"
# Compile the actual controller algorithms, helper and metadata without requiring
# the unrelated binary-only Pivariety SDK used by the complete RPi IPA build.
g++ -std=c++17 -O0 -DLIBCAMERA_BASE_PRIVATE -include "$build_dir/config.h" \
    -I"$source_dir" -I"$source_dir/include" -I"$source_dir/include/libcamera" \
    -I"$build_dir/include" -I"$build_dir/include/libcamera" \
    -I"$source_dir/src/ipa/rpi" -I"$source_dir/src/ipa/rpi/controller" \
    "$source_dir/test/imx662-openhd.cpp" \
    "$source_dir/src/ipa/rpi/cam_helper/cam_helper.cpp" \
    "$source_dir/src/ipa/rpi/cam_helper/cam_helper_imx662.cpp" \
    "$source_dir/src/libcamera/camera_sensor_properties.cpp" \
    "$source_dir/src/ipa/rpi/controller/"*.cpp \
    "$source_dir/src/ipa/rpi/controller/rpi/"*.cpp \
    -L"$build_dir/src/libcamera" -L"$build_dir/src/libcamera/base" \
    -Wl,-rpath,"$build_dir/src/libcamera" -Wl,-rpath,"$build_dir/src/libcamera/base" \
    -lcamera -lcamera-base -lyaml -pthread -o "$validation_dir/test-imx662"
"$validation_dir/test-imx662" "$source_dir/src/ipa/rpi/vc4/data/imx662.json"
