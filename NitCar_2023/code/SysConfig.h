/*
 * SysConfig.h
 *
 *  Created on: 2023年6月29日
 *      Author: Soler
 */

#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H

#include "zf_common_headfile.h"


/*------------------------------此处为通讯配置------------------------------*/
//串口通信(Usb.h)
#define USB_FRAME_HEAD               0x42                //USB通信序列帧头


#define USB_ADDR_HEART               0x00                //监测软件心跳
#define USB_ADDR_CONTROL             0x01                //智能车控制
#define USB_ADDR_SPEEDMODE           0x02                //速控模式
#define USB_ADDR_SERVOTHRESHOLD      0x03                //舵机阈值
#define USB_ADDR_BUZZER              0x04                //蜂鸣器音效
#define USB_ADDR_LIGHT               0x05                //LED灯效
#define USB_ADDR_KEYINPUT            0x06                //按键输入
#define USB_ADDR_BATTERY             0x07                //电池信息

//仅限自检软件通信使用
#define USB_ADDR_INSPECTOR           0x0A                //智能车自检软件连接心跳
#define USB_ADDR_SELFCHECK           0x0B                //智能车自检开始
#define USB_ADDR_SPEEDBACK           0x08                //车速信息反馈：m/s

/*------------------------------此处为通讯配置------------------------------*/
/*------------------------------此处为参数配置------------------------------*/


//电机模型配置(motor.h)
#define  MOTOR_PWM_MAX              9500        //OCR=95%,禁止满占空比输出，造成MOS损坏
#define  MOTOR_PWM_MIN              -9500       //OCR=95%
#define  MOTOR_SPEED_MAX            1.5f       //电机最大转速(m/s) (0.017,8.04)
//#define  PI                         3.141593f   //π

#define M_ENCODERLINE       512.0f  //编码器线数=光栅数16*4
#define M_REDUCTIONRATIO    2.7f    //电机减速比
#define M_ENCODERVALUE      0       //编码器实时速度
#define M_DIAMETERWHEEL     0.064f  //轮子直径:m
#define M_CLOSELOOP         true    //默认闭环模式
#define MOTOR_CONTROL_CYCLE        0.01f       //电机控制周期T：10ms

#define TEST_SPEED 0.1f



//PID参数配置(Pid.h)
#define VV_DEADLINE             2                       //速度PID，设置死区范围，消抖，静止强硬程度
#define VV_MAX                  20.0f                   //积分过饱和用
#define VV_MIN                 -20.0f                   //积分过饱和用
#define PID_VKP                 1.9f                    //PID标定值
#define PID_VKI                 0.3f                    //PID标定值
#define PID_VKD                 0.02f                   //PID标定值


/*------------------------------此处为参数配置----------------------------------*/
/*------------------------------此处为硬件管脚配置------------------------------*/
//编码器配置(Encoder.h)
// 接入正交编码器连接 1
//      定时器              TIM2
//      A                   ENCODER_1_A 宏定义的引脚 默认 P33_7
//      B                   ENCODER_1_B 宏定义的引脚 默认 P33_6
#define ENCODER_1                   (TIM2_ENCODER)
#define ENCODER_1_A                 (TIM2_ENCODER_CH1_P33_7)
#define ENCODER_1_B                 (TIM2_ENCODER_CH2_P33_6)


//LED、按钮和开关(Gpio.h)
#define BUZZER_PIN              (P33_10)

#define LED1                    (P20_9)
#define LED2                    (P20_8)
//#define LED3                    (P21_5)
//#define LED4                    (P21_4)
#define KEY1                    (P22_0)
#define KEY2                    (P22_1)
#define KEY3                    (P22_2)
#define KEY4                    (P22_3)
#define SWITCH1                 (P33_11)
#define SWITCH2                 (P33_12)


//驱动控制脚(motor.h)
#define DIR1                (P02_5)
#define PWM1                (ATOM0_CH4_P02_4)

//舵机控制脚(Servo.h)
#define SERVO_MOTOR_PWM             (ATOM1_CH1_P33_9)                           // 定义主板上舵机对应引脚
#define SERVO_MOTOR_FREQ            (100)                                       // 定义主板上舵机频率  请务必注意范围 50-300

#define SERVO_MOTOR_L_MAX           (50)                                       // 定义主板上舵机活动范围 角度
#define SERVO_MOTOR_R_MAX           (150)                                       // 定义主板上舵机活动范围 角度


//串口配置(Usb.h)
#define USB_UART_INDEX         (UART_0)                                    // 无线串口对应使用的串口号
#define USB_UART_BUAD_RATE     (115200)                                    // 无线串口对应使用的串口波特率
#define USB_UART_TX_PIN        (UART0_TX_P14_0)                            // 无线串口对应模块的 TX 要接到单片机的 RX
#define USB_UART_RX_PIN        (UART0_RX_P14_1)                            // 无线串口对应模块的 RX 要接到单片机的 TX


/*------------------------------此处为硬件管脚配置------------------------------*/

/*------------------------------此处为宏函数------------------------------*/
#define LED_ON          (gpio_set_level(LED1, GPIO_LOW))
#define LED_OFF         (gpio_set_level(LED1, GPIO_HIGH))
#define LED_REV         (gpio_get_level(LED1))

#define BUZZER_ON        (gpio_set_level(BUZZER_PIN, GPIO_HIGH))
#define BUZZER_OFF       (gpio_set_level(BUZZER_PIN, GPIO_LOW))
#define BUZZER_REV       (gpio_get_level(BUZZER_PIN))
/*------------------------------此处为宏函数------------------------------*/


void Delay_Ms(uint32 t);
void GPIO_Initialize(void);
void MOTOR_Init(void);
void ENCODER_Init(void);
void PID_Init(void);
void USB_Edgeboard_Init(void);
void SERVO_Init(void);
#endif /* CODE_SYSCONFIG_H_ */
