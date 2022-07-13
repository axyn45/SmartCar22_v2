#include"debug.h"


char txt[16];                  //oled��ʾ�滻�ַ�
int start_flag=0;

//extern int DJ_MID;
//                      ��һ���֣����Խ��沿��

/********************������������****************************/
uint32 Button_Duty(uint32 Button_val)     //������������
{
  if(!KEY_Read(KEY2))                   //������
  {
      delayms(10);
    if(!KEY_Read(KEY2))                 //�����ж�
    {
      Button_val++;
      TFTSPI_CLS(u16BLACK);                   //����
      if(Button_val>10000)                //�޷�
        Button_val=10000;
      while(!KEY_Read(KEY2));
    }
  }
  if(!KEY_Read(KEY1))                   //������
  {
      delayms(10);
    if(!KEY_Read(KEY1))                 //�����ж�
    {
      Button_val--;
      TFTSPI_CLS(u16BLACK);                   //����
      if(Button_val<2)                  //�޷�
        Button_val=1;
      while(!KEY_Read(KEY1));
    }
  }
   return Button_val;
}



/*******************���Խ��溯��**************************/
void GUI_Duty(void)
{
    unsigned char i;
  /*********ϵͳ����***********/
  unsigned char static GUI_flag=0;     //���Խ������
  unsigned char static display_y=25;   //������������
  if(!KEY_Read(KEY0))                  //�ı����
  {
    delayms(10);
    if(!KEY_Read(KEY0))                //����ȷ��
    {
      TFTSPI_CLS(0);                   //����
      GUI_flag++;
      if(GUI_flag>2)                    //���ý���ҳ��
        GUI_flag=0;
      while(!KEY_Read(KEY0));
    }
  }
  /*********���Խ���#0***********/
  if(GUI_flag==0)
  {
     // OLED_Show_Frame80();//����ͷ����
      TFTSPI_BinRoad(0,0,LCDH, LCDW, (unsigned char *)Pixle);        // OLED��̬��ʾ����ͷͼ��
   for(i=img_y_max;i>=img_y_min;i--)
          {
            //OLED_PutPixel((mid_line[i]+24),i);                //oled������
//            OLED_PutPixel((left_point[i]),i);
//            OLED_PutPixel((right_point[i]),i);
          }
    display_y=Button_Duty(display_y);           //������������
    TFTSPI_Draw_Rectangle(1, display_y, 23,display_y,u16BLACK);   //���ƾ���
    TFTSPI_Draw_Rectangle(105, display_y, 127,display_y,u16BLACK);   //���ƾ���

/*���������oled����ʾ�����ֱ�־λ�������Ԫ��*/

        sprintf(txt, "garage_flag:%d", garage_flag);
        TFTSPI_P6X8Str(0, 10, txt,u16WHITE,u16BLUE);


           sprintf(txt, "garage_count:%d",garage_count);
           TFTSPI_P6X8Str(0, 11, txt,u16WHITE,u16BLUE);


        sprintf(txt, "white_black:%d",white_black);
        TFTSPI_P6X8Str(0, 12, txt,u16WHITE,u16BLUE);

              sprintf(txt, "black_white:%d",black_white);
              TFTSPI_P6X8Str(0, 13, txt,u16WHITE,u16BLUE);

       sprintf(txt, "garage_delay:%d",garage_delay);
       TFTSPI_P6X8Str(0, 14, txt,u16WHITE,u16BLUE);


  }
//  /*********���Խ���#1***********/
  else if(GUI_flag==1)
  {

      if(KEY_Read(DSW0))//���������ֵ
      {
      DJ_midpoint=Button_Duty(DJ_midpoint);   //�����ֵ����
      TFTSPI_P6X8Str(0,10, "DJ_midpoint",u16WHITE,u16BLUE);

      sprintf(txt,"DJ_midpoint:%d",DJ_midpoint);  //���Pֵ
      TFTSPI_P6X8Str(0,11,(float*)txt,u16WHITE,u16BLUE);
      }
      else//�������P
      {
      //speed_SW_flag=Button_Duty(speed_SW_flag);   //�ٶȵ�λѡ��
          TFTSPI_P6X8Str(0,10, "DJ_PWM",u16WHITE,u16BLUE);
      KP_A=Button_Duty(KP_A);



      sprintf(txt,"KP_A:%d",KP_A);  //���Pֵ
      TFTSPI_P6X8Str(0,11,(float*)txt,u16WHITE,u16BLUE);
      }

      sprintf(txt, "DJ_PWM:%d",DJ_PWM);   //tft��ʾ���PWM
      TFTSPI_P6X8Str(0,12, txt,u16WHITE,u16BLUE);
    /***�ٶȵ�λѡ��***/
      TFTSPI_P6X8Str(0,13,"Speed_SET",u16WHITE,u16BLUE);              //tft��ʾ�趨�ٶ�
      sprintf(txt, "%d", speed_SW_flag);   //��ʾ�ٶ�ѡ���־
      TFTSPI_P6X8Str(15,13, txt,u16WHITE,u16BLUE);

    if(speed_SW_flag>4)speed_SW_flag=1;
    speed_SW();                                 //�ٶȵ�λѡ����

  }
  else if(GUI_flag==2)
  {
      TFTSPI_P6X8Str(5,11,"START ENGINE!",u16WHITE,u16BLUE);         //һ������
    if(!KEY_Read(KEY2))
    {KEY_start_flag=1;}                         //������־ֵ��
    else;
    if(!KEY_start_flag)
        TFTSPI_P6X8Str(5,12,"    Loop    ",u16WHITE,u16BLUE);       //ͣ��
    else if(KEY_start_flag && KEY_start_time_flag<100)
        TFTSPI_P6X8Str(5,12,"    READY   ",u16WHITE,u16BLUE);       //׼��
    //else if(KEY_start_time_flag>100 && !stop_motors_flag)
    else if(KEY_start_time_flag>100)
        TFTSPI_P6X8Str(5,12,"    Voom!    ",u16WHITE,u16BLUE);      //������
    else
        TFTSPI_P6X8Str(5,12,"    STOP    ",u16WHITE,u16BLUE);       //ͣ��*/
  }
  else;
//  /************END**************/
}


