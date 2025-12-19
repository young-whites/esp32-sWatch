cmake_minimum_required(VERSION 3.16)


file(GLOB_RECURSE SOURCES ./*.c)

idf_component_register(
    SRCS  ${SOURCES}
    INCLUDE_DIRS "."
    REQUIRES lvgl
             lvgl_esp32_drivers
             main
)



# 设置工程名称 - 建议放在CMakeLists.txt的末尾
project(eWatch_lvgl_porting)





