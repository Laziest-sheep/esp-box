idf_component_register(
    SRCS
        "image_display.c"
        "profile.c"
        "my_lvgl.c"
        "led_img.c"
        "SR_img.c"
        "AC_img.c"
        "listen_img.c"
    INCLUDE_DIRS
        "")

spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)
