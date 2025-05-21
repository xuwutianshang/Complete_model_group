#include "Rgb.h" 
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
* @brief        RGB灯初始化
* @param        
* @ref          
* @author       Leo
* @note         
**/
void RGB_Init(void)
{
//    Delay_Ms(10);
//
//    RGB_SetColorToColor(RGB_COLOR_GREEN,RGB_COLOR_RED);  //初始化灯效
//    rgbStr.lastColor = RGB_COLOR_RED;
}


/**
* @brief        特殊延时
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
* @brief        发送0信号(Byte)
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
* @brief        发送1信号(Byte)
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
* @brief        灯效复位
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
* @brief        设置一种灯效
* @param        
* @ref          
* @author       Leo
* @note         
**/
void RGB_SetLight(unsigned long dat)
{	
//    //调整GRB 的顺序至 RGB
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
//		dat<<=1;							//左移一位
//	}
}

/**
* @brief        设置多种灯效
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
* @brief        设置灯光颜色
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
* @brief        颜色渐变算法
* @param        
* @ref          
* @author       Leo
* @note         误差 <= 2
**/
uint32_t RGB_SetColorToColor(unsigned long color0, unsigned long color1)
{
//	unsigned char Red0, Green0, Blue0;  // 起始三原色
//	unsigned char Red1, Green1, Blue1;  // 结果三原色
//	int			  RedMinus, GreenMinus, BlueMinus;	// 颜色差（color1 - color0）
//	unsigned char NStep; 							// 需要几步
//	float		  RedStep, GreenStep, BlueStep;		// 各色步进值
//	unsigned long color;							// 结果色
//	unsigned char i;
//
//	// 绿 红 蓝 三原色分解
//	Red0   = color0>>8;
//	Green0 = color0>>16;
//	Blue0  = color0;
//
//	Red1   = color1>>8;
//	Green1 = color1>>16;
//	Blue1  = color1;
//
//	// 计算需要多少步（取差值的最大值）
//	RedMinus   = Red1 - Red0;
//	GreenMinus = Green1 - Green0;
//	BlueMinus  = Blue1 - Blue0;
//
//	NStep = ( abs(RedMinus) > abs(GreenMinus) ) ? abs(RedMinus):abs(GreenMinus);
//	NStep = ( NStep > abs(BlueMinus) ) ? NStep:abs(BlueMinus);
//
//	// 计算出各色步进值
//	RedStep   = (float)RedMinus   / NStep;
//	GreenStep = (float)GreenMinus / NStep;
//	BlueStep  = (float)BlueMinus  / NStep;
//
//	// 渐变开始
//	for(i=0; i<NStep; i++)
//	{
//		Red1   = Red0   + (int)(RedStep   * i);
//		Green1 = Green0 + (int)(GreenStep * i);
//		Blue1  = Blue0  + (int)(BlueStep  * i);
//
//		color  = Green1<<16 | Red1<<8 | Blue1; 	                // 合成  绿红蓝
//        for(int n=0;n<RGB_NUM;n++)
//            rgbStr.buffColors[n] = color;
//		RGB_SetAllLight(rgbStr.buffColors);			    // 输出
//		Delay_Ms(1);											// 渐变速度
//	}
//	// 渐变结束
//
//	return color;
}
