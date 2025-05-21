#include "Pid.h"
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
* @brief        PID�ٿ�ģ��
* @param        
* @ref          
* @author       Leo
* @note         
**/
signed int PID_MoveCalculate(void)
{    
    PIDStruct *pp = &pidStr;
    float  error, d_error, dd_error, I_error;
			 
    error = pp->vi_Ref - pp->vi_FeedBack;
    d_error = error - pp->vi_PreError;
    dd_error = d_error - pp->vi_PreDerror;          
        
    pp->vi_PreError = error;		                     
    pp->vi_PreDerror = d_error;
	
    if((error < VV_DEADLINE) && (error > -VV_DEADLINE ))
    {

    }
    else								
    { 
//PID���ְ��ͣ���Ҫʱ�����ã�����
				I_error = pp -> v_Ki * error;
				KC=I_error;
				if(I_error >= (VV_MAX/5))
				{
				I_error = VV_MAX/5;
				}
				else if(I_error <= (VV_MIN/5))
				{
				I_error = VV_MIN/5;
				}
        pp->vl_PreU += (pp -> v_Kp * d_error + I_error + pp->v_Kd*dd_error);
	    pp->vl_PreU += (pp -> v_Kp * d_error + pp -> v_Ki * error + pp->v_Kd*dd_error);
    } 

		//pp->vl_PreU = pp->vl_PreU;
    if( pp->vl_PreU >= MOTOR_PWM_MAX )
    {
        pp->vl_PreU = MOTOR_PWM_MAX;
    }
    else if( pp->vl_PreU <= MOTOR_PWM_MIN )	
    {
        pp->vl_PreU = MOTOR_PWM_MIN;
    }
                                             
    return (pp->vl_PreU);
} 





