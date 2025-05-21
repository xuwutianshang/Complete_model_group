/*
 * ExternStruct.h
 *
 *  Created on: 2023年6月28日
 *      Author: Soler
 */

#ifndef __ExternStruct_h
#define __ExternStruct_h


#include "zf_common_headfile.h"



#define RGB_NUM                     7               //有多少颗WS2812D级联
#define USB_FRAME_LENMIN             4                   //USB通信序列字节最短长度
#define USB_FRAME_LENMAX             30                  //USB通信序列字节最长长度

/*------------------------------此处补充定义------------------------------*/
//typedef unsigned           char       uint8_t;
//typedef unsigned short     int        uint16_t;
//typedef unsigned           int        uint32_t;
typedef   uint32_t   u32;   ///32位
typedef   uint16_t   u16;   ///16位
typedef   uint8_t     u8;   ///8位
//typedef   short int    int16_t;
typedef union
{
    uint8_t U8_Buff[2];
    uint16_t U16;
    int16_t S16;
}Bint16_Union;

typedef union
{
    uint8_t U8_Buff[4];
    float Float;
    unsigned long U32;
}Bint32_Union;


/*------------------------------此处补充定义------------------------------*/

/*------------------------------此处为全局结构体------------------------------*/

typedef struct
{
    bool receiveStart;                                      //数据接收开始
    uint8_t receiveIndex;                                   //接收序列
    bool receiveFinished;                                   //数据队列接收并校验完成
    uint8_t receiveBuff[USB_FRAME_LENMAX];                  //USB接收队列：临时接收
    uint8_t receiveBuffFinished[USB_FRAME_LENMAX];          //USB接收队列：校验成功
    uint16_t counter;                                       //计数器
    uint16_t counterDrop;                                   //掉线计数器

    uint16_t counterSend;                                   //自检数据发送计数器
    bool connected;                                         //上位机通信连接状态
    bool inspectorEnable;                                   //智能汽车自检软件连接使能
}UsbStruct;



/**
* @brief    电量计相关
**/
typedef struct
{
    unsigned char UsbOnline;                                //USB插入状态
    unsigned int Capacity;                                  //电量
    unsigned int voltage;                                   //电压值
    uint32_t Counter;                                       //计数器
}SocStruct;


/**
* @brief    舵机相关
**/
typedef struct
{
    uint16_t thresholdMiddle;                   //舵机中值PWM
    uint16_t thresholdLeft;                     //舵机左向转角最大值PWM
    uint16_t thresholdRight;                    //舵机右向转角最大值PWM
}ServoStruct;



/**
* @brief    RGB灯相关
**/
typedef struct
{
    unsigned long buffColors[RGB_NUM];
    unsigned long lastColor;
}RgbStruct;


/**
* @brief    PID相关
**/
typedef struct
{
    float vi_Ref;                       //速度PID，速度设定值
    float vi_FeedBack;                  //速度PID，速度反馈值
    float vi_PreError;                  //速度PID，速度误差,vi_Ref - vi_FeedBack
    float vi_PreDerror;                 //速度PID，前一次，速度误差之差，d_error-PreDerror;
    float v_Kp;                         //比例系数，Kp = Kp
    float v_Ki;                         //积分系数，Ki = Kp * ( T / Ti )
    float v_Kd;                         //微分系数，Kd = KP * Td * T
    float vl_PreU;                      //PID输出值
}PIDStruct;



/**
* @brief    电机相关
**/
typedef struct
{
    float ReductionRatio ;                      //电机减速比
    float EncoderLine ;                         //编码器线数=光栅数16*4
    signed int EncoderValue;                    //编码器实时速度
    float DiameterWheel;                        //轮子直径：mm
    bool CloseLoop;                             //开环模式
    uint16_t Counter;                           //线程计数器
}MotorStruct;




/**
* @brief    智能车自检步骤
**/
typedef enum
{
    Selfcheck_None = 0,             //开始测试
    Selfcheck_MotorA,               //电机正转启动
    Selfcheck_MotorB,               //电机正转采样
    Selfcheck_MotorC,               //电机反转启动
    Selfcheck_MotorD,               //电机反转采样
    Selfcheck_MotorE,               //电机闭环正传启动
    Selfcheck_MotorF,               //电机闭环正传采样
    Selfcheck_MotorG,               //电机闭环反转启动
    Selfcheck_MotorH,               //电机闭环反转采样
    Selfcheck_ServoA,               //舵机测试A
    Selfcheck_Com,                  //通信测试
    Selfcheck_Buzzer,               //蜂鸣器测试
    Selfcheck_RgbLed,               //灯效测试
    Selfcheck_Key,                  //按键测试
    Selfcheck_Finish                //测试完成
}SelfcheckEnum;

/**
* @brief    智能车相关
**/
typedef struct                              //[智能车驱动主板]
{
    float Voltage;                          //电池电压
    uint8_t Electricity;                    //电池电量百分比：0~100
    float SpeedSet;                         //电机目标速度：m/s
    float SpeedFeedback;                    //电机模型实测速度：m/s
    float SpeedMaxRecords;                  //测试记录最高速
    uint16_t ServoPwmSet;                   //舵机PWM设置

    uint16_t counterKeyA;                   //按键模式A计数器
    bool keyPressed;                        //按键按下
    bool sprintEnable;                      //闭环冲刺使能
    uint16_t counterSprint;                 //闭环冲刺时间
    uint16_t errorCode;                     //错误代码

    bool selfcheckEnable;                   //智能车自检使能
    uint16_t counterSelfcheck;              //自检计数器
    uint8_t timesSendStep;                  //发送超时数据次数
    uint16_t counterModuleCheck;            //自检计数器
    SelfcheckEnum selfcheckStep;            //自检步骤
    uint8_t speedSampleStep;                //速度采样步骤
}IcarStruct;


/**
* @brief    按键和LED相关
**/
typedef struct
{
    bool KeyPress;                      //按键输入-B
    uint16_t CounterLed;                //LED闪烁计数器
}GpioStruct;




/**
* @brief    蜂鸣器相关
**/
typedef struct
{
    bool Enable;                        //使能标志
    uint16_t Times;                     //鸣叫次数
    uint16_t Counter;                   //计数器
    uint16_t Cut;                       //间隔时间
    bool Silent;                        //是否禁用蜂鸣器
}BuzzerStruct;

extern UsbStruct usbStr;
extern SocStruct socStr;
extern ServoStruct servoStr;
extern RgbStruct rgbStr;
extern PIDStruct pidStr;
extern MotorStruct motorStr;
extern IcarStruct icarStr;
extern GpioStruct gpioStr;
extern BuzzerStruct buzzerStr;



extern bool flashSaveEnable;

//测试用
extern float KC;


/*------------------------------此处为全局结构体------------------------------*/

void Externstruct_Init(void);


#endif /* CODE_EXTERNSTRUCT_H_ */
