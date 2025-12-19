#include "bsp_hwtimer.h"
#include "driver/timer.h"





/***
 *  @note ESP32硬件定时器说明
 *        ESP32内部有2个硬件定时器组，每个组包含两个通用硬件定时器，总共4个定时器
 *        这些定时器都是64位的通用定时器，基于16位预分频器和64位自动重载的上下计数器
 * 
 *  @brief 定时器组分为TIMER_GROUP_0和TIMER_GROUP_1，每个组有TIMER_0和TIMER_1两个定时器实例
 **/
static void IRAM_ATTR timer_group_isr_callback(void *arg);
#define TIMER_1MS_ALARM_VALUE 80000 // 80MHz / 1000ms = 80000 ticks
void hw_timer_init(void)
{
    timer_config_t timer_config = {
        .divider = 80, // 1 second = 80,000,000 ticks
        .counter_dir = TIMER_COUNT_UP,
        .counter_en = TIMER_PAUSE,
        .alarm_en = TIMER_ALARM_EN,
        .auto_reload = true
    };
    // Initialize the timer with the specified configuration
    timer_init(TIMER_GROUP_0, TIMER_0, &timer_config);
    // Set the timer counter value to 0
    timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0);
    // Set the timer alarm value to trigger every 1ms
    timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, TIMER_1MS_ALARM_VALUE);
    // Enable the timer interrupt
    timer_enable_intr(TIMER_GROUP_0, TIMER_0);
    // Register the timer interrupt callback function
    timer_isr_callback_add(TIMER_GROUP_0, TIMER_0, timer_group_isr_callback, NULL, 0);
    // Start the timer
    timer_start(TIMER_GROUP_0, TIMER_0);
}







static void IRAM_ATTR timer_group_isr_callback(void *arg)
{


}















