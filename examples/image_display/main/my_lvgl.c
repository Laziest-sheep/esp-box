#include "my_lvgl.h"
#include "lvgl.h"
#include "bsp/esp-bsp.h"
#include "esp_log.h"
#include "app_led.h"


#define PROFILE_SIZE        150
#define PROFILE_POS_X       170
#define PROFILE_POS_Y       0

#define BTN_START_W         150
#define BTN_START_H         30
#define BTN_START_POS_X     85
#define BTN_START_POS_Y     200



LV_IMG_DECLARE(profile);
LV_IMG_DECLARE(led_img);
LV_IMG_DECLARE(AC_img);
LV_IMG_DECLARE(SR_img);
LV_IMG_DECLARE(listen_img);
static lv_obj_t *scr_start;
static lv_obj_t *scr_func;
static lv_obj_t *scr_listen;
static lv_obj_t *scr_respond;
static lv_obj_t *btn_start;
static lv_obj_t *label_start;
static lv_obj_t *label_time;
static lv_obj_t *switch_led;
static lv_obj_t *switch_AC;     //air-conditioning
static lv_obj_t *switch_SR;     //speech recognition
static lv_obj_t *img_profile;
static lv_obj_t *img_led;
static lv_obj_t *img_SR;
static lv_obj_t *img_AC;
static lv_obj_t *img_listen;
static lv_obj_t *obj_led_bg;
static lv_obj_t *obj_AC_bg;
static lv_obj_t *obj_SR_bg;
static lv_obj_t *label_led;
static lv_obj_t *label_AC;
static lv_obj_t *label_SR;
static lv_obj_t *label_myself;
static lv_font_t *font_12 = (lv_font_t *)&lv_font_montserrat_12;
static lv_font_t *font_14 = (lv_font_t *)&lv_font_montserrat_14;

extern void bt_led_set(uint8_t on_off);

char time_buf[32] = {0};

static void btn_start_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
    {
        lv_scr_load(scr_func);
    }
}

static void switch_led_cb(lv_event_t *e)
{
    if(lv_obj_has_state(switch_led, LV_STATE_CHECKED))
    {
        app_pwm_led_set_power(1);
    }
    else
    {
        app_pwm_led_set_power(0);
    }
}

static void switch_AC_cb(lv_event_t *e)
{
    if(lv_obj_has_state(switch_AC, LV_STATE_CHECKED))
    {
        bt_led_set(1);
    }
    else
    {
        bt_led_set(0);
    }
}

static void switch_SR_cb(lv_event_t *e)
{
    if(lv_obj_has_state(switch_SR, LV_STATE_CHECKED))
    {
        
    }
    else
    {
        
    }
}

static void scr_listen_init(void)
{
    img_listen = lv_img_create(scr_listen);
    lv_img_set_src(img_listen, &listen_img);
    lv_img_set_zoom(img_listen, 128);
    lv_img_set_pivot(img_listen, 200, 0);
}

static void scr_respond_init(void)
{

}

void lv_load_listen(void)
{
    lv_scr_load(scr_listen);
}

void lv_load_func(void)
{
    lv_scr_load(scr_func);
}

void set_myself(void)
{
    label_myself = lv_label_create(scr_listen);
    lv_label_set_text(label_myself, "YOU SB");
    lv_obj_set_style_text_font(label_myself, font_12, LV_STATE_DEFAULT);
    lv_obj_align(label_myself, LV_ALIGN_CENTER, 0, 0);
}

static void scr_module_init(void)
{
    /*创建页面*/
    scr_start = lv_obj_create(NULL);
    scr_func = lv_obj_create(NULL);
    scr_listen = lv_obj_create(NULL);
    scr_respond = lv_obj_create(NULL);

    /*禁用页面滚动*/
    lv_obj_clear_flag(scr_start, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(scr_func, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(scr_listen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(scr_respond, LV_OBJ_FLAG_SCROLLABLE);
    
    /*设置背景颜色*/
    lv_obj_set_style_bg_color(scr_start, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(scr_func, lv_color_hex(0x00ffff), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(scr_listen, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(scr_respond, lv_color_hex(0xffffff), LV_STATE_DEFAULT);

    /*加载初始页面*/
    lv_scr_load(scr_start);

    /*初始页面图像显示*/
    img_profile = lv_img_create(scr_start);
    lv_img_set_src(img_profile, &profile);
    lv_img_set_zoom(img_profile, PROFILE_SIZE);
    lv_img_set_pivot(img_profile, PROFILE_POS_X, PROFILE_POS_Y);
    
    /*初始页面按钮配置*/
    btn_start = lv_btn_create(scr_start);
    lv_obj_set_size(btn_start, BTN_START_W, BTN_START_H);
    lv_obj_set_pos(btn_start, BTN_START_POS_X, BTN_START_POS_Y);
    lv_obj_set_style_bg_color(btn_start, lv_color_hex(0x51d4ff), LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btn_start, btn_start_cb, LV_EVENT_CLICKED, NULL);

    /*按钮标签文字配置*/
    label_start = lv_label_create(btn_start);
    lv_obj_set_style_text_font(label_start, font_12, LV_PART_MAIN);
    lv_label_set_text(label_start, "START WORK");
    lv_obj_set_align(label_start, LV_ALIGN_CENTER);

    /*时间标签配置*/
    label_time = lv_label_create(scr_func);
    lv_obj_set_style_text_font(label_time, font_14, LV_PART_MAIN);
    // lv_label_set_text(label_time, time_buf);

    /*语音识别界面*/
    scr_listen_init();

    /*回复界面*/
    scr_respond_init();
}

void reveal_time(void)
{
    lv_label_set_text(label_time, time_buf);
}

static void led_module_init(void)
{
    obj_led_bg = lv_obj_create(scr_func);
    lv_obj_clear_flag(obj_led_bg, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(obj_led_bg, lv_obj_get_height(scr_func) / 3, lv_obj_get_height(scr_func) / 2);
    lv_obj_align(obj_led_bg, LV_ALIGN_CENTER, -100, 0);

    label_led = lv_label_create(obj_led_bg);
    lv_label_set_text(label_led, "LED");
    lv_obj_set_style_text_font(label_led, font_12, LV_STATE_DEFAULT);
    lv_obj_align(label_led, LV_ALIGN_CENTER, 0, 15);

    switch_led = lv_switch_create(obj_led_bg);
    lv_obj_set_size(switch_led, lv_obj_get_height(scr_func) / 6, lv_obj_get_height(scr_func) / 12);
    lv_obj_align(switch_led, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_event_cb(switch_led, switch_led_cb, LV_EVENT_VALUE_CHANGED, NULL);

    img_led = lv_img_create(obj_led_bg);
    lv_img_set_src(img_led, &led_img);
    lv_img_set_zoom(img_led, 50);
    lv_img_set_pivot(img_led, 8, 0);
}

static void AC_module_init(void)
{
    obj_AC_bg = lv_obj_create(scr_func);
    lv_obj_clear_flag(obj_AC_bg, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(obj_AC_bg, lv_obj_get_height(scr_func) / 3, lv_obj_get_height(scr_func) / 2);
    lv_obj_align(obj_AC_bg, LV_ALIGN_CENTER, 0, 0);

    label_AC = lv_label_create(obj_AC_bg);
    lv_label_set_text(label_AC, "AC");
    lv_obj_set_style_text_font(label_AC, font_12, LV_STATE_DEFAULT);
    lv_obj_align(label_AC, LV_ALIGN_CENTER, 0, 15);

    switch_AC = lv_switch_create(obj_AC_bg);
    lv_obj_set_size(switch_AC, lv_obj_get_height(scr_func) / 6, lv_obj_get_height(scr_func) / 12);
    lv_obj_align(switch_AC, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_event_cb(switch_AC, switch_AC_cb, LV_EVENT_VALUE_CHANGED, NULL);

    img_AC = lv_img_create(obj_AC_bg);
    lv_img_set_src(img_AC, &AC_img);
    lv_img_set_zoom(img_AC, 50);
    lv_img_set_pivot(img_AC, 8, 0);
}

static void SR_module_init(void)
{
    obj_SR_bg = lv_obj_create(scr_func);
    lv_obj_clear_flag(obj_SR_bg, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(obj_SR_bg, lv_obj_get_height(scr_func) / 3, lv_obj_get_height(scr_func) / 2);
    lv_obj_align(obj_SR_bg, LV_ALIGN_CENTER, 100, 0);

    label_SR = lv_label_create(obj_SR_bg);
    lv_label_set_text(label_SR, "SR");
    lv_obj_set_style_text_font(label_SR, font_12, LV_STATE_DEFAULT);
    lv_obj_align(label_SR, LV_ALIGN_CENTER, 0, 15);

    switch_SR = lv_switch_create(obj_SR_bg);
    lv_obj_add_state(switch_SR, LV_STATE_CHECKED);
    lv_obj_set_size(switch_SR, lv_obj_get_height(scr_func) / 6, lv_obj_get_height(scr_func) / 12);
    lv_obj_align(switch_SR, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_event_cb(switch_SR, switch_SR_cb, LV_EVENT_VALUE_CHANGED, NULL);

    img_SR = lv_img_create(obj_SR_bg);
    lv_img_set_src(img_SR, &SR_img);
    lv_img_set_zoom(img_SR, 50);
    lv_img_set_pivot(img_SR, 8, 0);
}

void screen_init(void)
{
    /*页面创建*/
    scr_module_init();
    
    /*电灯开关*/
    led_module_init();

    /*空调开关*/
    AC_module_init();

    /*语音识别开关*/
    SR_module_init();

    //TODO
    /*语音识别界面*/
    // lv_scr_load(scr_listen);

    //TODO
    /*答复界面*/
}

void AC_switch_set(uint8_t data)
{
    if(data == 0)
    {
        lv_obj_add_state(switch_AC, LV_STATE_DEFAULT);
    }
    else
    {
        lv_obj_add_state(switch_AC, LV_STATE_CHECKED);
    }
}