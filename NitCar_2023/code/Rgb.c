#include "Rgb.h" 
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
* @brief        RGB�Ƴ�ʼ��
* @param        
* @ref          
* @author       Leo
* @note         
**/
void RGB_Init(void)
{
//    Delay_Ms(10);
//
//    RGB_SetColorToColor(RGB_COLOR_GREEN,RGB_COLOR_RED);  //��ʼ����Ч
//    rgbStr.lastColor = RGB_COLOR_RED;
}


/**
* @brief        ������ʱ
* @param        
* @ref          
* @author       Leo
* @note         
**/
void RGB_Delay2us(void)
{
//	Delay_Us(2);
}
void RGB_Delay05us()
{
//	unsigned char i;
//	for(i=0; i<1; i++);
}

/**
* @brief        ����0�ź�(Byte)
* @param        
* @ref          
* @author       Leo
* @note         
**/
void RGB_SendLow(void)  		
{ 
//    PBout(3) = 1;
//    RGB_Delay05us();
//    PBout(3) = 0;
//    RGB_Delay2us();
} 


/**
* @brief        ����1�ź�(Byte)
* @param        
* @ref          
* @author       Leo
* @note         
**/
void RGB_SendHigh(void)  		
{ 
//    PBout(3) = 1;
//    RGB_Delay2us();
//    PBout(3) = 0;
//    RGB_Delay05us();
} 	


/**
* @brief        ��Ч��λ
* @param        
* @ref          
* @author       Leo
* @note         
**/
void RGB_Reset(void) 
{ 
//    PBout(3) = 0;
//    Delay_Us(60);
//    PBout(3) = 1;
//    PBout(3) = 0;
}	  


/**
* @brief        ����һ�ֵ�Ч
* @param        
* @ref          
* @author       Leo
* @note         
**/
void RGB_SetLight(unsigned long dat)
{	
//    //����GRB ��˳���� RGB
//    unsigned long colorG,colorR;
//    colorG = dat & 0xFF0000;        //G
//    colorR = dat & 0x00FF00;        //R
//
//    dat &= 0x0000FF;
//    dat |= colorG>>8;
//    dat |= colorR<<8;
//
//    for(int i=0; i<24; i++)
//	{
//		if(0x800000 == (dat & 0x800000) )
//            RGB_SendHigh();
//		else
//            RGB_SendLow();
//		dat<<=1;							//����һλ
//	}
}

/**
* @brief        ���ö��ֵ�Ч
* @param        
* @ref          
* @author       Leo
* @note         
**/
void RGB_SetAllLight(unsigned long *colorBuff)
{
//	unsigned char j;
//
//	for(j=0; j<RGB_NUM; j++)
//	{
//		RGB_SetLight(colorBuff[j]);  // j / 0
//	}
//	RGB_Reset();
}


/**
* @brief        ���õƹ���ɫ
* @param        
* @ref          
* @author       Leo
* @note         
**/
void RGB_SetAllColor(unsigned long color)
{
//	unsigned char j;
//
//	for(j=0; j<RGB_NUM; j++)
//	{
//		RGB_SetLight(color);  // j / 0
//	}
//	RGB_Reset();
}


/**
* @brief        ��ɫ�����㷨
* @param        
* @ref          
* @author       Leo
* @note         ��� <= 2
**/
uint32_t RGB_SetColorToColor(unsigned long color0, unsigned long color1)
{
//	unsigned char Red0, Green0, Blue0;  // ��ʼ��ԭɫ
//	unsigned char Red1, Green1, Blue1;  // �����ԭɫ
//	int			  RedMinus, GreenMinus, BlueMinus;	// ��ɫ�color1 - color0��
//	unsigned char NStep; 							// ��Ҫ����
//	float		  RedStep, GreenStep, BlueStep;		// ��ɫ����ֵ
//	unsigned long color;							// ���ɫ
//	unsigned char i;
//
//	// �� �� �� ��ԭɫ�ֽ�
//	Red0   = color0>>8;
//	Green0 = color0>>16;
//	Blue0  = color0;
//
//	Red1   = color1>>8;
//	Green1 = color1>>16;
//	Blue1  = color1;
//
//	// ������Ҫ���ٲ���ȡ��ֵ�����ֵ��
//	RedMinus   = Red1 - Red0;
//	GreenMinus = Green1 - Green0;
//	BlueMinus  = Blue1 - Blue0;
//
//	NStep = ( abs(RedMinus) > abs(GreenMinus) ) ? abs(RedMinus):abs(GreenMinus);
//	NStep = ( NStep > abs(BlueMinus) ) ? NStep:abs(BlueMinus);
//
//	// �������ɫ����ֵ
//	RedStep   = (float)RedMinus   / NStep;
//	GreenStep = (float)GreenMinus / NStep;
//	BlueStep  = (float)BlueMinus  / NStep;
//
//	// ���俪ʼ
//	for(i=0; i<NStep; i++)
//	{
//		Red1   = Red0   + (int)(RedStep   * i);
//		Green1 = Green0 + (int)(GreenStep * i);
//		Blue1  = Blue0  + (int)(BlueStep  * i);
//
//		color  = Green1<<16 | Red1<<8 | Blue1; 	                // �ϳ�  �̺���
//        for(int n=0;n<RGB_NUM;n++)
//            rgbStr.buffColors[n] = color;
//		RGB_SetAllLight(rgbStr.buffColors);			    // ���
//		Delay_Ms(1);											// �����ٶ�
//	}
//	// �������
//
//	return color;
}
