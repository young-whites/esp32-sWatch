#ifndef __CST816_H
#define __CST816_H




#include <stdint.h>
#include <stdbool.h>
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CST816_I2C_SLAVE_ADDR   0x15

#define CST816_PRODUCT_ID_LEN   1

/* Register Map of CST816 */
#define CST816_CHIP_ID          0xA7
#define CST816_PRODUCT_ID       0xA8
#define CST816_FWVERSION_ID     0xA9
#define CST816_X_COORD_RES_L    0x04
#define CST816_X_COORD_RES_H    0x03
#define CST816_Y_COORD_RES_L    0x06
#define CST816_Y_COORD_RES_H    0x05
#define CST816_FINGER_NUM       0x02


  typedef struct
  {
    bool inited;
    char product_id[CST816_PRODUCT_ID_LEN];
    uint16_t max_x_coord;
    uint16_t max_y_coord;
    uint8_t i2c_dev_addr;
} cst816_status_t;

/**
  * @brief  Initialize for CST816 communication via I2C
  * @param  dev_addr: Device address on communication Bus (I2C slave address of CST816).
  * @retval None
  */
void cst816_init(uint8_t dev_addr);

/**
  * @brief  Get the touch screen X and Y positions values. Ignores multi touch
  * @param  drv:
  * @param  data: Store data here
  * @retval Always false
  */
bool cst816_read(lv_indev_drv_t *drv, lv_indev_data_t *data);

#ifdef __cplusplus
}
#endif

#endif // __CST816_H
