cmake_minimum_required(VERSION 3.16)



file(GLOB_RECURSE boot_srcs
        "./bsp_applications/macSYS/Src/*.c"
        "./bsp_applications/macBSP/Src/*.c"
        "./gui_guider/*.c"
        "./gui_guider/custom/*.c"
        "./gui_guider/generated/*.c"
        "./user_tasks/Src/*.c"
)

# 设置自定义的头文件目录路径 
set(MY_INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/main
        ${CMAKE_SOURCE_DIR}/main/bsp_applications/macSYS/Inc
        ${CMAKE_SOURCE_DIR}/main/bsp_applications/macBSP/Inc
        ${CMAKE_SOURCE_DIR}/main/gui_guider
        ${CMAKE_SOURCE_DIR}/main/gui_guider/custom
        ${CMAKE_SOURCE_DIR}/main/gui_guider/generated
        ${CMAKE_SOURCE_DIR}/main/gui_guider/generated/guider_customer_fonts
        ${CMAKE_SOURCE_DIR}/main/gui_guider/generated/guider_fonts
        ${CMAKE_SOURCE_DIR}/main/gui_guider/generated/images
        ${CMAKE_SOURCE_DIR}/main/user_tasks/Inc
)


idf_component_register(
        SRCS    "main.c"
                ${boot_srcs}

        INCLUDE_DIRS    
                "."
                ${MY_INCLUDE_DIRS}
)


# 设置工程名称 - 建议放在CMakeLists.txt的末尾
project(eWatch_main)