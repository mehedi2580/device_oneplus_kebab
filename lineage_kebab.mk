#
# Copyright (C) 2018 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit from kebab device
$(call inherit-product, device/oneplus/kebab/device.mk)

# Inherit some common Lineage stuff.
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

# Rom flags
RICE_MAINTAINER := Chaeyoung
RICE_OFFICIAL := true
RICE_DEVICE := kebab
RICE_CHIPSET := SDM8705G
SUSHI_BOOTANIMATION  := 1080
TARGET_HAS_UDFPS := true
TARGET_ENABLE_BLUR := true
TARGET_SUPPORTS_QUICK_TAP := true
TARGET_FACE_UNLOCK_SUPPORTED := true
TARGET_BUILD_GRAPHENEOS_CAMERA := false

# Device identifier. This must come after all inclusions.
PRODUCT_NAME := lineage_kebab
PRODUCT_DEVICE := kebab
PRODUCT_MANUFACTURER := OnePlus
PRODUCT_BRAND := OnePlus
PRODUCT_MODEL := KB2001

PRODUCT_SYSTEM_NAME := OnePlus8T
PRODUCT_SYSTEM_DEVICE := OnePlus8T

PRODUCT_GMS_CLIENTID_BASE := android-oneplus

PRODUCT_BUILD_PROP_OVERRIDES += \
    TARGET_DEVICE=OnePlus8T \
    TARGET_PRODUCT=OnePlus8T

BUILD_FINGERPRINT := "google/raven/raven:13/TP1A.220624.021/8877034:user/release-keys"

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="raven-user 13 TP1A.220624.021 8877034 release-keys"
