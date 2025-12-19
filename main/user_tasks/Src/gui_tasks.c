#include "gui_tasks.h"






#define LV_TICK_PERIOD_MS 1

lv_ui lvgl_guider_ui; // Pointer to the UI structure, defined in lvgl_ui.h

/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
SemaphoreHandle_t xGuiSemaphore;

void gui_task(void *pvParameter) 
{

    (void) pvParameter;

    xGuiSemaphore = xSemaphoreCreateMutex();

    lv_init();

    /* Initialize the display driver */
    lv_port_disp_init();

    
    /* Register an input device when enabled on the menuconfig */
#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = touch_driver_read;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);
#endif

    setup_ui(&lvgl_guider_ui); // Initialize the UI, defined in lvgl_ui.h

    while (1) {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
       }
    }

    vTaskDelete(NULL);

}









