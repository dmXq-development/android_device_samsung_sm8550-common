/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/file.h>
#include <android-base/strings.h>

#include <fstream>

#include "DisplayColorCalibration.h"

using android::base::ReadFileToString;
using android::base::Split;
using android::base::Trim;
using android::base::WriteStringToFile;

namespace vendor {
namespace lineage {
namespace livedisplay {
namespace V2_0 {
namespace samsung {

static constexpr const char* kColorPath = "/sys/class/mdnie/mdnie/sensorRGB";

bool DisplayColorCalibration::isSupported() {
    std::fstream rgb(kColorPath, rgb.in | rgb.out);
    return rgb.good();
}

Return<int32_t> DisplayColorCalibration::getMaxValue() {
    return 255;
}

Return<int32_t> DisplayColorCalibration::getMinValue() {
    return 1;
}

Return<void> DisplayColorCalibration::getCalibration(getCalibration_cb resultCb) {
    std::vector<int32_t> rgb;
    std::string tmp;

    if (ReadFileToString(kColorPath, &tmp)) {
        std::vector<std::string> colors = Split(Trim(tmp), " ");
        for (const std::string& color : colors) {
            rgb.push_back(std::stoi(color));
        }
    }

    resultCb(rgb);
    return Void();
}

Return<bool> DisplayColorCalibration::setCalibration(const hidl_vec<int32_t>& rgb) {
    std::string contents;
    for (const int32_t& color : rgb) {
        contents += std::to_string(color) + " ";
    }
    return WriteStringToFile(Trim(contents), kColorPath, true);
}

}  // namespace samsung
}  // namespace V2_0
}  // namespace livedisplay
}  // namespace lineage
}  // namespace vendor
