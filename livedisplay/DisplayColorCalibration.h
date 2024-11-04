/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <vendor/lineage/livedisplay/2.0/IDisplayColorCalibration.h>

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

class DisplayColorCalibration : public IDisplayColorCalibration {
  public:
    bool isSupported();

    // Methods from ::vendor::lineage::livedisplay::V2_0::IDisplayColorCalibration follow.
    Return<int32_t> getMaxValue() override;
    Return<int32_t> getMinValue() override;
    Return<void> getCalibration(getCalibration_cb resultCb) override;
    Return<bool> setCalibration(const hidl_vec<int32_t>& rgb) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
};

}  // namespace samsung
}  // namespace V2_0
}  // namespace livedisplay
}  // namespace lineage
}  // namespace vendor
