#include "motor.h"
/*
********************************************************************************************************
*                                               ʾ������
*                                             EXAMPLE  CODE                                             
*
*                             (c) Copyright 2021; SaiShu.Lcc.; Leo
*                                 ��Ȩ����[��������Ƽ����޹�˾]
*
*               The code is for internal use only, not for commercial transactions(��Դѧϰ,��������).
*               The code ADAPTS the corresponding hardware circuit board(����ʹ��CarDo�ǿذ�), 
*               the specific details consult the professional(��ӭ��ϵ����).
*********************************************************************************************************
*/



/**
* @brief        ������PWM����
* @param        pwm��-2000~2000
* @ref          
* @author       Leo
* @note         
**/
void MOTOR_SetPwmValue(signed int pwm)
{   
    pwm = -pwm;
    if(pwm>=0)
    {
        if(pwm>MOTOR_PWM_MAX)
            pwm =MOTOR_PWM_MAX;
        
        pwm_set_duty(PWM1,pwm);
    }
    else if(pwm<0)
    {
        if(pwm<MOTOR_PWM_MIN)
            pwm=MOTOR_PWM_MIN;
        
        pwm = -pwm;

        pwm_set_duty(PWM1, pwm);
    }	
}


/**
* @brief        ����ջ��ٿ�
* @param        speed���ٶ�m/s
* @ref          
* @author       Leo
* @note         
**/
void MOTOR_ControlLoop(float speed)
{	
    if(speed > MOTOR_SPEED_MAX)
        speed = MOTOR_SPEED_MAX;
    else if(speed < -MOTOR_SPEED_MAX)
        speed = -MOTOR_SPEED_MAX;
    
    pidStr.vi_Ref = (float)(speed*MOTOR_CONTROL_CYCLE / motorStr.DiameterWheel / PI * motorStr.EncoderLine * 1.0f * motorStr.ReductionRatio);
    
    MOTOR_SetPwmValue(PID_MoveCalculate());
}


/**
* @brief        ��������߳�
* @param        
* @ref          
* @author       Leo
* @note         
**/
void MOTOR_Timer(void)
{
    motorStr.Counter++;
    if(motorStr.Counter >= 10)							    //�ٿ�:10ms
    {
        motorStr.Counter = 0;
        ENCODER_RevSample();								//����������

        if(icarStr.sprintEnable || usbStr.connected)        //ͨ�����ӻ������Բſ����ջ�������+ʡ�磩
        {
            if(motorStr.CloseLoop)
            {
                MOTOR_ControlLoop(icarStr.SpeedSet);		//�ջ��ٿ�
            }
            else//�����ٷֱȿ���
            {
                if(icarStr.SpeedSet > MOTOR_SPEED_MAX)
                    icarStr.SpeedSet = MOTOR_SPEED_MAX;
                else if(icarStr.SpeedSet < -MOTOR_SPEED_MAX)
                    icarStr.SpeedSet = -MOTOR_SPEED_MAX;
                //signed int speedRate = MOTOR_PWM_MAX/100.f*icarStr.SpeedSet; //�������ٷֱ�%
                signed int speedRate = icarStr.SpeedSet*(3500.0f);//�������ٷֱ�%
                MOTOR_SetPwmValue(speedRate);		//�����ٿ�
            }
        }
        else
        {
            MOTOR_SetPwmValue(0);
        }
       

    }
}

