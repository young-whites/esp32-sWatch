#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "bsp_sys.h"


// 启用普通按键功能 -- 自定义软件定时器的状态机
#define USE_GENERAL_KEY  0
#if USE_GENERAL_KEY
#define		KEY_NUM			(2)		// 按键数量
//------------------------------------------------------------------------
typedef	enum
{
    KeyPower_PRESS= (0x01),
    KeyDown_PRESS,
}KEY_Val_TypeDef;
//------------------------------------------------------------------------
typedef	enum {					    // 按键事件类型
    KEY_Evt_Press   = (0x80),		// 按下
    KEY_Evt_Release = (0x40),		// 松开
    KEY_Evt_Long2S  = (0x20),		// 长按2s
    KEY_Evt_Long4S  = (0x10),		// 长按4s
}KEY_Evt_TypeDef;
//------------------------------------------------------------------------

void KEY_Scan(void);
void KEY_DrvScan(void);
uint8_t KEY_Read(void);
void KEY_Write(uint8_t value);
void KeyTimer_Init(void);
#endif /* USE_GENERAL_KEY */

void bsp_key_init(void);


#endif /* __BSP_KEY_H */
