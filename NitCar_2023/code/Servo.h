#ifndef __SERVO_H__
#define __SERVO_H__

#include "zf_common_headfile.h"


#define  SERVO_PWM_MAX					2500						//����������PWM��180��
#define  SERVO_PWM_MIN					500							//���������СPWM��0��
#define  SERVO_PWM_MAX_L				1250						//�������ת�����ֵPWM
#define  SERVO_PWM_MAX_R				1995    						//�������ת�����ֵPWM
#define  SERVO_PWM_MIDDLE				1600						//�����ֵPWM

#define  SERVO_ANGLE_MAX				38.0f						//���

// ------------------ ���ռ�ձȼ��㷽ʽ ------------------
//
// �����Ӧ�� 0-180 ��Ƕȶ�Ӧ ��������� 0.5ms-2.5ms �ߵ�ƽ
//
// ��ô��ͬƵ���µ�ռ�ձȼ��㷽ʽ����
// PWM_DUTY_MAX/(1000/freq)*(1+Angle/180) �� 50hz ʱ���� PWM_DUTY_MAX/(1000/50)*(1+Angle/180)
//
// ��ô 100hz �� 90�ȵĴ�� ���ߵ�ƽʱ��1.5ms ��������Ϊ
// PWM_DUTY_MAX/(1000/100)*(1+90/180) = PWM_DUTY_MAX/10*1.5
//
// ------------------ ���ռ�ձȼ��㷽ʽ ------------------
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))




void SERVO_SetPwmValue(signed int pwm);
void SERVO_SetPwmValueCorrect(signed int pwm);
void SERVO_AngleControl(float angle);
#endif

//===========================================  End Of File  ===========================================//


