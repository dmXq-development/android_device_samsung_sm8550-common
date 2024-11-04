/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <vendor/lineage/touch/1.0/IGloveMode.h>
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

class GloveMode : public IGloveMode {
  public:
    GloveMode() = default;

    bool isSupported();

    // Methods from ::vendor::lineage::touch::V1_0::IGloveMode follow.
    Return<bool> isEnabled() override;
    Return<bool> setEnabled(bool enabled) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
};

}  // namespace samsung
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
