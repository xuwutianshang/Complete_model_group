#include "Encoder.h"
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
* @brief        ������ת�ٲ���
* @param        
* @ref          
* @author       Leo
* @note         
**/
void ENCODER_RevSample(void)
{
    motorStr.EncoderValue = encoder_get_count(ENCODER_1); // ��ȡ����������
    encoder_clear_count(ENCODER_1);                       // ��ձ���������
    //PID��������������
    pidStr.vi_FeedBack = (float)motorStr.EncoderValue;
    
    //����ʵ���ٶ�	---		m/s
    icarStr.SpeedFeedback = (float)(motorStr.EncoderValue * 3.141593f * motorStr.DiameterWheel)/ MOTOR_CONTROL_CYCLE / motorStr.EncoderLine / 1.0f / motorStr.ReductionRatio; //  m/s
    
    
    if(icarStr.SpeedFeedback > 0 && icarStr.SpeedFeedback > icarStr.SpeedMaxRecords)
        icarStr.SpeedMaxRecords = icarStr.SpeedFeedback;
        
    else if(icarStr.SpeedFeedback < 0 && -icarStr.SpeedFeedback > icarStr.SpeedMaxRecords)
        icarStr.SpeedMaxRecords = -icarStr.SpeedFeedback;
}




