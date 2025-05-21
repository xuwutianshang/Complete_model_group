#ifndef __GPIO_H__
#define __GPIO_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/

#include "zf_common_headfile.h"

/**
* @brief    ��������Ч
**/
typedef enum
{
    BuzzerOk = 0,                       //ȷ����ʾ��
    BuzzerWarnning,                     //������ʾ��
    BuzzerSysStart,                     //������ʾ��
    BuzzerDing,                         //��=====(������*)
    BuzzerFinish,                       //������ʾ��
}BuzzerEnum;

void GPIO_Initialize(void);
void GPIO_Timer(void);
void GPIO_Handle(void);
void GPIO_BuzzerEnable(BuzzerEnum buzzer);

#endif

//===========================================  End Of File  ===========================================//

