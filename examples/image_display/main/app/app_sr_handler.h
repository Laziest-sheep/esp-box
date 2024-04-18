/*
 * SPDX-FileCopyrightText: 2015-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#pragma once

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*esp_sr_cmd_cb_t)(void);

typedef enum
{
    TURN_ON_THE_LIGHT = 0,
    TURN_OFF_THE_LIGHT,
    MY_SELF,
    TURN_ON_AC,
    TURN_OFF_AC,
    MAX_CMD_NUM
}ESP_SR_CMD_ID;

bool sr_echo_is_playing(void);

void sr_handler_task(void *pvParam);

#ifdef __cplusplus
}
#endif
