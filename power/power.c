/*
 * Copyright (C) 2014, The CyanogenMod Project <http://www.cyanogenmod.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LOG_TAG "Picassowifi PowerHAL"
#include <utils/Log.h>

#include <hardware/hardware.h>
#include <hardware/power.h>

#define BUTTONS_FLASH_MS   5
#define BUTTONS_BRIGHTNESS "/sys/devices/virtual/sec/sec_touchkey/brightness"

/* Remember old state of the interactive flag (which is on on boot) to avoid
 * flashing the button lights more than 1 and to avoid flashing them on boot.
 */
static int old_interactive_state = 1;

static void sysfs_write(char *path, char *s) {
    char buf[80];
    int len;
    int fd = open(path, O_WRONLY);

    if (fd < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);
        return;
    }

    len = write(fd, s, strlen(s));
    if (len < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error writing to %s: %s\n", path, buf);
    }

    close(fd);
}

static void
flash_buttons(void)
{
    sysfs_write(BUTTONS_BRIGHTNESS, "1");
    usleep(BUTTONS_FLASH_MS*1000);
    sysfs_write(BUTTONS_BRIGHTNESS, "0");
}

static void power_init(struct power_module *module)
{
}

static void power_set_interactive(struct power_module *module, int on)
{
    ALOGD("%s on=%d old=%d\n", __func__, on, old_interactive_state);

    if (on && ! old_interactive_state) {
        flash_buttons();
    }

    old_interactive_state = on;
}

static void power_hint(struct power_module *module, power_hint_t hint,
                       void *data) {
    switch (hint) {
    default:
        break;
    }
}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

struct power_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = POWER_MODULE_API_VERSION_0_2,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = POWER_HARDWARE_MODULE_ID,
        .name = "Picassowifi Power HAL",
        .author = "The CyanogenMod Project",
        .methods = &power_module_methods,
    },

    .init = power_init,
    .setInteractive = power_set_interactive,
    .powerHint = power_hint,
};
