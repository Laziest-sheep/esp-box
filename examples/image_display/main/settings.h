/*
 * SPDX-FileCopyrightText: 2015-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#pragma once

#include "app_sr.h"

#define SSID_SIZE 32
#define PASSWORD_SIZE 64
#define KEY_SIZE 64
#define URL_SIZE 64

typedef struct {
    char ssid[SSID_SIZE];             /* SSID of target AP. */
    char password[PASSWORD_SIZE];     /* Password of target AP. */
    char key[KEY_SIZE];               /* OpenAI key. */
    char url[URL_SIZE];               /* OpenAI Base url. */
} wifi_param_t;

typedef struct {
    bool need_hint;
    sr_language_t sr_lang;
    uint8_t volume; // 0 - 100%
    bool radar_en;
} sys_param_t;

esp_err_t settings_read_parameter_from_nvs(void);
esp_err_t settings_write_parameter_to_nvs(void);
sys_param_t *settings_get_parameter(void);
