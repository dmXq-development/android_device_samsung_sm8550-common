/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <vendor/lineage/touch/1.0/ITouchscreenGesture.h>
#include "samsung_touch.h"

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace samsung {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

class TouchscreenGesture : public ITouchscreenGesture {
  public:
    bool isSupported();

    // Methods from ::vendor::lineage::touch::V1_0::ITouchscreenGesture follow.
    Return<void> getSupportedGestures(getSupportedGestures_cb resultCb) override;
    Return<bool> setGestureEnabled(const ::vendor::lineage::touch::V1_0::Gesture& gesture,
                                   bool enabled) override;

  private:
    typedef struct {
        int32_t keycode;
        const char* name;
    } GestureInfo;
    static const std::map<int32_t, GestureInfo> kGestureInfoMap;  // id -> info
};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" ITouchscreenGesture* HIDL_FETCH_ITouchscreenGesture(const char* name);

}  // namespace samsung
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
