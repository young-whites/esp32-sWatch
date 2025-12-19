#ifndef __BSP_SYS_H
#define __BSP_SYS_H

// 板载外设驱动头文件------------------------------------------------------------------------
#include "driver/gpio.h"
#include "driver/uart.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "soc/soc_caps.h"
#include "esp_log.h"
#include <esp_err.h>

// lvgl配置相关头文件------------------------------------------------------------------------
#include "lvgl.h"
#include "lvgl_helpers.h"
#include "lv_port_disp.h"



// 标准库相关头文件--------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// 轻量级TCP/IP协议栈相关头文件--------------------------------------------------------------
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

// Wifi配置相关头文件------------------------------------------------------------------------
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_system.h"
#include "esp_netif.h"

// MQTT配置相关头文件------------------------------------------------------------------------
#include "mqtt_client.h"

// FreeRTOS相关头文件------------------------------------------------------------------------
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"


// ESP32相关头文件--------------------------------------------------------------------------
#include "esp_timer.h"
#include "esp_freertos_hooks.h"


//自定义头文件------------------------------------------------------------------------------
#include "bsp_bmp280.h"
#include "bsp_mpu6050.h"
#include "bsp_key.h"
#include "gui_tasks.h"
#include "gui_guider.h"
#include "bsp_hwtimer.h"


//-----------------------------------------------------------------------------------------
// ESP32的应用核
#define ESP32_CORE_1_FOR_APP 1

// ESP32的任务优先级宏
#define GUI_TASK_PRIORITY       0

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define RESET   "\033[0m"

#endif /* __BSP_SYS_H */
