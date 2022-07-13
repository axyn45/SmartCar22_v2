/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��ZYF/chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��10��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
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
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ

ͨ�ö�ʱ����ԪGPT1 ��GPT2 ģ����зǳ����Ķ๦�ܶ�ʱ���ṹ����������
ʱ���¼�����������������������ɡ���Ƶ��������;��
���ǰ���5 ��16 λ��ʱ�����ֵ�������ʱ��GPT1 ��GPT2 ģ���С�ÿ��ģ���еĸ�
����ʱ��������಻ͬ��ģʽ�ж������У����ſض�ʱ��ģʽ������ģʽ�����ߺ�ͬģ��
��������ʱ������������ÿ��ģ���������/������ܺ�������ص�ר���жϡ�

GPT1 ģ����������ʱ��/���������ں˶�ʱ��T3 ������������ʱ��T2��T4�����ķֱ�
��ΪfGPT/4��GPT1 ģ��ĸ�����ʱ����Ϊ�ں˶�ʱ����ѡ������ó����ػ�׽�Ĵ�����
GPT2 ģ����������ʱ��/���������ں˶�ʱ��T6 �͸�����ʱ��T5�����ķֱ���ΪfGPT/2��
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/


#include <LQ_GPT12_ENC.h>
#include <stdint.h>
#include <LQ_TFT18.h>


/*************************************************************************
*  �������ƣ�void ENC_InitConfig(ENC_InputPin_t InputPin, ENC_DirPin_t DirPin)
*  ����˵����ENC ��ʼ��
*  ����˵����
*  InputPin  �� ENC��������ܽ�  LQ_GPT12_ENC.h ��ö����
*  DirPin    �� ENC����ܽ�      LQ_GPT12_ENC.h ��ö����
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��ENC_InitConfig(ENC2_InPut_P33_7, ENC2_Dir_P33_6); //��ʼ��ENC2 P33_7��Ϊ��������ܽ�  P33_6��Ϊ����ܽ�
*************************************************************************/
void ENC_InitConfig(ENC_InputPin_t InputPin, ENC_DirPin_t DirPin)
{
  //��ʼ��ȫ��ʱ��
  IfxGpt12_enableModule(&MODULE_GPT120);
  if(ENC_GetTimer(InputPin) != ENC_GetTimer(DirPin))
  {
#pragma warning 557         // ���ξ���
    while(1); //���� ENC��������ܽźͷ���ܽ��Ƿ�Ϊͬһ�� ENC
#pragma warning default     // �򿪾���
  }
  switch(ENC_GetTimer(InputPin))
  {
  case 2:
    //����T2 ����ģʽ
    IfxGpt12_T2_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
    //����T2 ����ģʽ   TxIn �����ؼ���
    IfxGpt12_T2_setIncrementalInterfaceInputMode(&MODULE_GPT120, IfxGpt12_IncrementalInterfaceInputMode_bothEdgesTxIN);
    IfxGpt12_T2_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
    //����T2 �����ܽ� A
    IfxGpt12_T2_setEudInput(&MODULE_GPT120, (IfxGpt12_EudInput)(DirPin & 0x0f));
    IfxGpt12_T2_setInput(&MODULE_GPT120, (IfxGpt12_Input)(InputPin & 0x0f));
    //��������  ʹ���ⲿ�ܽſ���
    IfxGpt12_T2_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
    //�������ϼ���
    IfxGpt12_T2_setTimerDirection(&MODULE_GPT120,IfxGpt12_TimerDirection_up);
    IfxGpt12_T2_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
    break;
  case 3:
    //����T3 ����ģʽ
    IfxGpt12_T3_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
    //����T2 ����ģʽ   TxIn �����ؼ���
    IfxGpt12_T3_setIncrementalInterfaceInputMode(&MODULE_GPT120, IfxGpt12_IncrementalInterfaceInputMode_bothEdgesTxIN);
    IfxGpt12_T3_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
    //����T2 �����ܽ� A
    IfxGpt12_T3_setEudInput(&MODULE_GPT120, (IfxGpt12_EudInput)(DirPin & 0x0f));
    IfxGpt12_T3_setInput(&MODULE_GPT120, (IfxGpt12_Input)(InputPin & 0x0f));
    //��������  ʹ���ⲿ�ܽſ���
    IfxGpt12_T3_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
    //�������ϼ���
    IfxGpt12_T3_setTimerDirection(&MODULE_GPT120,IfxGpt12_TimerDirection_up);
    IfxGpt12_T3_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
    break;
  case 4:
    //����T4 ����ģʽ
    IfxGpt12_T4_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
    //����T4 ����ģʽ   TxIn �����ؼ���
    IfxGpt12_T4_setIncrementalInterfaceInputMode(&MODULE_GPT120, IfxGpt12_IncrementalInterfaceInputMode_bothEdgesTxIN);
    IfxGpt12_T4_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
    //����T4 �����ܽ� A
    IfxGpt12_T4_setEudInput(&MODULE_GPT120, (IfxGpt12_EudInput)(DirPin & 0x0f));
    IfxGpt12_T4_setInput(&MODULE_GPT120, (IfxGpt12_Input)(InputPin & 0x0f));
    //��������  ʹ���ⲿ�ܽſ���
    IfxGpt12_T4_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
    //�������ϼ���
    IfxGpt12_T4_setTimerDirection(&MODULE_GPT120,IfxGpt12_TimerDirection_up);
    IfxGpt12_T4_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
    break;
  case 5:
    //����T5����ģʽ
    IfxGpt12_T5_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
    //����T5 ����ģʽ   TxIn �����ؼ���
    IfxGpt12_T5_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
    //����T5 �����ܽ� A
    IfxGpt12_T5_setEudInput(&MODULE_GPT120, (IfxGpt12_EudInput)(DirPin & 0x0f));
    IfxGpt12_T5_setInput(&MODULE_GPT120, (IfxGpt12_Input)(InputPin & 0x0f));
    //��������  ʹ���ⲿ�ܽſ���
    IfxGpt12_T5_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
    //�������ϼ���
    IfxGpt12_T5_setTimerDirection(&MODULE_GPT120,IfxGpt12_TimerDirection_up);
    IfxGpt12_T5_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
    break;
  case 6:
    //����T6 ����ģʽ
    IfxGpt12_T6_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
    //����T6 ����ģʽ   TxIn �����ؼ���
    IfxGpt12_T6_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
    //����T6 �����ܽ� A
    IfxGpt12_T6_setEudInput(&MODULE_GPT120, (IfxGpt12_EudInput)(DirPin & 0x0f));
    IfxGpt12_T6_setInput(&MODULE_GPT120, (IfxGpt12_Input)(InputPin & 0x0f));
    //��������  ʹ���ⲿ�ܽſ���
    IfxGpt12_T6_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
    //�������ϼ���
    IfxGpt12_T6_setTimerDirection(&MODULE_GPT120,IfxGpt12_TimerDirection_up);
    IfxGpt12_T6_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
    break;
  }
}

/*************************************************************************
*  �������ƣ�void ENC_InitConfig(ENC_InputPin_t InputPin, ENC_DirPin_t DirPin)
*  ����˵����ENC �õ�����ֵ,ʹ��ǰ��Ҫ��ENC��ʼ��
*  ����˵����InputPin  �� ENC��������ܽ�  LQ_GPT12_ENC.h ��ö����
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��ENC_GetCounter(ENC2_InPut_P00_7); //��ȡENC2�������ֵ
*************************************************************************/
signed short ENC_GetCounter(ENC_InputPin_t InputPin)
{
  signed short value = 0;
  switch(ENC_GetTimer(InputPin))
  {
  case 2:
    value = (signed short)MODULE_GPT120.T2.U;
    MODULE_GPT120.T2.U = 0;
    break;

  case 3:
    value = (signed short)MODULE_GPT120.T3.U;
    MODULE_GPT120.T3.U = 0;
    break;

  case 4:
    value = (signed short)MODULE_GPT120.T4.U;
    MODULE_GPT120.T4.U = 0;
    break;

  case 5:
    value = (signed short)MODULE_GPT120.T5.U;
    MODULE_GPT120.T5.U = 0;
    break;

  case 6:
    value = (signed short)MODULE_GPT120.T6.U;
    MODULE_GPT120.T6.U = 0;
    break;
  }
  return value;
}
#include <LQ_UART.h>
void TestEncoder(void)
{
    char txt[32];

     ENC_InitConfig(ENC2_InPut_P33_7, ENC2_Dir_P33_6);
     //ENC_InitConfig(ENC3_InPut_P02_6, ENC3_Dir_P02_7);//����ͷ��ͻ����������
//     ENC_InitConfig(ENC4_InPut_P02_8, ENC4_Dir_P33_5);
//     ENC_InitConfig(ENC5_InPut_P10_3, ENC5_Dir_P10_1);
//     ENC_InitConfig(ENC6_InPut_P20_3, ENC6_Dir_P20_0);
     TFTSPI_Init(1);        //LCD��ʼ��  0:����  1������
     TFTSPI_CLS(u16BLUE);   //��ɫ��Ļ
     TFTSPI_P8X16Str(0, 0, "Test Encoder",u16WHITE,u16BLACK);      //�ַ�����ʾ
     while(1)
     {
//        sint16 encValue2 = ENC_GetCounter(ENC2_InPut_P33_7);
//
//       sprintf(txt, "Enc2: %d; ", encValue2);
//
//       TFTSPI_P8X16Str(0, 2, txt,u16WHITE,u16BLACK);       //�ַ�����ʾ
       sint16 temp=0;
       sprintf(txt, "Enc2: %d", temp);

       TFTSPI_P6X8Str(0, 3, txt,u16WHITE,u16BLACK);       //�ַ�����ʾ
//       int encValue3 = ENC_GetCounter(ENC4_InPut_P02_8);
//       sprintf(txt, "Enc3: %05d; ", encValue3);
//       TFTSPI_P8X16Str(0, 3, txt,u16WHITE,u16BLACK);       //�ַ�����ʾ
//       UART_PutStr(UART0,txt);
//
//       int encValue4 = ENC_GetCounter(ENC5_InPut_P10_3);
//       sprintf(txt, "Enc4: %05d; ", encValue4);
//       TFTSPI_P8X16Str(0, 4, txt,u16WHITE,u16BLACK);       //�ַ�����ʾ
//       UART_PutStr(UART0,txt);
//
//       int encValue5 = ENC_GetCounter(ENC6_InPut_P20_3);
//       sprintf(txt, "Enc5: %05d;", encValue5);
//       TFTSPI_P8X16Str(0, 5, txt,u16WHITE,u16BLACK);       //�ַ�����ʾ
//       UART_PutStr(UART0,txt);

       //LED_Ctrl(LED0,RVS);        //��ƽ��ת,LED��˸
       delayms(200);              //��ʱ�ȴ�
     }

}

/////////////////////////////////////////////////////////////////////////////////////
