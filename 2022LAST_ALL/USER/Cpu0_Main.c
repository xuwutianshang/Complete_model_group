/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            main
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ3184284598)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        ADS v1.2.2
 * @Target core     TC264D
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-3-23
 ********************************************************************************************************************/

#include "headfile.h"
#include "stdio.h"
#include "stdlib.h"
#include "isr.h"

#pragma section all "cpu0_dsram"

char uart_buff;
int t=0;
int error;
int a,c,b,d,PWMA,PWMB;
int PWM_MID=722;
int PWM_MAX=922;
int PWM_MIN=522;
int last_error=0;
int kp=6;
int kd=1;
uint16 Volt;
char *p;
uint16 speed;

uint16 duty;
extern int16 encoder;
extern char USART1_RX_BUF[200];
extern char USART0_RX_BUF[200];

//���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��


//���̵��뵽���֮��Ӧ��ѡ�й���Ȼ����refreshˢ��һ��֮���ٱ���
//����Ĭ������Ϊ�ر��Ż��������Լ��һ�����ѡ��properties->C/C++ Build->Setting
//Ȼ�����Ҳ�Ĵ������ҵ�C/C++ Compiler->Optimization->Optimization level�������Ż��ȼ�
//һ��Ĭ���½����Ĺ��̶���Ĭ�Ͽ�2���Ż�����˴��Ҳ��������Ϊ2���Ż�

//����TCϵ��Ĭ���ǲ�֧���ж�Ƕ�׵ģ�ϣ��֧���ж�Ƕ����Ҫ���ж���ʹ��enableInterrupts();�������ж�Ƕ��
//�򵥵�˵ʵ���Ͻ����жϺ�TCϵ�е�Ӳ���Զ�������disableInterrupts();���ܾ���Ӧ�κε��жϣ������Ҫ�����Լ��ֶ�����enableInterrupts();�������жϵ���Ӧ��

//���尴������
#define KEY1    P22_0
#define KEY2    P22_1
//#define KEY3    P22_2
//#define KEY4    P22_3

//����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
//uint8 key3_status = 1;
//uint8 key4_status = 1;

//��һ�ο���״̬����
uint8 key1_last_status;
uint8 key2_last_status;
//uint8 key3_last_status;
//uint8 key4_last_status;

//���ر�־λ
uint8 key1_flag;
uint8 key2_flag;
//uint8 key3_flag;
//uint8 key4_flag;

uint8 test1,test2,test3,test4;
uint16 duty;
uint16 target;
int core0_main(void)
{
    disableInterrupts();

    get_clk();//��ȡʱ��Ƶ��  ��ر���
    //�û��ڴ˴����ø��ֳ�ʼ��������
    gtm_pwm_init(ATOM0_CH4_P02_4, 17*1000, 5000);//ATOM 0ģ���ͨ��4 ʹ��P02_4�������PWM  PWMƵ��50HZ  ռ�ձȰٷ�֮0/GTM_ATOM0_PWM_DUTY_MAX*100  GTM_ATOM0_PWM_DUTY_MAX�궨����zf_gtm_pwm.h
    gtm_pwm_init(ATOM0_CH5_P02_5, 17*1000, 5000);
    gtm_pwm_init(ATOM0_CH6_P02_6, 17*1000, 5000);
    gtm_pwm_init(ATOM0_CH7_P02_7, 17*1000, 5000);

    gtm_pwm_init(ATOM1_CH1_P33_9, 50, 722);
        //ÿ��ͨ�������������ͬƵ�ʵ�PWM
    uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
    gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
    pit_init(CCU6_0, PIT_CH0, 5000);
    //������ʼ��
    gpio_init(KEY1,GPI,0,PULLUP);
  //  gpio_init(KEY2,GPI,0,PULLUP);
  //  gpio_init(KEY3,GPI,0,PULLUP);
   // gpio_init(KEY4,GPI,0,PULLUP);

	//IfxCpu_emitEvent(&g_cpuSyncEvent);
	//IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();

    //ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
    //ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
    //ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
    while (TRUE)
    {
        //ʹ�ô˷����ŵ����ڣ�����Ҫʹ��while(1) �ȴ������⴦������Դ�˷�
               //���水��״̬
               key1_last_status = key1_status;
               key2_last_status = key2_status;
               //key3_last_status = key3_status;
               //key4_last_status = key4_status;
               //��ȡ��ǰ����״̬
               key1_status = gpio_get(KEY1);
               key2_status = gpio_get(KEY2);
             //  key3_status = gpio_get(KEY3);
               //key4_status = gpio_get(KEY4);

               //��⵽��������֮��  ���ſ���λ��־λ
               if(key1_status && !key1_last_status)    key1_flag = 1;
               if(key2_status && !key2_last_status)    key2_flag = 1;
            //   if(key3_status && !key3_last_status)    key3_flag = 1;
              // if(key4_status && !key4_last_status)    key4_flag = 1;

        error = ((int16)SteerEBData) - 39;
        //PWMB=722-1.3*error;
        PWMB = 722-(kp*error+kd*(error-last_error));
        last_error=error;
        //PWMB=400*b/1000;
        //PWMB=100*b/1000;
        pwm_duty(ATOM1_CH1_P33_9, PWMB);

        if(key1_flag)
        {
            key1_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            unsigned short duty=5000;

                if(duty<GTM_ATOM0_PWM_DUTY_MAX-1000)
                //duty+=555;
                target=10;
                duty=5000+Incremental_PI_A(encoder,target);

                pwm_duty(ATOM0_CH4_P02_4, duty);//����ռ�ձ�Ϊ�ٷ�֮5000/GTM_ATOM0_PWM_DUTY_MAX*100
                pwm_duty(ATOM0_CH5_P02_5, 5000);
                pwm_duty(ATOM0_CH6_P02_6, duty);
                pwm_duty(ATOM0_CH7_P02_7, 5000);

                systick_delay_ms(STM0, 100);
        }

        if(key2_flag)
            {
                key2_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
                unsigned short duty=5000;

                if(duty<GTM_ATOM0_PWM_DUTY_MAX-1000)
                duty+=666;

                pwm_duty(ATOM0_CH4_P02_4, duty);//����ռ�ձ�Ϊ�ٷ�֮5000/GTM_ATOM0_PWM_DUTY_MAX*100
                pwm_duty(ATOM0_CH5_P02_5, 5000);
                pwm_duty(ATOM0_CH6_P02_6, duty);
                pwm_duty(ATOM0_CH7_P02_7, 5000);

                systick_delay_ms(STM0, 100);
            }

                    //test2++;



        //��־λ��λ֮�󣬿���ʹ�ñ�־λִ���Լ���Ҫ�����¼�

        //��TFT����ʾ���Ա���
        /*lcd_showstr(0,3,"KEY1  TEST:");     lcd_showint32(12*8,3,test1,1);
        lcd_showstr(0,4,"KEY2  TEST:");     lcd_showint32(12*8,4,test2,1);
        lcd_showstr(0,5,"KEY3  TEST:");     lcd_showint32(12*8,5,test3,1);
        lcd_showstr(0,6,"KEY4  TEST:");     lcd_showint32(12*8,6,test4,1);*/

        systick_delay_ms(STM0, 10);//��ʱ����������Ӧ�ñ�֤����ʱ�䲻С��10ms

    }
}

#pragma section all restore


