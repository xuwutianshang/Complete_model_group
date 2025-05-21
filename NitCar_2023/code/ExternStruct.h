/*
 * ExternStruct.h
 *
 *  Created on: 2023��6��28��
 *      Author: Soler
 */

#ifndef __ExternStruct_h
#define __ExternStruct_h


#include "zf_common_headfile.h"



#define RGB_NUM                     7               //�ж��ٿ�WS2812D����
#define USB_FRAME_LENMIN             4                   //USBͨ�������ֽ���̳���
#define USB_FRAME_LENMAX             30                  //USBͨ�������ֽ������

/*------------------------------�˴����䶨��------------------------------*/
//typedef unsigned           char       uint8_t;
//typedef unsigned short     int        uint16_t;
//typedef unsigned           int        uint32_t;
typedef   uint32_t   u32;   ///32λ
typedef   uint16_t   u16;   ///16λ
typedef   uint8_t     u8;   ///8λ
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


/*------------------------------�˴����䶨��------------------------------*/

/*------------------------------�˴�Ϊȫ�ֽṹ��------------------------------*/

typedef struct
{
    bool receiveStart;                                      //���ݽ��տ�ʼ
    uint8_t receiveIndex;                                   //��������
    bool receiveFinished;                                   //���ݶ��н��ղ�У�����
    uint8_t receiveBuff[USB_FRAME_LENMAX];                  //USB���ն��У���ʱ����
    uint8_t receiveBuffFinished[USB_FRAME_LENMAX];          //USB���ն��У�У��ɹ�
    uint16_t counter;                                       //������
    uint16_t counterDrop;                                   //���߼�����

    uint16_t counterSend;                                   //�Լ����ݷ��ͼ�����
    bool connected;                                         //��λ��ͨ������״̬
    bool inspectorEnable;                                   //���������Լ��������ʹ��
}UsbStruct;



/**
* @brief    ���������
**/
typedef struct
{
    unsigned char UsbOnline;                                //USB����״̬
    unsigned int Capacity;                                  //����
    unsigned int voltage;                                   //��ѹֵ
    uint32_t Counter;                                       //������
}SocStruct;


/**
* @brief    ������
**/
typedef struct
{
    uint16_t thresholdMiddle;                   //�����ֵPWM
    uint16_t thresholdLeft;                     //�������ת�����ֵPWM
    uint16_t thresholdRight;                    //�������ת�����ֵPWM
}ServoStruct;



/**
* @brief    RGB�����
**/
typedef struct
{
    unsigned long buffColors[RGB_NUM];
    unsigned long lastColor;
}RgbStruct;


/**
* @brief    PID���
**/
typedef struct
{
    float vi_Ref;                       //�ٶ�PID���ٶ��趨ֵ
    float vi_FeedBack;                  //�ٶ�PID���ٶȷ���ֵ
    float vi_PreError;                  //�ٶ�PID���ٶ����,vi_Ref - vi_FeedBack
    float vi_PreDerror;                 //�ٶ�PID��ǰһ�Σ��ٶ����֮�d_error-PreDerror;
    float v_Kp;                         //����ϵ����Kp = Kp
    float v_Ki;                         //����ϵ����Ki = Kp * ( T / Ti )
    float v_Kd;                         //΢��ϵ����Kd = KP * Td * T
    float vl_PreU;                      //PID���ֵ
}PIDStruct;



/**
* @brief    ������
**/
typedef struct
{
    float ReductionRatio ;                      //������ٱ�
    float EncoderLine ;                         //����������=��դ��16*4
    signed int EncoderValue;                    //������ʵʱ�ٶ�
    float DiameterWheel;                        //����ֱ����mm
    bool CloseLoop;                             //����ģʽ
    uint16_t Counter;                           //�̼߳�����
}MotorStruct;




/**
* @brief    ���ܳ��Լ첽��
**/
typedef enum
{
    Selfcheck_None = 0,             //��ʼ����
    Selfcheck_MotorA,               //�����ת����
    Selfcheck_MotorB,               //�����ת����
    Selfcheck_MotorC,               //�����ת����
    Selfcheck_MotorD,               //�����ת����
    Selfcheck_MotorE,               //����ջ���������
    Selfcheck_MotorF,               //����ջ���������
    Selfcheck_MotorG,               //����ջ���ת����
    Selfcheck_MotorH,               //����ջ���ת����
    Selfcheck_ServoA,               //�������A
    Selfcheck_Com,                  //ͨ�Ų���
    Selfcheck_Buzzer,               //����������
    Selfcheck_RgbLed,               //��Ч����
    Selfcheck_Key,                  //��������
    Selfcheck_Finish                //�������
}SelfcheckEnum;

/**
* @brief    ���ܳ����
**/
typedef struct                              //[���ܳ���������]
{
    float Voltage;                          //��ص�ѹ
    uint8_t Electricity;                    //��ص����ٷֱȣ�0~100
    float SpeedSet;                         //���Ŀ���ٶȣ�m/s
    float SpeedFeedback;                    //���ģ��ʵ���ٶȣ�m/s
    float SpeedMaxRecords;                  //���Լ�¼�����
    uint16_t ServoPwmSet;                   //���PWM����

    uint16_t counterKeyA;                   //����ģʽA������
    bool keyPressed;                        //��������
    bool sprintEnable;                      //�ջ����ʹ��
    uint16_t counterSprint;                 //�ջ����ʱ��
    uint16_t errorCode;                     //�������

    bool selfcheckEnable;                   //���ܳ��Լ�ʹ��
    uint16_t counterSelfcheck;              //�Լ������
    uint8_t timesSendStep;                  //���ͳ�ʱ���ݴ���
    uint16_t counterModuleCheck;            //�Լ������
    SelfcheckEnum selfcheckStep;            //�Լ첽��
    uint8_t speedSampleStep;                //�ٶȲ�������
}IcarStruct;


/**
* @brief    ������LED���
**/
typedef struct
{
    bool KeyPress;                      //��������-B
    uint16_t CounterLed;                //LED��˸������
}GpioStruct;




/**
* @brief    ���������
**/
typedef struct
{
    bool Enable;                        //ʹ�ܱ�־
    uint16_t Times;                     //���д���
    uint16_t Counter;                   //������
    uint16_t Cut;                       //���ʱ��
    bool Silent;                        //�Ƿ���÷�����
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

//������
extern float KC;


/*------------------------------�˴�Ϊȫ�ֽṹ��------------------------------*/

void Externstruct_Init(void);


#endif /* CODE_EXTERNSTRUCT_H_ */
