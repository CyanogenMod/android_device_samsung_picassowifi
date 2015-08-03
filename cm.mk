$(call inherit-product, device/samsung/v2wifixx/full_v2wifixx.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_tablet_wifionly.mk)

PRODUCT_NAME := cm_v2wifixx
PRODUCT_DEVICE := v2wifixx

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_MODEL=SM-T900 \
    PRODUCT_NAME=v2wifixx \
    PRODUCT_DEVICE=v2wifixx \
    TARGET_DEVICE=v2wifixx \
