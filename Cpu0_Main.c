/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL

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
#include "..\Driver\include.h" //����ģ���ͷ�ļ�

/***************************END**********************************/
App_Cpu0 g_AppCpu0;                     /**< \brief CPU 0 global data */
IfxCpu_mutexLock mutexCpu0InitIsOk = 1; /** CPU0 ��ʼ����ɱ�־λ  */

volatile char mutexCpu0TFTIsOk = 0;

/*****************ִ�л����ۺϿ��ƺ���*********************/
void CAR_Drive_duty(void) //ִ�л����ۺϿ��ƺ���
{


  if(KEY_Read(DSW0))               //
    DJ_PID(mid_point[50]);  //�����������
  else;

    if (podao_flag)
        DJ_PID(mid_point[30]);

    if (garage_flag)
        DJ_PID(40);

    /************�ٶȿ���**************/
    if (0)
        speed_need = speed_need_Boost;
    else
        speed_need = 14; // speed_need_normal;       //�ϵ�ʱ�ٶ�Ĭ��Ϊ0������key0��ִ���ٶȵ�λѡ����  void speed_SW

    speed_PID(speed_need);
}

void CAR_Drive_duty_2(int point)           //ִ�л����ۺϿ��ƺ���
{


  if(KEY_Read(DSW0))               //
    DJ_PID(mid_point[point]);  //�����������
  else;

  if(podao_flag)
      DJ_PID(mid_point[30]);

  if(garage_flag)
      DJ_PID(40);


  /************�ٶȿ���**************/
  if(0)
  speed_need=speed_need_Boost;
  else
  speed_need=14;//speed_need_normal;       //�ϵ�ʱ�ٶ�Ĭ��Ϊ0������key0��ִ���ٶȵ�λѡ����  void speed_SW

    speed_PID(speed_need);

}




/*************************************************************************
 *  �������ƣ�int core0_main (void)
 *  ����˵����CPU0������
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��3��10��
 *  ��    ע��
 *************************************************************************/
int left_lost_flag;
int right_lost_flag;

int core0_main(void)
{
    //�ر�CPU���ж�
    IfxCpu_disableInterrupts();

    //�رտ��Ź�����������ÿ��Ź�ι����Ҫ�ر�
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    //��ȡ����Ƶ��
    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

    //����P14.0�ܽ����,P14.1���룬������115200
    UART_InitConfig(UART0_RX_P14_1, UART0_TX_P14_0, 115200);
    TFTSPI_Init(0);
    TFTSPI_CLS(u16BLACK);                                                         // OLED����
    TFTSPI_P16x16Str(0, 0, (unsigned char *)"�����������ܿƼ�", u16RED, u16BLUE); // �ַ�����ʾ
    CAMERA_Init(50);                                                              //����ͷ��ʼ��
    MotorInit();
    CAMERA_Init(50);                                   //����ͷ��ʼ��
    ATOM_PWM_InitConfig(ATOMSERVO1, DJ_midpoint, 100); //���Ƶ��Ϊ100HZ����ʼֵΪ1.5ms��ֵ
    ENC_InitConfig(ENC2_InPut_P33_7, ENC2_Dir_P33_6);
    // ENC_InitConfig(ENC6_InPut_P20_3, ENC6_Dir_P20_0);//������4��ʼ��
    // LED������P10.6��P10.5��ʼ��
    GPIO_LED_Init();
    //����CPU���ж�
    IfxCpu_enableInterrupts();

    // adc��ʼ��
    // ADC_InitConfig(ADC0, 80000); //��ʼ��
    // ADC_InitConfig(ADC1, 80000);
    // ADC_InitConfig(ADC2, 80000);
    // ADC_InitConfig(ADC3, 80000);
    // ADC_InitConfig(ADC4, 80000);
    // ADC_InitConfig(ADC5, 80000);
    // ADC_InitConfig(ADC6, 80000);
    // ADC_InitConfig(ADC7, 80000);

    // ATOM_PWM_InitConfig(IfxGtm_ATOM2_4_TOUT30_P33_8_OUT, 0,4000);//��������ʼ��

    // STM_InitConfig(STM1, STM_Channel_0, 50000);

    left_point[img_y_max] = 0;
    right_point[img_y_max] = 80;

    //֪ͨCPU1   CPU0��ʼ�����
    IfxCpu_releaseMutex(&mutexCpu0InitIsOk);
    mutexCpu0TFTIsOk = 0;
    start_flag = 0;

    TFTSPI_P8X16Str(2, 0, "LQ 9V034 Car", u16RED, u16GREEN);
    TFTSPI_P8X16Str(1, 2, "K2 Show Video77", u16RED, u16GREEN);
    delayms(500);
    TFTSPI_CLS(u16BLUE); // ����

    mutexCpu0TFTIsOk = 1; // CPU1�� 0ռ��/1�ͷ� TFT
                          //  LQ_ATom_Servo_2chPWM();
                          //  LQ_GPT_4mini512TFT();
                          // Test_CAMERA();
                          //    TestEncoder();
                          //    LQ_Atom_Motor_8chPWM();
    while (1)             //��ѭ��
    {

        if(Camera_Flag == 2)                       //����ͷ���ж�
           {
              FEED_COUNT();                             //����������
              Camera_Flag = 0;
             /* ��ȡ����ʹ�õ����� */
              Get_Use_Image();
              Get_01_Value(0);                          // ��ֵ��
              //TFTSPI_BinRoad(0, 0, LCDH, LCDW, (unsigned char*)Pixle);        // TFT��̬��ʾ����ͷͼ��
           //   Get_ADC();                                   //��Ųɼ�

              Horizontal_line();                         //ˮƽɨ�ߣ��ұ߽�������
              portrait_line();                             //����ɨ�ߣ�������Ԫ�صĹյ�

              if(start_flag==0)//���ܱ�־λ
                  {
//                              OutInGarage (0, 1);
                              start_flag=1;
                              huandaoshibie++;    //��������ʶ��
                  }

              saidaokuandu();                       //����25��10�п���

              left_lost_flag=Lost_line_left();
              right_lost_flag=Lost_line_right();//�ж���Ч�ж���

              misslinecount();                           //�������ۼ�

              saidaoyuansu();                          //����Ԫ���жϣ�����


            saidaokuandu(); //����25��10�п���

           //  for(uint8 i=59;i>0;i--)              //oled��ʾ����
           //  Pixle[i][(mid_point[i])]=0;
               if(lefthuandao_flag)
               {
                  if(leftstate==4)
                  {
                      if(pulse>160)
                      {
//                          DJ_PID(15);
                      ATOM_PWM_SetDuty(ATOMSERVO1, 1760, 100);
                      MotorCtrl4w(1000,1000,1000,1000);

                      }
                      else
                      {
                          CAR_Drive_duty_2(35);
                      }
                  }
                  else{
                      CAR_Drive_duty_2(35);
                  }
                  if(leftstate==5)
                  {
//                          ATOM_PWM_SetDuty(ATOMSERVO1, 1700, 100);
                      CAR_Drive_duty_2(45);
                  }
                  if(leftstate==6)
                  {
                      CAR_Drive_duty_2(36);
                  }

               }
               else{
                  CAR_Drive_duty();      }         //��������������ƣ�ת�����ٶȣ�

               GUI_Duty();                           //���Խ���

            saidaoyuansu(); //����Ԫ���жϣ�����

            //  for(uint8 i=59;i>0;i--)              //oled��ʾ����
            //  Pixle[i][(mid_point[i])]=0;

            CAR_Drive_duty(); //��������������ƣ�ת�����ٶȣ�
            GUI_Duty();       //���Խ���

            if (garage_delay)
                garage_delay++; //ʶ��������ӳٱ�������ֹ�ظ�ʶ�������

            if (ruku_flag)
                OutInGarage(1, 1); //���

            /* �������ͷ�ɼ���ɱ�־λ  �����������򲻻��ٴβɼ����� */
        }

        LED_Ctrl(LED1, RVS); //��ƽ��ת,LED��˸
    }
}
