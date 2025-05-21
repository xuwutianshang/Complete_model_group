#ifndef __SERVO_H__
#define __SERVO_H__

#include "zf_common_headfile.h"


#define  SERVO_PWM_MAX					2500						//舵机方向最大PWM：180°
#define  SERVO_PWM_MIN					500							//舵机方向最小PWM：0°
#define  SERVO_PWM_MAX_L				1250						//舵机左向转角最大值PWM
#define  SERVO_PWM_MAX_R				1995    						//舵机右向转角最大值PWM
#define  SERVO_PWM_MIDDLE				1600						//舵机中值PWM

#define  SERVO_ANGLE_MAX				38.0f						//舵机

// ------------------ 舵机占空比计算方式 ------------------
//
// 舵机对应的 0-180 活动角度对应 控制脉冲的 0.5ms-2.5ms 高电平
//
// 那么不同频率下的占空比计算方式就是
// PWM_DUTY_MAX/(1000/freq)*(1+Angle/180) 在 50hz 时就是 PWM_DUTY_MAX/(1000/50)*(1+Angle/180)
//
// 那么 100hz 下 90度的打角 即高电平时间1.5ms 计算套用为
// PWM_DUTY_MAX/(1000/100)*(1+90/180) = PWM_DUTY_MAX/10*1.5
//
// ------------------ 舵机占空比计算方式 ------------------
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))




void SERVO_SetPwmValue(signed int pwm);
void SERVO_SetPwmValueCorrect(signed int pwm);
void SERVO_AngleControl(float angle);
#endif

//===========================================  End Of File  ===========================================//


