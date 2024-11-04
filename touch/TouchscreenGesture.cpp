/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <fstream>

#include "TouchscreenGesture.h"

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace samsung {

static constexpr const char* kTspPath = TSP_CMD_NODE;

const std::map<int32_t, TouchscreenGesture::GestureInfo> TouchscreenGesture::kGestureInfoMap = {
    // clang-format off
    {0, {0x1c7, "Single Tap"}},
    // clang-format on
};

bool TouchscreenGesture::isSupported() {
    std::ifstream file(kTspPath);
    return file.good();
}

// Methods from ::vendor::lineage::touch::V1_0::ITouchscreenGesture follow.
Return<void> TouchscreenGesture::getSupportedGestures(getSupportedGestures_cb resultCb) {
    std::vector<Gesture> gestures;

    for (const auto& entry : kGestureInfoMap) {
        gestures.push_back({entry.first, entry.second.name, entry.second.keycode});
    }
    resultCb(gestures);

    return Void();
}

Return<bool> TouchscreenGesture::setGestureEnabled(
    const ::vendor::lineage::touch::V1_0::Gesture&, bool enabled) {
    std::fstream file(kTspPath);

    file << "singletap_enable," << (enabled ? "1" : "0");

    return !file.fail();
}

// Methods from ::android::hidl::base::V1_0::IBase follow.

}  // namespace samsung
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
