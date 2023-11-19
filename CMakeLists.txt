if(ESP_PLATFORM)
    set(srcs
        "tft_driver.c"
        "ili9341/ili9341.c")

    set(includes 
        ".")

    idf_component_register(SRCS "${srcs}"
                           INCLUDE_DIRS ${includes}
                           REQUIRES mcu_port fonts)
endif()

