/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/file.h>
#include <android-base/strings.h>

#include <fstream>

#include "SunlightEnhancement.h"

using android::base::ReadFileToString;
using android::base::Trim;
using android::base::WriteStringToFile;

namespace vendor {
namespace lineage {
namespace livedisplay {
namespace V2_0 {
namespace samsung {

static constexpr const char* kSREPath = "/sys/class/mdnie/mdnie/outdoor";

// Methods from ::vendor::lineage::livedisplay::V2_0::ISunlightEnhancement follow.
bool SunlightEnhancement::isSupported() {
    std::fstream sre(kSREPath, sre.in | sre.out);

    return sre.good();
}

// Methods from ::vendor::lineage::livedisplay::V2_0::IAdaptiveBacklight follow.
Return<bool> SunlightEnhancement::isEnabled() {
    std::string tmp;
    int32_t statusSRE = 0;
    if (ReadFileToString(kSREPath, &tmp)) {
        statusSRE = std::stoi(Trim(tmp));
    }

    return statusSRE == 1;
}

Return<bool> SunlightEnhancement::setEnabled(bool enabled) {
    return WriteStringToFile(enabled ? "1" : "0", kSREPath, true);
}

}  // namespace samsung
}  // namespace V2_0
}  // namespace livedisplay
}  // namespace lineage
}  // namespace vendor
