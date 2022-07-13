#include"debug.h"


char txt[16];                  //oled显示替换字符
int start_flag=0;

//extern int DJ_MID;
//                      下一部分：调试界面部分

/********************按键设置行数****************************/
uint32 Button_Duty(uint32 Button_val)     //按键计数函数
{
  if(!KEY_Read(KEY2))                   //按键加
  {
      delayms(10);
    if(!KEY_Read(KEY2))                 //二次判断
    {
      Button_val++;
      TFTSPI_CLS(u16BLACK);                   //清屏
      if(Button_val>10000)                //限幅
        Button_val=10000;
      while(!KEY_Read(KEY2));
    }
  }
  if(!KEY_Read(KEY1))                   //按键减
  {
      delayms(10);
    if(!KEY_Read(KEY1))                 //二次判断
    {
      Button_val--;
      TFTSPI_CLS(u16BLACK);                   //清屏
      if(Button_val<2)                  //限幅
        Button_val=1;
      while(!KEY_Read(KEY1));
    }
  }
   return Button_val;
}



/*******************调试界面函数**************************/
void GUI_Duty(void)
{
    unsigned char i;
  /*********系统设置***********/
  unsigned char static GUI_flag=0;     //调试界面变量
  unsigned char static display_y=25;   //调试行数变量
  if(!KEY_Read(KEY0))                  //改变界面
  {
    delayms(10);
    if(!KEY_Read(KEY0))                //二次确认
    {
      TFTSPI_CLS(0);                   //清屏
      GUI_flag++;
      if(GUI_flag>2)                    //设置界面页数
        GUI_flag=0;
      while(!KEY_Read(KEY0));
    }
  }
  /*********调试界面#0***********/
  if(GUI_flag==0)
  {
     // OLED_Show_Frame80();//摄像头边线
      TFTSPI_BinRoad(0,0,LCDH, LCDW, (unsigned char *)Pixle);        // OLED动态显示摄像头图像
   for(i=img_y_max;i>=img_y_min;i--)
          {
            //OLED_PutPixel((mid_line[i]+24),i);                //oled画中线
//            OLED_PutPixel((left_point[i]),i);
//            OLED_PutPixel((right_point[i]),i);
          }
    display_y=Button_Duty(display_y);           //按键设置行数
    TFTSPI_Draw_Rectangle(1, display_y, 23,display_y,u16BLACK);   //绘制矩形
    TFTSPI_Draw_Rectangle(105, display_y, 127,display_y,u16BLACK);   //绘制矩形

/*这里可以在oled上显示出各种标志位，方便调元素*/

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
//  /*********调试界面#1***********/
  else if(GUI_flag==1)
  {

      if(KEY_Read(DSW0))//调整舵机中值
      {
      DJ_midpoint=Button_Duty(DJ_midpoint);   //舵机中值整定
      TFTSPI_P6X8Str(0,10, "DJ_midpoint",u16WHITE,u16BLUE);

      sprintf(txt,"DJ_midpoint:%d",DJ_midpoint);  //舵机P值
      TFTSPI_P6X8Str(0,11,(float*)txt,u16WHITE,u16BLUE);
      }
      else//调整舵机P
      {
      //speed_SW_flag=Button_Duty(speed_SW_flag);   //速度档位选择
          TFTSPI_P6X8Str(0,10, "DJ_PWM",u16WHITE,u16BLUE);
      KP_A=Button_Duty(KP_A);



      sprintf(txt,"KP_A:%d",KP_A);  //舵机P值
      TFTSPI_P6X8Str(0,11,(float*)txt,u16WHITE,u16BLUE);
      }

      sprintf(txt, "DJ_PWM:%d",DJ_PWM);   //tft显示舵机PWM
      TFTSPI_P6X8Str(0,12, txt,u16WHITE,u16BLUE);
    /***速度档位选择***/
      TFTSPI_P6X8Str(0,13,"Speed_SET",u16WHITE,u16BLUE);              //tft显示设定速度
      sprintf(txt, "%d", speed_SW_flag);   //显示速度选择标志
      TFTSPI_P6X8Str(15,13, txt,u16WHITE,u16BLUE);

    if(speed_SW_flag>4)speed_SW_flag=1;
    speed_SW();                                 //速度档位选择函数

  }
  else if(GUI_flag==2)
  {
      TFTSPI_P6X8Str(5,11,"START ENGINE!",u16WHITE,u16BLUE);         //一键启动
    if(!KEY_Read(KEY2))
    {KEY_start_flag=1;}                         //启动标志值置
    else;
    if(!KEY_start_flag)
        TFTSPI_P6X8Str(5,12,"    Loop    ",u16WHITE,u16BLUE);       //停车
    else if(KEY_start_flag && KEY_start_time_flag<100)
        TFTSPI_P6X8Str(5,12,"    READY   ",u16WHITE,u16BLUE);       //准备
    //else if(KEY_start_time_flag>100 && !stop_motors_flag)
    else if(KEY_start_time_flag>100)
        TFTSPI_P6X8Str(5,12,"    Voom!    ",u16WHITE,u16BLUE);      //启动！
    else
        TFTSPI_P6X8Str(5,12,"    STOP    ",u16WHITE,u16BLUE);       //停车*/
  }
  else;
//  /************END**************/
}


