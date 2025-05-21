#include "timer.h"
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
* @brief        定时器TIM2初始化
* @param        
* @ref          
* @author       Leo
* @note         
**/
void TIM2_Init(void)
{
    system_start();//系统定时器启动

}


/**
* @brief        TIM2定时中断服务
* @param        
* @ref          
* @author       Leo
* @note         
**/
void TIM2_IRQHandler(void)    //1ms触发一次
{

        GPIO_Timer();			//GPIO外设线程
        MOTOR_Timer();			//电机控制线程
        //SOC_Timer();			//电量计监测线程
        ICAR_Timer();           //智能车综合处理线程计数器
        USB_Edgeboard_Timr();   //USB通信线程
    

}














