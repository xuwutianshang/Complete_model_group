#ifndef __GPIO_H__
#define __GPIO_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/

#include "zf_common_headfile.h"

/**
* @brief    蜂鸣器音效
**/
typedef enum
{
    BuzzerOk = 0,                       //确认提示音
    BuzzerWarnning,                     //报警提示音
    BuzzerSysStart,                     //开机提示音
    BuzzerDing,                         //叮=====(￣▽￣*)
    BuzzerFinish,                       //结束提示音
}BuzzerEnum;

void GPIO_Initialize(void);
void GPIO_Timer(void);
void GPIO_Handle(void);
void GPIO_BuzzerEnable(BuzzerEnum buzzer);

#endif

//===========================================  End Of File  ===========================================//

