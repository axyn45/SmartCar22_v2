/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL

------------------------------------------------
��dev.env.��AURIX Development Studio1.2.2�����ϰ汾
��Target �� TC264DA/TC264D
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
________________________________________________________________
����iLLD_1_0_1_11_0�ײ����,

ʹ�����̵�ʱ�򣬽������û�пո��Ӣ��·����
����CIFΪTC264DA�����⣬�����Ĵ������TC264D
����Ĭ�ϳ�ʼ����EMEM��512K������û�ʹ��TC264D��ע�͵�EMEM_InitConfig()��ʼ��������
������\Libraries\iLLD\TC26B\Tricore\Cpu\CStart\IfxCpu_CStart0.c��164�����ҡ�
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "..\Driver\include.h"//����ģ���ͷ�ļ�

extern IfxCpu_mutexLock mutexCpu0InitIsOk;   /** CPU0 ��ʼ����ɱ�־λ  */

int core1_main (void)
{

    IfxCpu_enableInterrupts();
    /*
     * �رտ��Ź�
     * */
    IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());


    //�ȴ�CPU0 ��ʼ�����
    while(!IfxCpu_acquireMutex(&mutexCpu0InitIsOk));


    /* �û����� */


#pragma warning 557         // ���ξ���
    while(1)//��ѭ��
    {


    }
#pragma warning default     // �򿪾���
}
