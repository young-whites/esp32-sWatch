/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include "lvgl_helpers.h"
#include <stdbool.h>

/*********************
 *      DEFINES 
 *********************/


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);


/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/





 /**
 * LVGL requires a buffer where it internally draws the widgets.
 * Later this buffer will passed to your display driver's `flush_cb` to copy its content to your display.
 * The buffer has to be greater than 1 display row
 *
 * There are 3 buffering configurations:
 * 1. Create ONE buffer:
 *      LVGL will draw the display's content here and writes it to your display
 *
 * 2. Create TWO buffer:
 *      LVGL will draw the display's content to a buffer and writes it your display.
 *      You should use DMA to write the buffer's content to the display.
 *      It will enable LVGL to draw the next part of the screen to the other buffer while
 *      the data is being sent form the first buffer. It makes rendering and flushing parallel.
 *
 * 3. Double buffering
 *      Set 2 screens sized buffers and set disp_drv.full_refresh = 1.
 *      This way LVGL will always provide the whole rendered screen in `flush_cb`
 *      and you only need to change the frame buffer's address.
 */
void lv_port_disp_init(void)
{

    /* LVGL使用单缓冲模式 */
    #define LV_USE_ONE_BUFFER 0
    /* LVGL使用双缓冲模式 */
    #define LV_USE_TWO_BUFFER 1
    #define LV_USE_DOUBLE_BUFFER 0

    /* 初始化LCD显示屏驱动 */
    disp_init();

    /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/

    #if LV_USE_ONE_BUFFER
    /***
     * @note 单缓冲模式
     * 在这种配置中，LVGL 使用一个缓冲区来绘制显示内容。绘制完成后，将缓冲区的内容通过 flush_cb 回调函数写入显示设备。这种方式简单*直接，但在缓冲区写入显示设备期间，LVGL 无法进行新的绘制操作，可能会导致一些延迟。
     */
    static lv_disp_draw_buf_t draw_buf_dsc_1;
    static lv_color_t buf_1[MY_DISP_HOR_RES * 10];                          /*A buffer for 10 rows*/
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES * 10);   /*Initialize the display buffer*/
    #endif

    #if LV_USE_TWO_BUFFER
    /***
     * @note 双缓冲模式
     * 在这种配置中，LVGL 使用两个缓冲区来实现双缓冲。LVGL 在一个缓冲区绘制显示内容，同时可以通过 DMA（直接内存访问）将另一个缓冲区的内容写入显示设备。这样，渲染和刷新可以并行进行，提高效率。
     */
    static lv_disp_draw_buf_t draw_buf_dsc_2;
    static lv_color_t buf_2_1[DISP_BUF_SIZE];                        /*A buffer for 10 rows*/
    static lv_color_t buf_2_2[DISP_BUF_SIZE];                        /*An other buffer for 10 rows*/
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, DISP_BUF_SIZE); /*Initialize the display buffer*/
    #endif

    #if LV_USE_DOUBLE_BUFFER
    /***
     * @note 双缓冲模式（全屏）
     * 在这种配置中，设置了两个与屏幕大小相同的缓冲区，并且设置 disp_drv.full_refresh = 1。LVGL 会将整个渲染后的屏幕内容提供给 flush_cb 回调函数，只需要切换帧缓冲区的地址即可。这种方式适用于需要频繁更新整个屏幕的应用。
     */
    static lv_disp_draw_buf_t draw_buf_dsc_3;
    static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];            /*A screen sized buffer*/
    static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES];            /*Another screen sized buffer*/
    lv_disp_draw_buf_init(&draw_buf_dsc_3, buf_3_1, buf_3_2,
                          MY_DISP_VER_RES * LV_VER_RES_MAX);   /*Initialize the display buffer*/
    #endif



    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/

    static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_driver_flush;

    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_2;

    /*Required for Example 3)*/
    //disp_drv.full_refresh = 1;

    /* Fill a memory array with a color if you have GPU.
     * Note that, in lv_conf.h you can enable GPUs that has built-in support in LVGL.
     * But if you have a different GPU you can use with this callback.*/
    //disp_drv.gpu_fill_cb = gpu_fill;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
    lvgl_driver_init();
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}



/*OPTIONAL: GPU INTERFACE*/

/*If your MCU has hardware accelerator (GPU) then you can use it to fill a memory with a color*/
//static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//                    const lv_area_t * fill_area, lv_color_t color)
//{
//    /*It's an example code which should be done by your GPU*/
//    int32_t x, y;
//    dest_buf += dest_width * fill_area->y1; /*Go to the first line*/
//
//    for(y = fill_area->y1; y <= fill_area->y2; y++) {
//        for(x = fill_area->x1; x <= fill_area->x2; x++) {
//            dest_buf[x] = color;
//        }
//        dest_buf+=dest_width;    /*Go to the next line*/
//    }
//}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
