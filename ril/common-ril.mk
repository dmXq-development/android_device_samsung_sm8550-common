#
# Copyright (C) 2024 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

PRODUCT_PACKAGES += \
    sehradiomanager

PRODUCT_PACKAGES += \
    secril_config_svc

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/ril/sehradiomanager.conf:$(TARGET_COPY_OUT_VENDOR)/etc/sehradiomanager.conf
