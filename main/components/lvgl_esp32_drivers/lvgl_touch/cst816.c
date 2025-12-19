#include "cst816.h"
#include <esp_log.h>
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include <lvgl.h>
#else
#include <lvgl/lvgl.h>
#endif
#include "gt911.h"

#include "lvgl_i2c/i2c_manager.h"

#define TAG "CST816"

gt911_status_t cst816_status;

//TODO: handle multibyte read and refactor to just one read transaction
esp_err_t cst816_i2c_read(uint8_t slave_addr, uint16_t register_addr, uint8_t *data_buf, uint8_t len) {
    return lvgl_i2c_read(CONFIG_LV_I2C_TOUCH_PORT, slave_addr, register_addr | I2C_REG_16, data_buf, len);
}

esp_err_t gt911_i2c_write8(uint8_t slave_addr, uint16_t register_addr, uint8_t data) {
    uint8_t buffer = data;
    return lvgl_i2c_write(CONFIG_LV_I2C_TOUCH_PORT, slave_addr, register_addr | I2C_REG_16, &buffer, 1);
}





/**
  * @brief  Initialize for GT911 communication via I2C
  * @param  dev_addr: Device address on communication Bus (I2C slave address of GT911).
  * @retval None
  */
void cst816_init(uint8_t dev_addr) {
    if (!cst816_status.inited) {
        cst816_status.i2c_dev_addr = dev_addr;
        uint8_t data_buf;
        esp_err_t ret;

        ESP_LOGI(TAG, "Checking for CST816 Touch Controller");
        if ((ret = cst816_i2c_read(dev_addr, CST816_I2C_SLAVE_ADDR, &data_buf, 1) != ESP_OK))
        {
            ESP_LOGE(TAG, "Error reading from device: %s",
                        esp_err_to_name(ret));    // Only show error the first time
            return;
        }

        if ((ret = cst816_i2c_read(dev_addr, CST816_CHIP_ID, &data_buf, 1) != ESP_OK))
        {
            ESP_LOGE(TAG, "Error reading from device: %s",
                     esp_err_to_name(ret)); // Only show error the first time
            ESP_LOGE(TAG, "CST816 Chip ID: 0x%02x", data_buf);
        }

        // Read 1 bytes for Product ID in ASCII
        for (int i = 0; i < CST816_PRODUCT_ID_LEN; i++) {
            cst816_i2c_read(dev_addr, (CST816_PRODUCT_ID + i), (uint8_t *)&(cst816_status.product_id[i]), CST816_PRODUCT_ID_LEN);
        }
        ESP_LOGI(TAG, "\tProduct ID: %s", cst816_status.product_id);

        cst816_i2c_read(dev_addr, CST816_FWVERSION_ID, &data_buf, 1);
        ESP_LOGI(TAG, "\tFWVersion ID: 0x%02x", data_buf);

        cst816_i2c_read(dev_addr, CST816_X_COORD_RES_L, &data_buf, 1);
        cst816_status.max_x_coord = data_buf;
        cst816_i2c_read(dev_addr, CST816_X_COORD_RES_H, &data_buf, 1);
        cst816_status.max_x_coord |= ((uint16_t)data_buf << 8);
        ESP_LOGI(TAG, "\tX Resolution: %d", cst816_status.max_x_coord);

        cst816_i2c_read(dev_addr, CST816_Y_COORD_RES_L, &data_buf, 1);
        cst816_status.max_y_coord = data_buf;
        cst816_i2c_read(dev_addr, CST816_Y_COORD_RES_H, &data_buf, 1);
        cst816_status.max_y_coord |= ((uint16_t)data_buf << 8);
        ESP_LOGI(TAG, "\tY Resolution: %d", cst816_status.max_y_coord);
        cst816_status.inited = true;
    }
}

/**
 * @brief  Get the touch screen X and Y positions values. Ignores multi touch
 * @param  drv:
 * @param  data: Store data here
 * @retval Always false
 */
bool cst816_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    uint8_t touch_pnt_cnt;     // Number of detected touch points
    static int16_t last_x = 0; // 12bit pixel value
    static int16_t last_y = 0; // 12bit pixel value
    uint8_t data_buf;

    // 先读取触摸点数
    cst816_i2c_read(cst816_status.i2c_dev_addr, CST816_FINGER_NUM, &touch_pnt_cnt, 1);
    if (touch_pnt_cnt != 1)
    { // ignore no touch & multi touch
        data->point.x = last_x;
        data->point.y = last_y;
        data->state = LV_INDEV_STATE_REL;
        return false;
    }


    cst816_i2c_read(cst816_status.i2c_dev_addr, CST816_X_COORD_RES_L, &data_buf, 1);
    last_x = data_buf;
    cst816_i2c_read(cst816_status.i2c_dev_addr, CST816_X_COORD_RES_H, &data_buf, 1);
    last_x |= ((uint16_t)data_buf << 8);

    cst816_i2c_read(cst816_status.i2c_dev_addr, CST816_Y_COORD_RES_L, &data_buf, 1);
    last_y = data_buf;
    cst816_i2c_read(cst816_status.i2c_dev_addr, CST816_Y_COORD_RES_H, &data_buf, 1);
    last_y |= ((uint16_t)data_buf << 8);

#if CONFIG_LV_CST816_INVERT_X
    last_x = cst816_status.max_x_coord - last_x;
#endif
#if CONFIG_LV_CST816_INVERT_Y
    last_y = cst816_status.max_y_coord - last_y;
#endif
#if CONFIG_LV_CST816_SWAPXY
    int16_t swap_buf = last_x;
    last_x = last_y;
    last_y = swap_buf;
#endif
    data->point.x = last_x;
    data->point.y = last_y;
    if(touch_pnt_cnt > 0){
        data->state = LV_INDEV_STATE_PR;
        ESP_LOGI(TAG, "X=%u Y=%u", data->point.x, data->point.y);
        ESP_LOGV(TAG, "X=%u Y=%u", data->point.x, data->point.y);
    }
    else{
        data->state = LV_INDEV_STATE_REL;
    }

    return false;
}





