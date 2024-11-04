/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef LIVES_IN_SYSTEM
#define LOG_TAG "lineage.livedisplay@2.0-service.samsung-qcom.sm8550"
#else
#define LOG_TAG "vendor.lineage.livedisplay@2.0-service.samsung-qcom.sm8550"
#endif

#include <android-base/logging.h>
#include <binder/ProcessState.h>
#include <hidl/HidlTransportSupport.h>

#include "AdaptiveBacklight.h"
#include "SunlightEnhancement.h"
#include "DisplayColorCalibration.h"

using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;
using android::status_t;
using android::OK;

using vendor::lineage::livedisplay::V2_0::samsung::AdaptiveBacklight;
using vendor::lineage::livedisplay::V2_0::samsung::SunlightEnhancement;
using vendor::lineage::livedisplay::V2_0::samsung::DisplayColorCalibration;

int main() {
    sp<AdaptiveBacklight> adaptiveBacklight;
    sp<SunlightEnhancement> sunlightEnhancement;
    sp<DisplayColorCalibration> displayColorCalibration;
    status_t status;

    LOG(INFO) << "LiveDisplay HAL service is starting.";

    adaptiveBacklight = new AdaptiveBacklight();
    if (adaptiveBacklight == nullptr) {
        LOG(ERROR)
            << "Can not create an instance of LiveDisplay HAL AdaptiveBacklight Iface, exiting.";
        goto shutdown;
    }

    sunlightEnhancement = new SunlightEnhancement();
    if (sunlightEnhancement == nullptr) {
        LOG(ERROR)
            << "Can not create an instance of LiveDisplay HAL SunlightEnhancement Iface, exiting.";
        goto shutdown;
    }

    displayColorCalibration = new DisplayColorCalibration();
    if (displayColorCalibration == nullptr) {
        LOG(ERROR) << "Can not create an instance of LiveDisplay HAL DisplayColorCalibration "
                      "Iface, exiting.";
        goto shutdown;
    }

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    if (adaptiveBacklight->isSupported()) {
        status = adaptiveBacklight->registerAsService();
        if (status != OK) {
            LOG(ERROR) << "Could not register service for LiveDisplay HAL AdaptiveBacklight Iface ("
                       << status << ")";
            goto shutdown;
        }
    }

    if (sunlightEnhancement->isSupported()) {
        status = sunlightEnhancement->registerAsService();
        if (status != OK) {
            LOG(ERROR)
                << "Could not register service for LiveDisplay HAL SunlightEnhancement Iface ("
                << status << ")";
            goto shutdown;
        }
    }

    if (displayColorCalibration->isSupported()) {
        status = displayColorCalibration->registerAsService();
        if (status != OK) {
            LOG(ERROR)
                << "Could not register service for LiveDisplay HAL DisplayColorCalibration Iface ("
                << status << ")";
            goto shutdown;
        }
    }

    LOG(INFO) << "LiveDisplay HAL service is ready.";
    joinRpcThreadpool();
// Should not pass this line

shutdown:
    // In normal operation, we don't expect the thread pool to shutdown
    LOG(ERROR) << "LiveDisplay HAL service is shutting down.";
    return 1;
}
