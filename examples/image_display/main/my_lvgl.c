#include "my_lvgl.h"
#include "lvgl.h"


#define PROFILE_SIZE        150
#define PROFILE_POS_X       170
#define PROFILE_POS_Y       0

#define BTN_START_W         150
#define BTN_START_H         30
#define BTN_START_POS_X     85
#define BTN_START_POS_Y     200



LV_IMG_DECLARE(profile);
static lv_obj_t *scr_start;
static lv_obj_t *scr_func;
static lv_obj_t *btn_start;
static lv_obj_t *label_start;
static lv_font_t *font = (lv_font_t *)&lv_font_montserrat_12;


static void btn_start_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
    {
        lv_scr_load(scr_func);
    }
}

void screen_init(void)
{
    /*创建两个页面，初始页面和功能页面*/
    scr_start = lv_obj_create(NULL);
    scr_func = lv_obj_create(NULL);

    /*禁用页面滚动*/
    lv_obj_clear_flag(scr_start, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(scr_func, LV_OBJ_FLAG_SCROLLABLE);
    
    /*设置白色背景*/
    lv_obj_set_style_bg_color(scr_start, lv_color_hex(0xffffff), LV_STATE_DEFAULT);

    /*加载初始页面*/
    lv_scr_load(scr_start);

    /*初始页面图像显示*/
    lv_obj_t *img_profile = lv_img_create(scr_start);
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
    lv_obj_set_style_text_font(label_start, font, LV_PART_MAIN);
    lv_label_set_text(label_start, "START WORK");
    lv_obj_set_align(label_start, LV_ALIGN_CENTER);
}