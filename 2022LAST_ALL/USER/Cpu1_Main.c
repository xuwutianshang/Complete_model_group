/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/

#include "headfile.h"
#pragma section all "cpu1_dsram"

uint8 gpio_status;



void core1_main(void)
{
	disableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());

    gpio_init(P21_4, GPO, 0, PUSHPULL);//����P20_8Ϊ��� Ĭ������͵�ƽ  PUSHPULL���������

    gpio_init(P21_5, GPO, 0, PUSHPULL);

    gpio_init(P20_8, GPO, 0, PUSHPULL);

    gpio_init(P20_9, GPO, 0, PUSHPULL);


    gpio_init(P21_2, GPI, 0, PULLUP);  //����P21_2Ϊ���� PULLUP����������



    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());

    //�û��ڴ˴����ø��ֳ�ʼ��������
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();
    while (TRUE)
    {
		//�û��ڴ˴���д�������

        gpio_toggle(P21_4);
        systick_delay_ms(STM0, 100);
        gpio_toggle(P21_5);

        systick_delay_ms(STM0, 100);
        gpio_toggle(P20_8);//��תIO
        systick_delay_ms(STM0, 100);
        gpio_toggle(P20_9);
        systick_delay_ms(STM0, 100);


    }
}





#pragma section all restore
