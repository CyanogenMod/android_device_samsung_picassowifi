$(call inherit-product, device/samsung/picassowifi/full_picassowifi.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_tablet_wifionly.mk)

PRODUCT_NAME := cm_picassowifi
PRODUCT_DEVICE := picassowifi

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_MODEL=SM-T520 \
    PRODUCT_NAME=picassowifi \
    PRODUCT_DEVICE=picassowifi \
    TARGET_DEVICE=picassowifi \
