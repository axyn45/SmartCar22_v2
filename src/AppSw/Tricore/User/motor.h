#ifndef _MOTOR_H_
#define _MOTOR_H_

#include"include.h"
/************************速度控制*******************************/
extern sint8  speed_need;                   //目标速度
extern sint8  speed_need_Boost;             //目标高速
extern sint8  speed_need_normal;            //目标速度
extern sint8  speed_SW_flag;                 //速度选择标志

/**************************编码器********************************/
extern float feed_fix;           //编码器修正系数
extern sint32 Feed_flag;             //编码器累计计数
extern sint32 Feed_speed;            //编码器采集速度

/**************************速度PID参数********************************/
extern float speed_out;         //输出实际速度
extern float speed_error;       //速度误差
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

