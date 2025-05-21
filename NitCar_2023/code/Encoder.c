#include "Encoder.h"
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
* @brief        编码器转速采样
* @param        
* @ref          
* @author       Leo
* @note         
**/
void ENCODER_RevSample(void)
{
    motorStr.EncoderValue = encoder_get_count(ENCODER_1); // 获取编码器计数
    encoder_clear_count(ENCODER_1);                       // 清空编码器计数
    //PID负反馈数据输入
    pidStr.vi_FeedBack = (float)motorStr.EncoderValue;
    
    //计算实际速度	---		m/s
    icarStr.SpeedFeedback = (float)(motorStr.EncoderValue * 3.141593f * motorStr.DiameterWheel)/ MOTOR_CONTROL_CYCLE / motorStr.EncoderLine / 1.0f / motorStr.ReductionRatio; //  m/s
    
    
    if(icarStr.SpeedFeedback > 0 && icarStr.SpeedFeedback > icarStr.SpeedMaxRecords)
        icarStr.SpeedMaxRecords = icarStr.SpeedFeedback;
        
    else if(icarStr.SpeedFeedback < 0 && -icarStr.SpeedFeedback > icarStr.SpeedMaxRecords)
        icarStr.SpeedMaxRecords = -icarStr.SpeedFeedback;
}




