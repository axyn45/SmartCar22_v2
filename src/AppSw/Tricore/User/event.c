#include"event.h"
/*��ҳ�����ò���*/



/******************ʶ�����жϱ�־***************************/
/*���߱�־*/
uint8 all_lost=0;               //ȫ����־
uint8 lost_left[60];            //���߱�־
uint8 lost_right[60];           //�Ҷ��߱�־
/*��ͣ*/
uint8 KEY_start_flag=0;         //һ��������־
uint16 KEY_start_time_flag=0;   //����ʱ���־
uint16 stop_flag=0;//ͣ����־
uint16 stop_time_flag=0;//ͣ��ʱ���־
uint16 stop_realy=0;//��ʵͣ����־


/*����*/
uint8 Tri_count=0;              //���������־
uint8 Tri_flag=0;               //�����ʼʶ���־
uint8 Tri_delay_flag=0;         //�����и��־
uint8 Tri_retest_flag=0;        //�����ظ�����־
uint8 Tri_retest_flag1=0;       //�����ظ�����־1
uint16 Tri_time_flag=0;         //�����ʱ����
uint8 Tri_duty_flag=0;          //����׼ȷʶ���־
uint8 Tri_out_flag=0;           //�������־
uint8 Tri_delay_flag1=0;   //��ֹ�ظ�ʶ������
/*�µ���־*/
uint8 uphill_flag=0;            //�µ�ʶ���־
uint8 uphill_delay_flag=0;      //�µ���и��־
uint8 uphill_duty_flag=0;       //�µ�׼ȷʶ���־
uint8 uphill_time_flag=0;       //�µ���ʱ����
float point_K=0;               //Զ��б��*10


/*ʮ��*/
uint8 lost_flag=0;              //ȫ���߳�ʼʶ���־
uint8 lost_delay_flag=0;        //ʮ�ֳ�и��־
uint16 lost_car_time_flag=0;    //ʮ�ּ�ʱ����
uint8 lost_duty_flag=0;         //ȫ����׼ȷʶ���־(ʮ��)
/*����Ԥ�ж�*/
uint8 cur_L_ready_flag=0;         //�󻷵�Ԥ�жϳ�ʼʶ���־
uint8 cur_L_ready_delay_flag=0;   //�󻷵�Ԥ�жϳ�и��־
uint16 cur_L_ready_time_flag=0;   //�󻷵�Ԥ�жϼ�ʱ����
uint8 cur_L_ready_rest_flag=0;    //�󻷵�Ԥ�жϸ�λ����
uint8 cur_R_ready_flag=0;         //�һ���Ԥ�жϳ�ʼʶ���־
uint8 cur_R_ready_delay_flag=0;   //�һ���Ԥ�жϳ�и��־
uint16 cur_R_ready_time_flag=0;   //�һ���Ԥ�жϼ�ʱ����
uint8 cur_R_ready_rest_flag=0;    //�һ���Ԥ�жϸ�λ����
/*����׼ȷʶ��*/
uint8 cur_L_real_flag=0;          //�󻷵�׼ȷ�ж�ʶ���־
uint8 cur_L_real_delay_flag=0;    //�󻷵�׼ȷ��иʶ���־
uint8 cur_L_real_rest_flag=0;     //�󻷵�׼ȷ��λʶ���־
uint16 cur_L_real_time_flag=0;    //�󻷵�׼ȷ��иʶ���־
uint16 cur_L_real_time_flag1=0;   //�󻷵�׼ȷ��иʶ���־1

uint8 cur_R_real_flag=0;          //�һ���׼ȷ�ж�ʶ���־
uint8 cur_R_real_delay_flag=0;    //�һ���׼ȷ��иʶ���־
uint8 cur_R_real_rest_flag=0;     //�һ���׼ȷ��λʶ���־
uint16 cur_R_real_time_flag=0;    //�һ���׼ȷ��иʶ���־
uint16 cur_R_real_time_flag1=0;   //�һ���׼ȷ��иʶ���־1






//                      ��һ���֣��¼�������
/*******************************************************************************/
void EVENT_Duty(void)
{
  /************����ʱ��*****************/
  Tri_time_flag++;

//  if(uphill_time_flag>200)uphill_time_flag=200;else;
  lost_car_time_flag++;
  cur_R_ready_time_flag++;
  cur_R_real_time_flag++;
  cur_L_ready_time_flag++;
  cur_L_real_time_flag++;
  Tri_delay_flag1++;
  /************ͣ����ʱ*****************/
  if(stop_flag)
      stop_time_flag++;
  if(stop_time_flag>200)
  {
      stop_flag=0;//�ж�����
      stop_time_flag=0;//��ʱ����
  }
  if(stop_time_flag == 1)
  {
      stop_realy++;//�����ߴ�������
  }
  /************������ʱ*****************/
  if(KEY_start_flag)KEY_start_time_flag++;
  else;
  if(KEY_start_time_flag>5000) KEY_start_time_flag=5000;
  else;
  /************�µ�����*****************/
    if(uphill_flag || uphill_delay_flag)
    {
      uphill_delay_flag=1;
      uphill_duty_flag=1;
      uphill_time_flag++;
      if(uphill_time_flag>100)
        uphill_delay_flag=0;
      else;
    }
    else
    {
      uphill_delay_flag=0;
      uphill_duty_flag=0;
      uphill_time_flag=0;
    }
    /*************���沿��*****************/
    if((Tri_flag &&point_len[15]<30&& !uphill_duty_flag && !lost_duty_flag) || Tri_delay_flag)//�����־�����µ�����ʮ��
    {
      Tri_out_flag=0;
      Tri_delay_flag=1;
      Tri_duty_flag=1;

      if(Tri_flag==0)                                             //����ʶ����ʧ
        Tri_retest_flag=1;
      else;
      if(Tri_retest_flag&&Tri_flag&& Tri_delay_flag1>200)                               //������ʶ��
        Tri_retest_flag1=1;
      else;
      if(Tri_flag==0 && Tri_retest_flag1 && Tri_time_flag>40)     //��������ʧ
      {
         Tri_delay_flag=0;
         Tri_out_flag=1;
        // if(KEY_start_time_flag>10)
         Tri_count++;//else;
      }
      else;
    }
    else
    {
      Tri_retest_flag=0;
      Tri_retest_flag1=0;
      Tri_duty_flag=0;
      Tri_time_flag=0;
      Tri_delay_flag1=0;
    }


  /*************ʮ�ֲ���****************/
       if(lost_flag&&point_len[15]>30&& !uphill_duty_flag &&!Tri_delay_flag|| lost_delay_flag)//ʮ��ʶ��,�����棬���µ�
  {
    lost_delay_flag=1;
    lost_duty_flag=1;
    if((lost_flag==0&&lost_car_time_flag>15)||lost_car_time_flag>30)
    {
      lost_delay_flag=0;
    }else;
  }
  else
  {
    lost_car_time_flag=0;
    lost_duty_flag=0;
  }
  /*************����Ԥʶ��****************/
  /*��Ԥʶ��*/
  if(cur_R_ready_flag||cur_R_ready_delay_flag)
  { cur_R_ready_delay_flag=1;
  //ImageAddingLine(1, 10, 15, 10, 40);
   // if((!lost_right[20]&&!lost_right[23])&&!lost_left[23]&&!lost_left[25]&&street_len>40&&cur_R_ready_time_flag>10)
       if(!lost_left[23]&&!lost_left[25]&&street_len>40&&cur_R_ready_time_flag>10)
    {cur_R_ready_rest_flag=1;}else;

    if(cur_R_ready_time_flag>300||lost_left[23]||lost_left[25])
    {cur_R_ready_delay_flag=0;cur_R_ready_rest_flag=0;}
    else if(cur_R_ready_rest_flag&&lost_right[23]&&lost_right[25]&&!lost_left[23]&&!lost_left[25]&&street_len>40&&MagneticField>270)
    { cur_R_ready_delay_flag=0;cur_R_ready_rest_flag=0;cur_R_real_flag=1;}else;
  }
  else
  {cur_R_ready_delay_flag=0;
    cur_R_ready_time_flag=0;
    cur_R_ready_rest_flag=0;
  }
  /*��Ԥʶ��*/
  if(cur_L_ready_flag||cur_L_ready_delay_flag)
  { cur_L_ready_delay_flag=1;
  //ImageAddingLine(1, 10, 15, 10, 40);//���߷�ֹ������
    if((!lost_left[23]&&!lost_left[25])&&!lost_right[23]&&!lost_right[25]&&street_len>40&&cur_L_ready_time_flag>10)
    {cur_L_ready_rest_flag=1;}else;

    if(cur_L_ready_time_flag>300||lost_right[23]||lost_right[25])
    {cur_L_ready_delay_flag=0 ;cur_L_ready_rest_flag=0;}
    else if(cur_L_ready_rest_flag&&lost_left[23]&&lost_left[25]&&!lost_right[23]&&!lost_right[25]&&street_len>40&&MagneticField>350)
    { cur_L_ready_delay_flag=0;cur_L_ready_rest_flag=0;cur_L_real_flag=1;}else;
  }
  else
  { cur_L_ready_delay_flag=0;
    cur_L_ready_time_flag=0;
    cur_L_ready_rest_flag=0;
  }
  /*************����׼ȷʶ��****************/
  /*��׼ȷʶ��*/
  if(cur_R_real_flag||cur_R_real_delay_flag)
  { cur_R_real_flag=0;
    cur_R_real_delay_flag=1;
    if(cur_R_real_time_flag>50&&(lost_left[23]&&lost_left[25]))
      cur_R_real_rest_flag=1;else;
    if(cur_R_real_rest_flag)cur_R_real_time_flag1++;else;
    if(cur_R_real_time_flag1>100)cur_R_real_time_flag=100;else;
    if(cur_R_real_time_flag1>25&&!lost_left[23]&&!lost_left[25]&&!lost_right[23]&&!lost_right[25])
    {cur_R_real_delay_flag=0;}else;
  }
  else
  {cur_R_real_delay_flag=0;
    cur_R_real_time_flag=0;
    cur_R_real_time_flag1=0;
    cur_R_real_rest_flag=0;
  }
  /*��׼ȷʶ��*/
  if(cur_L_real_flag||cur_L_real_delay_flag)
  { cur_L_real_flag=0;
    cur_L_real_delay_flag=1;
    if(cur_L_real_time_flag>50&&(lost_right[23]&&lost_right[25]))//���������
      cur_L_real_rest_flag=1;else;
    if(cur_L_real_rest_flag)cur_L_real_time_flag1++;else;
    if(cur_L_real_time_flag1>100)cur_L_real_time_flag1=100;
    if(cur_L_real_time_flag1>25&&!lost_left[23]&&!lost_left[25]&&!lost_right[23]&&!lost_right[25])
    {cur_L_real_delay_flag=0;}else;
  }
  else
  {cur_L_real_delay_flag=0;
    cur_L_real_time_flag=0;
    cur_L_real_time_flag1=0;
    cur_L_real_rest_flag=0;
  }
}





/*********************�������ʶ��**************************/
uint8 Tri_count_duty(void)
{
  if(1)//��������ѡ��
  {
    if(Tri_count==0)return 0;
    else if(Tri_count)return 1;
    else return 0;
  }else
  {
    if(Tri_count==0)return 1;
    else if(Tri_count>=1)return 0;
    else return 1;
  }
}



