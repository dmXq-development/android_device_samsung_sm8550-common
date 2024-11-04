/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.lineage.touch@1.0-service.samsung"

#include <android-base/logging.h>
#include <binder/ProcessState.h>
#include <hidl/HidlTransportSupport.h>

#include "GloveMode.h"
#include "TouchscreenGesture.h"

using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;
using android::status_t;
using android::OK;

using ::vendor::lineage::touch::V1_0::samsung::GloveMode;
using ::vendor::lineage::touch::V1_0::samsung::TouchscreenGesture;

int main() {
    sp<GloveMode> gloveMode;
    sp<TouchscreenGesture> touchscreenGesture;
    status_t status;

    LOG(INFO) << "Touch HAL service is starting.";

    gloveMode = new GloveMode();
    if (gloveMode == nullptr) {
        LOG(ERROR) << "Can not create an instance of Touch HAL GloveMode Iface, exiting.";
        goto shutdown;
    }

    touchscreenGesture = new TouchscreenGesture();
    if (touchscreenGesture == nullptr) {
        LOG(ERROR) << "Can not create an instance of Touch HAL TouchscreenGesture Iface, exiting.";
        goto shutdown;
    }

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    if (gloveMode->isSupported()) {
        status = gloveMode->registerAsService();
        if (status != OK) {
            LOG(ERROR) << "Could not register service for Touch HAL GloveMode Iface (" << status
                       << ")";
            goto shutdown;
        }
    }

    if (touchscreenGesture->isSupported()) {
        status = touchscreenGesture->registerAsService();
        if (status != OK) {
            LOG(ERROR) << "Could not register service for Touch HAL TouchscreenGesture Iface ("
                       << status << ")";
            goto shutdown;
        }
    }

    LOG(INFO) << "Touch HAL service is ready.";
    joinRpcThreadpool();
// Should not pass this line

shutdown:
    // In normal operation, we don't expect the thread pool to shutdown
    LOG(ERROR) << "Touch HAL service is shutting down.";
    return 1;
}
