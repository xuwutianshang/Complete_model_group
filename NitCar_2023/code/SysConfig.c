/*
 * SysConfig.c
 *
 *  Created on: 2023年6月29日
 *      Author: Soler
 */

#include "SysConfig.h"


void Delay_Ms(uint32 t)
{
    system_delay_ms(t);
}
/**
* @brief        GPIO外设初始化
* @param
* @ref
* @author       Leo
* @note         外设：蜂鸣器 x1  状态LED x1  按键输入 x1
**/
void GPIO_Initialize(void)
{

    //蜂鸣器IO初始化
    gpio_init(BUZZER_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL); // 初始化 BUZZER_PIN 输出 默认低电平 推挽输出模式
    //LED灯IO初始化
    gpio_init(LED1, GPO, GPIO_LOW, GPO_PUSH_PULL);          // 初始化 LED1 输出 默认高电平 推挽输出模式
    gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // 初始化 LED2 输出 默认高电平 推挽输出模式
    //gpio_init(LED3, GPO, GPIO_LOW, GPO_PUSH_PULL);          // 初始化 LED3 输出 默认高电平 推挽输出模式
    //gpio_init(LED4, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // 初始化 LED4 输出 默认高电平 推挽输出模式
    //按键IO初始化
    gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY1 输入 默认高电平 上拉输入
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY2 输入 默认高电平 上拉输入
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY3 输入 默认高电平 上拉输入
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY4 输入 默认高电平 上拉输入
    //使能按键外部中断


    //BuzzerInit
    buzzerStr.Counter = 0;
    buzzerStr.Cut = 0;
    buzzerStr.Enable = false;
    buzzerStr.Times = 0;
    buzzerStr.Silent = false;
}
/**
* @brief        编码器初始化
* @param
* @ref
* @author       Leo
* @note
**/
void ENCODER_Init(void)
{
    encoder_quad_init(ENCODER_1, ENCODER_1_A, ENCODER_1_B);    // 初始化编码器模块与引脚 正交解码编码器模式

}
/**
* @brief        电机控制初始化
* @param
* @ref
* @author       Leo
* @note
**/
void MOTOR_Init(void)
{
    gpio_init(DIR1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // GPIO 初始化为输出 默认上拉输出高
    pwm_init(PWM1, 10000, 0);                                                   // PWM 通道初始化频率 17KHz 占空比初始为 0

    MOTOR_SetPwmValue(0);
    //电机模型初始化
    motorStr.EncoderLine = M_ENCODERLINE;                          //编码器线数=光栅数16*4
    motorStr.ReductionRatio = M_REDUCTIONRATIO;                         //电机减速比
    motorStr.EncoderValue = M_ENCODERVALUE;
    motorStr.DiameterWheel = M_DIAMETERWHEEL;//68cm                  //轮子直径:m
    motorStr.CloseLoop = M_CLOSELOOP;                              //默认闭环模式
}




/**
* @brief        舵机控制初始化
* @param
* @ref
* @author       Leo
* @note
**/
void SERVO_Init(void)
{

    servoStr.thresholdLeft =  SERVO_PWM_MAX_L;
    servoStr.thresholdMiddle = SERVO_PWM_MIDDLE;
    servoStr.thresholdRight = SERVO_PWM_MAX_R;
    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, 0);
//    SERVO_SetPwmValue(SERVO_PWM_MIDDLE);
//    Delay_Ms(5000);
//    SERVO_SetPwmValue(SERVO_PWM_MAX_L);
//    Delay_Ms(5000);
//    SERVO_SetPwmValue(SERVO_PWM_MIDDLE);
//    Delay_Ms(5000);
//    SERVO_SetPwmValue(SERVO_PWM_MAX_R);
    SERVO_SetPwmValue(servoStr.thresholdMiddle);
}



/**
* @brief        PID参数初始化
* @param
* @ref
* @author       Leo
* @note
**/
void PID_Init(void)
{
    pidStr.vi_Ref = 0 ;
    pidStr.vi_FeedBack = 0 ;
    pidStr.vi_PreError = 0 ;
    pidStr.vi_PreDerror = 0 ;
    pidStr.v_Kp = PID_VKP;
    pidStr.v_Ki = PID_VKI;
    pidStr.v_Kd = PID_VKD;
    pidStr.vl_PreU = 0;
}

/**
* @brief        USB/UART初始化
* @param
* @ref
* @author       Leo
* @note
**/
void USB_Edgeboard_Init(void)
{

    uart_init (USB_UART_INDEX, USB_UART_BUAD_RATE, USB_UART_TX_PIN, USB_UART_RX_PIN);   // 初始化串口
    uart_rx_interrupt(USB_UART_INDEX, 1);
    //USB数据初始化
    usbStr.counter = 0;
    usbStr.receiveFinished = false;
    usbStr.receiveStart = false;
    usbStr.receiveIndex = 0;
    usbStr.connected = false;
    usbStr.inspectorEnable = false;
}
