/*
 * SysConfig.c
 *
 *  Created on: 2023��6��29��
 *      Author: Soler
 */

#include "SysConfig.h"


void Delay_Ms(uint32 t)
{
    system_delay_ms(t);
}
/**
* @brief        GPIO�����ʼ��
* @param
* @ref
* @author       Leo
* @note         ���裺������ x1  ״̬LED x1  �������� x1
**/
void GPIO_Initialize(void)
{

    //������IO��ʼ��
    gpio_init(BUZZER_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL); // ��ʼ�� BUZZER_PIN ��� Ĭ�ϵ͵�ƽ �������ģʽ
    //LED��IO��ʼ��
    gpio_init(LED1, GPO, GPIO_LOW, GPO_PUSH_PULL);          // ��ʼ�� LED1 ��� Ĭ�ϸߵ�ƽ �������ģʽ
    gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // ��ʼ�� LED2 ��� Ĭ�ϸߵ�ƽ �������ģʽ
    //gpio_init(LED3, GPO, GPIO_LOW, GPO_PUSH_PULL);          // ��ʼ�� LED3 ��� Ĭ�ϸߵ�ƽ �������ģʽ
    //gpio_init(LED4, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // ��ʼ�� LED4 ��� Ĭ�ϸߵ�ƽ �������ģʽ
    //����IO��ʼ��
    gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY1 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY2 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY3 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY4 ���� Ĭ�ϸߵ�ƽ ��������
    //ʹ�ܰ����ⲿ�ж�


    //BuzzerInit
    buzzerStr.Counter = 0;
    buzzerStr.Cut = 0;
    buzzerStr.Enable = false;
    buzzerStr.Times = 0;
    buzzerStr.Silent = false;
}
/**
* @brief        ��������ʼ��
* @param
* @ref
* @author       Leo
* @note
**/
void ENCODER_Init(void)
{
    encoder_quad_init(ENCODER_1, ENCODER_1_A, ENCODER_1_B);    // ��ʼ��������ģ�������� �������������ģʽ

}
/**
* @brief        ������Ƴ�ʼ��
* @param
* @ref
* @author       Leo
* @note
**/
void MOTOR_Init(void)
{
    gpio_init(DIR1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(PWM1, 10000, 0);                                                   // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0

    MOTOR_SetPwmValue(0);
    //���ģ�ͳ�ʼ��
    motorStr.EncoderLine = M_ENCODERLINE;                          //����������=��դ��16*4
    motorStr.ReductionRatio = M_REDUCTIONRATIO;                         //������ٱ�
    motorStr.EncoderValue = M_ENCODERVALUE;
    motorStr.DiameterWheel = M_DIAMETERWHEEL;//68cm                  //����ֱ��:m
    motorStr.CloseLoop = M_CLOSELOOP;                              //Ĭ�ϱջ�ģʽ
}




/**
* @brief        ������Ƴ�ʼ��
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
* @brief        PID������ʼ��
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
* @brief        USB/UART��ʼ��
* @param
* @ref
* @author       Leo
* @note
**/
void USB_Edgeboard_Init(void)
{

    uart_init (USB_UART_INDEX, USB_UART_BUAD_RATE, USB_UART_TX_PIN, USB_UART_RX_PIN);   // ��ʼ������
    uart_rx_interrupt(USB_UART_INDEX, 1);
    //USB���ݳ�ʼ��
    usbStr.counter = 0;
    usbStr.receiveFinished = false;
    usbStr.receiveStart = false;
    usbStr.receiveIndex = 0;
    usbStr.connected = false;
    usbStr.inspectorEnable = false;
}
