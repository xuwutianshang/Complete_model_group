#include "motor.h"
/*
********************************************************************************************************
*                                               示例代码
*                                             EXAMPLE  CODE                                             
*
*                             (c) Copyright 2021; SaiShu.Lcc.; Leo
*                                 版权所属[北京赛曙科技有限公司]
*
*               The code is for internal use only, not for commercial transactions(开源学习,请勿商用).
*               The code ADAPTS the corresponding hardware circuit board(代码使用CarDo智控板), 
*               the specific details consult the professional(欢迎联系我们).
*********************************************************************************************************
*/



/**
* @brief        电机输出PWM设置
* @param        pwm：-2000~2000
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
* @brief        电机闭环速控
* @param        speed：速度m/s
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
* @brief        电机控制线程
* @param        
* @ref          
* @author       Leo
* @note         
**/
void MOTOR_Timer(void)
{
    motorStr.Counter++;
    if(motorStr.Counter >= 10)							    //速控:10ms
    {
        motorStr.Counter = 0;
        ENCODER_RevSample();								//编码器采样

        if(icarStr.sprintEnable || usbStr.connected)        //通信连接或电机测试才开启闭环（保护+省电）
        {
            if(motorStr.CloseLoop)
            {
                MOTOR_ControlLoop(icarStr.SpeedSet);		//闭环速控
            }
            else//开环百分比控制
            {
                if(icarStr.SpeedSet > MOTOR_SPEED_MAX)
                    icarStr.SpeedSet = MOTOR_SPEED_MAX;
                else if(icarStr.SpeedSet < -MOTOR_SPEED_MAX)
                    icarStr.SpeedSet = -MOTOR_SPEED_MAX;
                //signed int speedRate = MOTOR_PWM_MAX/100.f*icarStr.SpeedSet; //开环：百分比%
                signed int speedRate = icarStr.SpeedSet*(3500.0f);//开环：百分比%
                MOTOR_SetPwmValue(speedRate);		//开环速控
            }
        }
        else
        {
            MOTOR_SetPwmValue(0);
        }
       

    }
}

