#include "my_lvgl.h"
#include "lvgl.h"



LV_IMG_DECLARE(profile);


// img对象设置png图片自适应显示
static void lv_obj_img_png_set_zoom(lv_obj_t * obj_img, uint32_t obj_width, uint32_t obj_height)
{
    lv_img_t *img = (lv_img_t *)obj_img;
    uint32_t img_width = 0, img_height = 0, zoom_factor = 0;
   
    img_width = img->w;
    img_height = img->h;
 
    if (img_width != 0 && img_height != 0)
    {
        uint32_t y_a= obj_height * img_width;   
        uint32_t x_b= obj_width * img_height;
 
        if (x_b >= y_a)
        {
            if (img_height >= obj_height)
            {
                uint32_t x = obj_height * 256;
                zoom_factor = x / img_height;
                lv_img_set_zoom(obj_img, zoom_factor);
            }
        }
        else
        {
            if (img_width > obj_width)
            {
                uint32_t x = obj_width * 256;
                zoom_factor = x / img_width;
                lv_img_set_zoom(obj_img, zoom_factor);
            }
        }
    }
}
 
static lv_style_t background_style;
static lv_style_t profile_style;
static lv_obj_t *background;
void screen_init(void)
{
    background = lv_obj_create(lv_scr_act());
    lv_obj_set_style_bg_color(background, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_size(background, 320, 240);


    lv_obj_t *img_profile = lv_img_create(background);
    lv_img_set_src(img_profile, &profile);
    lv_img_set_zoom(img_profile, 128);
    // lv_obj_img_png_set_zoom(img_profile, 100, 100);


}