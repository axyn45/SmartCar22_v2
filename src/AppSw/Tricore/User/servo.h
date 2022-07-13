#ifndef _SERVO_H_
#define _SERVO_H_

#include"include.h"

void DJ_PID(unsigned char midpoint_in);  //���PD

extern int san;
extern sint16 midpoint_error;   //�������
extern sint16 lastpoint_error;   //�ϴ����
extern uint32 DJ_midpoint;                //�����ֵ
extern uint32 DJ_PWM;                          //���PWM
extern uint8 lost_flag;              //ȫ���߳�ʼʶ���־
extern uint8 lost_duty_flag;         //ȫ����׼ȷʶ���־(ʮ��)
extern uint8 cur_L_real_delay_flag;    //�󻷵�׼ȷ��иʶ���־
extern uint8 cur_R_real_delay_flag;    //�һ���׼ȷ��иʶ���־

extern uint8  KP_A,KP_B,KD;            //MAIN���PID
extern float Kd_pu;   //0   4.2
 extern float Kp_pu;  //4.5  2.8
#endif
