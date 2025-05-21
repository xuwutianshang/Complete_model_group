/*
 * SysConfig.h
 *
 *  Created on: 2023��6��29��
 *      Author: Soler
 */

#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H

#include "zf_common_headfile.h"


/*------------------------------�˴�ΪͨѶ����------------------------------*/
//����ͨ��(Usb.h)
#define USB_FRAME_HEAD               0x42                //USBͨ������֡ͷ


#define USB_ADDR_HEART               0x00                //����������
#define USB_ADDR_CONTROL             0x01                //���ܳ�����
#define USB_ADDR_SPEEDMODE           0x02                //�ٿ�ģʽ
#define USB_ADDR_SERVOTHRESHOLD      0x03                //�����ֵ
#define USB_ADDR_BUZZER              0x04                //��������Ч
#define USB_ADDR_LIGHT               0x05                //LED��Ч
#define USB_ADDR_KEYINPUT            0x06                //��������
#define USB_ADDR_BATTERY             0x07                //�����Ϣ

//�����Լ����ͨ��ʹ��
#define USB_ADDR_INSPECTOR           0x0A                //���ܳ��Լ������������
#define USB_ADDR_SELFCHECK           0x0B                //���ܳ��Լ쿪ʼ
#define USB_ADDR_SPEEDBACK           0x08                //������Ϣ������m/s

/*------------------------------�˴�ΪͨѶ����------------------------------*/
/*------------------------------�˴�Ϊ��������------------------------------*/


//���ģ������(motor.h)
#define  MOTOR_PWM_MAX              9500        //OCR=95%,��ֹ��ռ�ձ���������MOS��
#define  MOTOR_PWM_MIN              -9500       //OCR=95%
#define  MOTOR_SPEED_MAX            1.5f       //������ת��(m/s) (0.017,8.04)
//#define  PI                         3.141593f   //��

#define M_ENCODERLINE       512.0f  //����������=��դ��16*4
#define M_REDUCTIONRATIO    2.7f    //������ٱ�
#define M_ENCODERVALUE      0       //������ʵʱ�ٶ�
#define M_DIAMETERWHEEL     0.064f  //����ֱ��:m
#define M_CLOSELOOP         true    //Ĭ�ϱջ�ģʽ
#define MOTOR_CONTROL_CYCLE        0.01f       //�����������T��10ms

#define TEST_SPEED 0.1f



//PID��������(Pid.h)
#define VV_DEADLINE             2                       //�ٶ�PID������������Χ����������ֹǿӲ�̶�
#define VV_MAX                  20.0f                   //���ֹ�������
#define VV_MIN                 -20.0f                   //���ֹ�������
#define PID_VKP                 1.9f                    //PID�궨ֵ
#define PID_VKI                 0.3f                    //PID�궨ֵ
#define PID_VKD                 0.02f                   //PID�궨ֵ


/*------------------------------�˴�Ϊ��������----------------------------------*/
/*------------------------------�˴�ΪӲ���ܽ�����------------------------------*/
//����������(Encoder.h)
// ������������������ 1
//      ��ʱ��              TIM2
//      A                   ENCODER_1_A �궨������� Ĭ�� P33_7
//      B                   ENCODER_1_B �궨������� Ĭ�� P33_6
#define ENCODER_1                   (TIM2_ENCODER)
#define ENCODER_1_A                 (TIM2_ENCODER_CH1_P33_7)
#define ENCODER_1_B                 (TIM2_ENCODER_CH2_P33_6)


//LED����ť�Ϳ���(Gpio.h)
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


//�������ƽ�(motor.h)
#define DIR1                (P02_5)
#define PWM1                (ATOM0_CH4_P02_4)

//������ƽ�(Servo.h)
#define SERVO_MOTOR_PWM             (ATOM1_CH1_P33_9)                           // ���������϶����Ӧ����
#define SERVO_MOTOR_FREQ            (100)                                       // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300

#define SERVO_MOTOR_L_MAX           (50)                                       // ���������϶�����Χ �Ƕ�
#define SERVO_MOTOR_R_MAX           (150)                                       // ���������϶�����Χ �Ƕ�


//��������(Usb.h)
#define USB_UART_INDEX         (UART_0)                                    // ���ߴ��ڶ�Ӧʹ�õĴ��ں�
#define USB_UART_BUAD_RATE     (115200)                                    // ���ߴ��ڶ�Ӧʹ�õĴ��ڲ�����
#define USB_UART_TX_PIN        (UART0_TX_P14_0)                            // ���ߴ��ڶ�Ӧģ��� TX Ҫ�ӵ���Ƭ���� RX
#define USB_UART_RX_PIN        (UART0_RX_P14_1)                            // ���ߴ��ڶ�Ӧģ��� RX Ҫ�ӵ���Ƭ���� TX


/*------------------------------�˴�ΪӲ���ܽ�����------------------------------*/

/*------------------------------�˴�Ϊ�꺯��------------------------------*/
#define LED_ON          (gpio_set_level(LED1, GPIO_LOW))
#define LED_OFF         (gpio_set_level(LED1, GPIO_HIGH))
#define LED_REV         (gpio_get_level(LED1))

#define BUZZER_ON        (gpio_set_level(BUZZER_PIN, GPIO_HIGH))
#define BUZZER_OFF       (gpio_set_level(BUZZER_PIN, GPIO_LOW))
#define BUZZER_REV       (gpio_get_level(BUZZER_PIN))
/*------------------------------�˴�Ϊ�꺯��------------------------------*/


void Delay_Ms(uint32 t);
void GPIO_Initialize(void);
void MOTOR_Init(void);
void ENCODER_Init(void);
void PID_Init(void);
void USB_Edgeboard_Init(void);
void SERVO_Init(void);
#endif /* CODE_SYSCONFIG_H_ */
