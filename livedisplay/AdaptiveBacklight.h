/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef VENDOR_LINEAGE_LIVEDISPLAY_V2_0_ADAPTIVEBACKLIGHT_H
#define VENDOR_LINEAGE_LIVEDISPLAY_V2_0_ADAPTIVEBACKLIGHT_H

#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <vendor/lineage/livedisplay/2.0/IAdaptiveBacklight.h>

namespace vendor {
namespace lineage {
namespace livedisplay {
namespace V2_0 {
namespace samsung {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

class AdaptiveBacklight : public IAdaptiveBacklight {
  public:
    bool isSupported();

    // Methods from ::vendor::lineage::livedisplay::V2_0::IAdaptiveBacklight follow.
    Return<bool> isEnabled() override;
    Return<bool> setEnabled(bool enabled) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
};

}  // namespace samsung
}  // namespace V2_0
}  // namespace livedisplay
}  // namespace lineage
}  // namespace vendor

#endif  // VENDOR_LINEAGE_LIVEDISPLAY_V2_0_ADAPTIVEBACKLIGHT_H
