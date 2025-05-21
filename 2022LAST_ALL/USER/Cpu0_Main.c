/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file            main
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ3184284598)
 * @version         查看doc内version文件 版本说明
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

//将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中


//工程导入到软件之后，应该选中工程然后点击refresh刷新一下之后再编译
//工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
//然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
//一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化

//对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
//简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因此需要我们自己手动调用enableInterrupts();来开启中断的响应。

//定义按键引脚
#define KEY1    P22_0
#define KEY2    P22_1
//#define KEY3    P22_2
//#define KEY4    P22_3

//开关状态变量
uint8 key1_status = 1;
uint8 key2_status = 1;
//uint8 key3_status = 1;
//uint8 key4_status = 1;

//上一次开关状态变量
uint8 key1_last_status;
uint8 key2_last_status;
//uint8 key3_last_status;
//uint8 key4_last_status;

//开关标志位
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

    get_clk();//获取时钟频率  务必保留
    //用户在此处调用各种初始化函数等
    gtm_pwm_init(ATOM0_CH4_P02_4, 17*1000, 5000);//ATOM 0模块的通道4 使用P02_4引脚输出PWM  PWM频率50HZ  占空比百分之0/GTM_ATOM0_PWM_DUTY_MAX*100  GTM_ATOM0_PWM_DUTY_MAX宏定义在zf_gtm_pwm.h
    gtm_pwm_init(ATOM0_CH5_P02_5, 17*1000, 5000);
    gtm_pwm_init(ATOM0_CH6_P02_6, 17*1000, 5000);
    gtm_pwm_init(ATOM0_CH7_P02_7, 17*1000, 5000);

    gtm_pwm_init(ATOM1_CH1_P33_9, 50, 722);
        //每个通道都可以输出不同频率的PWM
    uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
    gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
    pit_init(CCU6_0, PIT_CH0, 5000);
    //按键初始化
    gpio_init(KEY1,GPI,0,PULLUP);
  //  gpio_init(KEY2,GPI,0,PULLUP);
  //  gpio_init(KEY3,GPI,0,PULLUP);
   // gpio_init(KEY4,GPI,0,PULLUP);

	//IfxCpu_emitEvent(&g_cpuSyncEvent);
	//IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();

    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    while (TRUE)
    {
        //使用此方法优点在于，不需要使用while(1) 等待，避免处理器资源浪费
               //保存按键状态
               key1_last_status = key1_status;
               key2_last_status = key2_status;
               //key3_last_status = key3_status;
               //key4_last_status = key4_status;
               //读取当前按键状态
               key1_status = gpio_get(KEY1);
               key2_status = gpio_get(KEY2);
             //  key3_status = gpio_get(KEY3);
               //key4_status = gpio_get(KEY4);

               //检测到按键按下之后  并放开置位标志位
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
            key1_flag = 0;//使用按键之后，应该清除标志位
            unsigned short duty=5000;

                if(duty<GTM_ATOM0_PWM_DUTY_MAX-1000)
                //duty+=555;
                target=10;
                duty=5000+Incremental_PI_A(encoder,target);

                pwm_duty(ATOM0_CH4_P02_4, duty);//设置占空比为百分之5000/GTM_ATOM0_PWM_DUTY_MAX*100
                pwm_duty(ATOM0_CH5_P02_5, 5000);
                pwm_duty(ATOM0_CH6_P02_6, duty);
                pwm_duty(ATOM0_CH7_P02_7, 5000);

                systick_delay_ms(STM0, 100);
        }

        if(key2_flag)
            {
                key2_flag = 0;//使用按键之后，应该清除标志位
                unsigned short duty=5000;

                if(duty<GTM_ATOM0_PWM_DUTY_MAX-1000)
                duty+=666;

                pwm_duty(ATOM0_CH4_P02_4, duty);//设置占空比为百分之5000/GTM_ATOM0_PWM_DUTY_MAX*100
                pwm_duty(ATOM0_CH5_P02_5, 5000);
                pwm_duty(ATOM0_CH6_P02_6, duty);
                pwm_duty(ATOM0_CH7_P02_7, 5000);

                systick_delay_ms(STM0, 100);
            }

                    //test2++;



        //标志位置位之后，可以使用标志位执行自己想要做的事件

        //在TFT上显示测试变量
        /*lcd_showstr(0,3,"KEY1  TEST:");     lcd_showint32(12*8,3,test1,1);
        lcd_showstr(0,4,"KEY2  TEST:");     lcd_showint32(12*8,4,test2,1);
        lcd_showstr(0,5,"KEY3  TEST:");     lcd_showint32(12*8,5,test3,1);
        lcd_showstr(0,6,"KEY4  TEST:");     lcd_showint32(12*8,6,test4,1);*/

        systick_delay_ms(STM0, 10);//延时，按键程序应该保证调用时间不小于10ms

    }
}

#pragma section all restore


