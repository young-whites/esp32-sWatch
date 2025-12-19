# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)
# 指定ESP-IDF的工程cmake文件路径
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# 添加额外的组件目录，对于每个指定的组件目录，构建系统会递归查找其中的子目录，并将每个子目录视为一个单独的组件
set(EXTRA_COMPONENT_DIRS
    main/components/lvgl
    main/components/lvgl_esp32_drivers
    main/components/lvgl_porting
    main/bsp_applications/macBSP
    main/bsp_applications/macSYS
)

# 组件的注册：每个组件需要有自己的CMakeLists.txt文件来定义其构建规则


# 禁用格式相关的警告
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-format")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format")


# 设置工程名称
# 该函数在ESP-IDF构件中具有特殊意义，他会触发一系列的构建配置和初始化操作
# 如果该函数调用位置不正确，会导致构建系统的全局配置不正确
project(eWatch)