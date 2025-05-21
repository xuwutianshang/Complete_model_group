#ifndef __PWM_H__
#define __PWM_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "zf_common_headfile.h"

/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/







//void MOTOR_Init(void);
void MOTOR_SetPwmValue(signed int pwm);
void MOTOR_ControlLoop(float speed);
void MOTOR_Timer(void);


//===========================================  End Of File  ===========================================//
#endif


