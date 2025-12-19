#include <stdio.h>
#include "bsp_sys.h"



/**********************
 *   APPLICATION MAIN
 **********************/
void app_main() 
{

    /* If you want to use a task to create the graphic, you NEED to create a Pinned task
     * Otherwise there can be problem such as memory corruption and so on.
     * NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0 */
    xTaskCreatePinnedToCore(gui_task, "gui_Task", 4096*4, NULL, GUI_TASK_PRIORITY, NULL, ESP32_CORE_1_FOR_APP);

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
