cmake_minimum_required(VERSION 3.16)


file(GLOB_RECURSE mac_bsp_srcs
        "./*.[c|h]"
)

# 设置自定义的头文件目录路径 
set(MAC_BSP_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)

idf_component_register(
    SRCS  ${mac_bsp_srcs}
    INCLUDE_DIRS ${MAC_BSP_INCLUDE_DIRS}
    REQUIRES main
)
