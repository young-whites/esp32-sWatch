cmake_minimum_required(VERSION 3.16)

# 使用递归通配的方式，收集当前组件目录下所有子目录中的 .c 文件，存入变量 SOURCES
file(GLOB_RECURSE SOURCES ./*.c)


idf_component_register(
    SRCS  ${SOURCES}        # 要编译的源文件列表
    INCLUDE_DIRS "."        # 公共头文件目录（可添加多个，如 "include" "src"）
    
    REQUIRES lvgl
             lvgl_esp32_drivers
             main
)



# 设置工程名称 - 建议放在CMakeLists.txt的末尾
project(eWatch_lvgl_porting)





