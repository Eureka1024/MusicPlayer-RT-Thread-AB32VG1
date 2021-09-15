/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-15     Eureka1024       the first version
 */
#ifndef APPLICATIONS_OLED_IIC_H_
#define APPLICATIONS_OLED_IIC_H_

#include "rtthread.h"
#include <rtdevice.h>
//#include "stdlib.h"
#define OLED_MODE 0
#define SIZE 8
#define XLevelL     0x00
#define XLevelH     0x10
#define Max_Column  128
#define Max_Row     64
#define Brightness  0xFF
#define X_WIDTH     128
#define Y_WIDTH     64
//---- OLED IIC 端口定义----------------
#define SDA_PIN rt_pin_get("PE.2")
#define SCL_PIN rt_pin_get("PE.3")

#define OLED_SCLK_Clr() rt_pin_write(SCL_PIN, PIN_LOW)
#define OLED_SCLK_Set() rt_pin_write(SCL_PIN, PIN_HIGH)

#define OLED_SDIN_Clr() rt_pin_write(SDA_PIN, PIN_LOW)
#define OLED_SDIN_Set() rt_pin_write(SDA_PIN, PIN_HIGH)

#define OLED_CMD  0 //写命令
#define OLED_DATA 1 //写数据

//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p,uint8_t Char_Size);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
//void Delay_50ms(unsigned int Del_50ms);
//void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);

void IIC_Wait_Ack();

#endif /* APPLICATIONS_OLED_IIC_H_ */
