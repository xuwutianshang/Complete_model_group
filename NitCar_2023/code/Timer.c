#include "timer.h"
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
* @brief        ��ʱ��TIM2��ʼ��
* @param        
* @ref          
* @author       Leo
* @note         
**/
void TIM2_Init(void)
{
    system_start();//ϵͳ��ʱ������

}


/**
* @brief        TIM2��ʱ�жϷ���
* @param        
* @ref          
* @author       Leo
* @note         
**/
void TIM2_IRQHandler(void)    //1ms����һ��
{

        GPIO_Timer();			//GPIO�����߳�
        MOTOR_Timer();			//��������߳�
        //SOC_Timer();			//�����Ƽ���߳�
        ICAR_Timer();           //���ܳ��ۺϴ����̼߳�����
        USB_Edgeboard_Timr();   //USBͨ���߳�
    

}














