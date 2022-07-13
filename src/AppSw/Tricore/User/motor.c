#include<motor.h>
/************************�ٶȿ���*******************************/
sint8  speed_need=0;                   //Ŀ���ٶ�
sint8  speed_need_Boost=0;             //Ŀ�����
sint8  speed_need_normal=0;            //Ŀ���ٶ�
sint8  speed_SW_flag=1;                 //�ٶ�ѡ���־

/**************************������********************************/
float feed_fix=10.6;           //����������ϵ��
sint32 Feed_flag=0;             //�������ۼƼ���
sint32 Feed_speed=0;            //�������ɼ��ٶ�

/*************************�������******************************/
float Speed_P=80,Speed_I=50,Speed_D=0; //MAIN���PID
float speed_out=0;         //���ʵ���ٶ�
float speed_error;       //�ٶ����
uint8 Block_motor_time_flag=0;          //��ת��ʱ��־
uint8 Block_motor_duty_flag=0;          //��ת�¼���־
uint8 Block_motor_delay_flag=0;         //��ת��и��־



/********************�ٶȵ�λѡ��************************/
void speed_SW(void)
{
  if(speed_SW_flag==1)           //�ٶȵ�λ1
  {
    speed_need_Boost=14;         //Ŀ�����
    speed_need_normal=14;        //Ŀ���ٶ�
  }
  else if(speed_SW_flag==2)     //�ٶȵ�λ2
  {
    speed_need_Boost=20;         //Ŀ�����
    speed_need_normal=15;        //Ŀ���ٶ�
  }
  else if(speed_SW_flag==3)     //�ٶȵ�λ3
  {
    speed_need_Boost=25;         //Ŀ�����
    speed_need_normal=20;        //Ŀ���ٶ�
  }
  else if(speed_SW_flag==4)     //�ٶȵ�λ4
  {
    speed_need_Boost=30;         //Ŀ�����
    speed_need_normal=25;        //Ŀ���ٶ�
  }
  else;
}



/*******************��������������************************/
void FEED_COUNT(void)
{
  Feed_speed=ENC_GetCounter(ENC2_InPut_P33_7);//ǰ��Ϊ��ֵ//������1
  //Feed_speed=ENC_GetCounter(ENC6_InPut_P20_3);//ǰ��Ϊ��ֵ//������4
  //char txt[20];
  //sprintf(txt, "Feed_speed: %05d;", Feed_speed);
  //TFTSPI_P8X16Str(0, 5, txt,u16WHITE,u16BLACK);       //�ַ�����ʾ
  Feed_flag += Feed_speed;
  Feed_speed=(Feed_speed/feed_fix); //ǰ��Ϊ��ֵ//����Ϊ��ֵ
}



/*******************ת��PID���ƺ���*************************/
void speed_PID(sint8 speed_in)
{
    if(Lleft2<10&&Lright2<10)  //������������ͣ��
        {
           speed_in=0;
           speed_out=0;
        }

  signed int static last_error_1;      //�ϴ�ƫ��
  signed int static last_error_2;      //���ϴ�ƫ��

  speed_error=(float)speed_in-Feed_speed;      //����ת�����
  speed_out +=Speed_P*(speed_error-last_error_1)+Speed_I*speed_error+ Speed_D*(speed_error-2*last_error_1+last_error_2);

  last_error_2=last_error_1;            //��¼���ϴ����
  last_error_1=speed_error;             //��¼�ϴ����

  /*******����޷� Σ�գ��󶯣�*********/
  if(speed_out>2500)
     speed_out=2500;
   if(speed_out<-2500)
     speed_out=-2500;


   if(speed_out<0)
   {
       ATOM_PWM_SetDuty(ATOMPWM5, -speed_out, 12500);//���������ת
       ATOM_PWM_SetDuty(ATOMPWM4, 0, 12500);
   }
   else
   {
     ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);//���������ת
     ATOM_PWM_SetDuty(ATOMPWM4, speed_out, 12500);
   }

}


#include<LQ_GPIO.h>
//#include"motor.h"
void MotorInit (void)
{
    ATOM_PWM_InitConfig(MOTOR1_P, 0, MOTOR_FREQUENCY);
    ATOM_PWM_InitConfig(MOTOR2_P, 0, MOTOR_FREQUENCY);
    ATOM_PWM_InitConfig(MOTOR3_P, 0, MOTOR_FREQUENCY);
    ATOM_PWM_InitConfig(MOTOR4_P, 0, MOTOR_FREQUENCY);


    PIN_InitConfig(P32_4, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(P22_3, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(P21_5, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(P21_3, PIN_MODE_OUTPUT, 0);

}

void MotorCtrl4w(sint32 motor1, sint32 motor2,sint32 motor3, sint32 motor4)
{
    if (motor1 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR1_P, motor1, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P32, 4);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR1_P, MOTOR_FREQUENCY+motor1, MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P32, 4);
       }

    if (motor2 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR2_P, motor2, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P22, 3);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR2_P, MOTOR_FREQUENCY+motor2, MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P22, 3);
       }
    if (motor3 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR3_P, motor3, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P21, 5);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR3_P, MOTOR_FREQUENCY+motor3, MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P21, 5);
       }

       if (motor4 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR4_P, motor4, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P21, 3);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR4_P, MOTOR_FREQUENCY+motor4, MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P21, 3);
       }
}




