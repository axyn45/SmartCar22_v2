#ifndef _DEBUG_H_
#define _DEBUG_H_

#include"include.h"



uint32 Button_Duty(uint32 Button_val);     //������������
void GUI_Duty(void);


/****************LQ_CAMERA�в����ظ�����*****************/
extern unsigned char Pixle[LCDH][LCDW];               //��ֵ��������
extern char txt[16];                  //oled��ʾ�滻�ַ�

extern uint8 img_y_max;             //ɨ�����������ֵ
extern uint8 img_y_min;             //ɨ����������Զֵ
extern uint8 img_y_control;         //ɨ�����������ֵ
extern unsigned char mid_line[60];
extern uint8 mid_point[60];            //��ȡ������
extern uint8 point_len[60];            //ʵʱ�������
extern uint8 street_len;             //ֱ������
extern int start_flag;

#endif
