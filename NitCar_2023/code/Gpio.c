#include "gpio.h"
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




//----------------------------------------------[UNIT-���������������ж�]----------------------------------------------------------

/**
* @brief        ����A�ж���Ӧ����
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
* @brief        GPIO�߳̿�����
* @param        
* @ref          
* @author       Leo
* @note         
**/
void GPIO_Timer(void)
{
    //�ⲿ��ԭ�����жϣ����ڷ���Timer�߳���1ms��ɨ��
    if(!gpio_get_level(KEY2))   //��������
            {
                gpioStr.KeyPress = true;
                GPIO_BuzzerEnable(BuzzerDing);
            }
            else    //��������
            {
                gpioStr.KeyPress = false;
            }

    //����������
    if(buzzerStr.Enable)
    {
        buzzerStr.Counter++;
        
        if(buzzerStr.Cut<buzzerStr.Counter)
            buzzerStr.Counter = buzzerStr.Cut;
    }
    
    //LED��˸
    gpioStr.CounterLed++;
}



/**
* @brief        GPIO�߼�������
* @param        
* @ref          
* @author       Leo
* @note         
**/
void GPIO_Handle(void)
{
    //����������
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
    
    //LED����
    if(gpioStr.CounterLed > 100)	    //100ms
    {
        LED_REV;
        gpioStr.CounterLed = 0;
    }
}


/**
* @brief        ������ʹ��
* @param        buzzer������������ģʽ
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


