#include "gpio.h"
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




//----------------------------------------------[UNIT-按键及数字输入中断]----------------------------------------------------------

/**
* @brief        按键A中断响应函数
* @param        
* @ref          
* @author       Leo
* @note         
**/
//void EXTI2_IRQHandler(void)
//{
//    if(EXTI_GetITStatus(EXTI_Line2)==1)
//    {
//
//    }
//    EXTI_ClearITPendingBit(EXTI_Line2);
//}

//------------------------------------------------[END]-------------------------------------------------------------




/**
* @brief        GPIO线程控制器
* @param        
* @ref          
* @author       Leo
* @note         
**/
void GPIO_Timer(void)
{
    //这部分原本在中断，现在放在Timer线程做1ms的扫描
    if(!gpio_get_level(KEY2))   //按键按下
            {
                gpioStr.KeyPress = true;
                GPIO_BuzzerEnable(BuzzerDing);
            }
            else    //按键弹起
            {
                gpioStr.KeyPress = false;
            }

    //蜂鸣器控制
    if(buzzerStr.Enable)
    {
        buzzerStr.Counter++;
        
        if(buzzerStr.Cut<buzzerStr.Counter)
            buzzerStr.Counter = buzzerStr.Cut;
    }
    
    //LED闪烁
    gpioStr.CounterLed++;
}



/**
* @brief        GPIO逻辑处理函数
* @param        
* @ref          
* @author       Leo
* @note         
**/
void GPIO_Handle(void)
{
    //蜂鸣器控制
    if(buzzerStr.Enable && !buzzerStr.Silent)
    {
        if(buzzerStr.Times<=0)
        {
            BUZZER_OFF;
            buzzerStr.Enable = false;
            return;
        }
        else if(buzzerStr.Cut<=buzzerStr.Counter)
        {
            BUZZER_ON;
            buzzerStr.Times--;          
            buzzerStr.Counter = 0;
        }
    }
    else
        BUZZER_OFF;
    
    //LED控制
    if(gpioStr.CounterLed > 100)	    //100ms
    {
        LED_REV;
        gpioStr.CounterLed = 0;
    }
}


/**
* @brief        蜂鸣器使能
* @param        buzzer：蜂鸣器工作模式
* @ref          
* @author       Leo
* @note         
**/
void GPIO_BuzzerEnable(BuzzerEnum buzzer)
{
	switch(buzzer)
	{
		case BuzzerOk:
			buzzerStr.Cut = 70;		    //70ms
			buzzerStr.Enable = true;
			buzzerStr.Times = 4;
			break;
		
		case BuzzerWarnning:
			buzzerStr.Cut = 100;		//100ms
			buzzerStr.Enable = true;
			buzzerStr.Times = 10;
			break;
		
		case BuzzerSysStart:
			buzzerStr.Cut = 60;			//60ms
			buzzerStr.Enable = true;
			buzzerStr.Times = 6;  
			break;
        
        case BuzzerDing:
			buzzerStr.Cut = 30;			//30ms
			buzzerStr.Enable = true;
			buzzerStr.Times = 2;  
			break;
        
        case BuzzerFinish:
			buzzerStr.Cut = 200;		//200ms
			buzzerStr.Enable = true;
			buzzerStr.Times = 6;  
			break;
	}
	
    buzzerStr.Counter = 0;
}


