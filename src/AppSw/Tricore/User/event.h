#ifndef _EVENT_H_
#define _EVENT_H_

#include"include.h"

/******************ʶ�����жϱ�־***************************/
/*���߱�־*/
extern uint8 all_lost;               //ȫ����־
extern uint8 lost_left[60];            //���߱�־
extern uint8 lost_right[60];           //�Ҷ��߱�־
/*��ͣ*/
extern uint8 KEY_start_flag;         //һ��������־
extern uint16 KEY_start_time_flag;   //����ʱ���־
extern uint16 stop_flag;//ͣ����־
extern uint16 stop_time_flag;//ͣ��ʱ���־
extern uint16 stop_realy;//��ʵͣ����־

/*����*/
extern uint8 Tri_count;              //���������־
extern uint8 Tri_flag;               //�����ʼʶ���־
extern uint8 Tri_delay_flag;         //�����и��־
extern uint8 Tri_retest_flag;        //�����ظ�����־
extern uint8 Tri_retest_flag1;       //�����ظ�����־1
extern uint16 Tri_time_flag;         //�����ʱ����
extern uint8 Tri_duty_flag;          //����׼ȷʶ���־
extern uint8 Tri_out_flag;           //�������־

/*�µ���־*/
extern uint8 uphill_flag;            //�µ�ʶ���־
extern uint8 uphill_delay_flag;      //�µ���и��־
extern uint8 uphill_duty_flag;       //�µ�׼ȷʶ���־
extern uint8 uphill_time_flag;       //�µ���ʱ����
extern float point_K;               //Զ��б��*10

/*ʮ��*/
extern uint8 lost_flag;              //ȫ���߳�ʼʶ���־
extern uint8 lost_delay_flag;        //ʮ�ֳ�и��־
extern uint16 lost_car_time_flag;    //ʮ�ּ�ʱ����
extern uint8 lost_duty_flag;         //ȫ����׼ȷʶ���־(ʮ��)
/*����Ԥ�ж�*/
extern uint8 cur_L_ready_flag;         //�󻷵�Ԥ�жϳ�ʼʶ���־
extern uint8 cur_L_ready_delay_flag;   //�󻷵�Ԥ�жϳ�и��־
extern uint16 cur_L_ready_time_flag;   //�󻷵�Ԥ�жϼ�ʱ����
extern uint8 cur_L_ready_rest_flag;    //�󻷵�Ԥ�жϸ�λ����
extern uint8 cur_R_ready_flag;         //�һ���Ԥ�жϳ�ʼʶ���־
extern uint8 cur_R_ready_delay_flag;   //�һ���Ԥ�жϳ�и��־
extern uint16 cur_R_ready_time_flag;   //�һ���Ԥ�жϼ�ʱ����
extern uint8 cur_R_ready_rest_flag;    //�һ���Ԥ�жϸ�λ����
/*����׼ȷʶ��*/
extern uint8 cur_L_real_flag;          //�󻷵�׼ȷ�ж�ʶ���־
extern uint8 cur_L_real_delay_flag;    //�󻷵�׼ȷ��иʶ���־
extern uint8 cur_L_real_rest_flag;     //�󻷵�׼ȷ��λʶ���־
extern uint16 cur_L_real_time_flag;    //�󻷵�׼ȷ��иʶ���־
extern uint16 cur_L_real_time_flag1;   //�󻷵�׼ȷ��иʶ���־1

extern uint8 cur_R_real_flag;          //�һ���׼ȷ�ж�ʶ���־
extern uint8 cur_R_real_delay_flag;    //�һ���׼ȷ��иʶ���־
extern uint8 cur_R_real_rest_flag;     //�һ���׼ȷ��λʶ���־
extern uint16 cur_R_real_time_flag;    //�һ���׼ȷ��иʶ���־
extern uint16 cur_R_real_time_flag1;   //�һ���׼ȷ��иʶ���־1



uint8 Tri_count_duty(void);      //�¼�������
void EVENT_Duty(void);           //�������ʶ

#endif

