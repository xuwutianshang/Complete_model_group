#ifndef __USB_H__
#define __USB_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "zf_common_headfile.h"





//void USB_Edgeboard_Init(void);
void USB_Edgeboard_TransmitByte(uint8_t data);
void USB_Edgeboard_Timr(void);
void USB_Edgeboard_Handle(void);
void USB_Edgeboard_TransmitKey(uint16_t time);

//ÖÇÄÜ³µ×Ô¼ì
void USB_Edgeboard_ServoThreshold(uint8_t chanel);
void USB_Edgeboard_KeyPress(uint16_t time);
void USB_Edgeboard_BatteryInfo(void);
void USB_Edgeboard_CarSpeed(void);
void USB_Edgeboard_Selfcheck(uint8_t step);

#endif

//===========================================  End Of File  ===========================================//

