#ifndef _MOTOR_H_
#define _MOTOR_H_

#include"include.h"
/************************�ٶȿ���*******************************/
extern sint8  speed_need;                   //Ŀ���ٶ�
extern sint8  speed_need_Boost;             //Ŀ�����
extern sint8  speed_need_normal;            //Ŀ���ٶ�
extern sint8  speed_SW_flag;                 //�ٶ�ѡ���־

/**************************������********************************/
extern float feed_fix;           //����������ϵ��
extern sint32 Feed_flag;             //�������ۼƼ���
extern sint32 Feed_speed;            //�������ɼ��ٶ�

/**************************�ٶ�PID����********************************/
extern float speed_out;         //���ʵ���ٶ�
extern float speed_error;       //�ٶ����
extern float Speed_P,Speed_I,Speed_D;


void speed_SW(void);
void FEED_COUNT(void);
void speed_PID(sint8 speed_in);


#define MOTOR1_P          IfxGtm_ATOM0_6_TOUT42_P23_1_OUT
#define MOTOR1_N          IfxGtm_ATOM0_5_TOUT40_P32_4_OUT

#define MOTOR2_P          IfxGtm_ATOM0_0_TOUT53_P21_2_OUT
#define MOTOR2_N          IfxGtm_ATOM0_4_TOUT50_P22_3_OUT


#define MOTOR3_P          IfxGtm_ATOM0_7_TOUT64_P20_8_OUT
#define MOTOR3_N          IfxGtm_ATOM0_3_TOUT56_P21_5_OUT


#define MOTOR4_P          IfxGtm_ATOM0_2_TOUT55_P21_4_OUT
#define MOTOR4_N          IfxGtm_ATOM0_1_TOUT54_P21_3_OUT

#define MOTOR_FREQUENCY    12500
#endif

