#ifndef __SMARTCAR_H__
#define __SMARTCAR_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "zf_common_headfile.h"


/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/






void ICAR_Init(void);
void ICAR_Timer(void);
void ICAR_Handle(void);
void ICAR_Reboot(void);

//×Ô¼ìÏà¹Ø
void ICAR_Selfcheck(void);
void ICAR_SelfcheckControl(uint8_t step);
float ICAR_SpeedSample(void);
bool ICAR_ServoCheck(void);
bool ICAR_BuzzerCheck(void);
void ICAR_RgbCheck(void);
void ICAR_SortFloat(float *buff, uint8_t start, uint8_t len);
float CMATH_AbsFloat(float data);


#endif

//===========================================  End Of File  ===========================================//


