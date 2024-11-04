/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/file.h>
#include <android-base/strings.h>

#include <fstream>

#include "AdaptiveBacklight.h"

using android::base::ReadFileToString;
using android::base::Trim;
using android::base::WriteStringToFile;

namespace vendor {
namespace lineage {
namespace livedisplay {
namespace V2_0 {
namespace samsung {

static constexpr const char* kBacklightPath = "/sys/class/lcd/panel/alpm";

bool AdaptiveBacklight::isSupported() {
    std::fstream backlight(kBacklightPath, backlight.in | backlight.out);
    return backlight.good();
}

// Methods from ::vendor::lineage::livedisplay::V2_0::IAdaptiveBacklight follow.
Return<bool> AdaptiveBacklight::isEnabled() {
    std::string tmp;
    int32_t contents = 0;

    if (ReadFileToString(kBacklightPath, &tmp)) {
        contents = std::stoi(Trim(tmp));
    }

    return contents > 0;
}

Return<bool> AdaptiveBacklight::setEnabled(bool enabled) {
    return WriteStringToFile(enabled ? "2" : "0", kBacklightPath, true);
}

}  // namespace samsung
}  // namespace V2_0
}  // namespace livedisplay
}  // namespace lineage
}  // namespace vendor
