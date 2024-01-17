idf_component_register(
    SRCS
        "image_display.c"
        "profile.c"
        "my_lvgl.c"
    INCLUDE_DIRS
        "")

spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)
