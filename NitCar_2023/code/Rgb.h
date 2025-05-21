#ifndef __RGB_H__
#define __RGB_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "zf_common_headfile.h"

/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/
#define RGB_NUM                     7	            //�ж��ٿ�WS2812D����
#define RGB_COLOR_WHITE             0xFFFFFF	    //��ɫ 
#define RGB_COLOR_BLACK             0x000000	    //��ɫ
#define RGB_COLOR_RED               0xFF0000	    //��ɫ
#define RGB_COLOR_GREEN             0x00FF00	    //��ɫ
#define RGB_COLOR_BLUE              0x0000FF	    //��ɫ




void RGB_Init(void);
void RGB_SetAllColor(unsigned long color);
uint32_t RGB_SetColorToColor(unsigned long color0, unsigned long color1);

#endif

