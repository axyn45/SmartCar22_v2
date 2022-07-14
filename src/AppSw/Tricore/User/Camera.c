#include "Camera.h"
#include <include.h>
/***********************����ͷ�йز���***************************/
/*���ز���*/
uint8 img_y_max = 29;     //ɨ�����������ֵ
uint8 img_y_min = 10;     //ɨ����������Զֵ
uint8 img_y_control = 25; //ɨ�����������ֵ
/*���ݲ���*/
uint8 img_x = 40;       //ɨ�������
uint8 img_y = 30;       //ɨ��������
uint8 start_point = 40; //ɨ����ʼ��
uint8 mid_point[60];    //��ȡ������
unsigned char mid_line[60];
uint8 mid_point_His[10]; //��ʷ������
uint8 left_point[60];    //��߽�
uint8 right_point[60];   //�ұ߽�
uint8 leftState = 0;
uint8 rightState = 0;
uint8 init_len[60];  //��ʼ����������
uint8 point_len[60]; //ʵʱ��������
uint8 street_len;    //ֱ������

uint8 above_arr[LCDW];

uint8 cross_white[LCDW];
uint8 ru_num;
uint8 cross_zuowhite[LCDH];
uint8 cross_youwhite[LCDH];
uint8 cross_hangwhite[LCDH];

int lefthuandao_flag; //�����󻷵�����־λ
uint8 righthuandao_flag;
int shizi_flag; //����ʮ�ֱ�־λ
int shizi_count = 0;

int huandaoshibie = 1; //����ʶ��********************************************
int shizishibie = 0;   //ʮ��ʶ��
int chekushibie = 0;

uint8 podao_flag;  //�����µ���־λ
int sancha_flag;   //��������·�ڱ�־λ
uint8 garage_flag; //�����־λ

int podaostate = 0;
int leftstate = 0; //�󻷵��׶α�־λ
uint8 rightstate = 0;
int shizistate = 0;  //ʮ�ֽ׶α�־λ
int sanchastate = 0; //����·�ڱ�־λ

uint16 Left_huandao1; //������õ�ֵȥ�ж�,Ϊʲô��ֱ��ȥ�ж�,ֱ���ж��ڱ�������оͻ���ֵ�ַ�����쳣
uint16 Left_huandao2;
uint16 Left_huandao3;
uint16 Right_huandao1;
uint16 Right_huandao2;
uint16 Right_huandao3;
uint8 Right_huandao4;
uint16 mid_white;
uint16 mid_white1;
uint16 mid_white2;
uint16 zuo_white;
uint16 you_white;

uint8 Rightzhiline;
uint8 Leftzhiline;
uint8 white_black;
uint8 black_white;
uint8 garage_count = 0;
uint8 garage_delay = 0;
float old_Yaw;
float zhuanjiaozhi;
uint8 right_count;
uint8 left_count;
uint8 san_white;
uint8 biaozhun;
uint8 shang_white;
///�յ���
uint8 lx1, ly1, rx1, ry1, lx2, ly2, rx2, ry2, lx3, ly3, rx3, ry3, lx4, ly4, rx4, ry4;
int lx5, ly5, rx5, ry5, lx6, ly6, rx6, ry6, lx7, ly7, rx7, ry7, lx8, ly8, rx8, ry8, lx13, ly13, rx13, ry13, lx14, ly14, rx14, ry14;
int lx9, ly9, rx9, ry9, lx10, ly10, rx10, ry10, lx11, ly11, rx11, ry11, lx12, ly12, rx12, ry12;
uint8 mend_flag;
uint8 sancha_count = 0;
uint8 zebra_count = 0;
uint8 ruku_flag = 0; //*****************************************************

//                   ����һ���֣�ͼ�������֣�

/************************************************************

���������ơ�lost_line_right
����    �ܡ��Ҳ�ͼ���߼�麯��
����    ������
���� �� ֵ��-1Ϊδ���� ����Ϊ������ʼ��
��ʵ    ����lost_line_right();
��ע�������

************************************************************/

int Lost_line_right(void)
{
  uint8 i;
  for (i = 25; i > 5; i--)
    if (right_point[i] == 79)
      return i;
  return -1;
}

/************************************************************

���������ơ�lost_line_left
����    �ܡ����ͼ���߼�麯��
����    ������
���� �� ֵ��-1Ϊδ���� ����Ϊ������ʼ��
��ʵ    ����lost_line_left();
��ע�������

************************************************************/

int Lost_line_left(void)
{
  uint8 i;
  for (i = 25; i > 5; i--)
    if (left_point[i] == 0)
      return i;
  return -1;
}

/************************************************************

���������ơ�Horizontal_line
����    �ܡ�ˮƽѲ�ߺ���
����    ������
���� �� ֵ����
��ʵ    ����Horizontal_line();
��ע�������

************************************************************/

void Horizontal_line(void)
{
  uint8 i, j;
  if (Pixle[LCDH - 1][LCDW / 2] == 0)
  {
    if (Pixle[LCDH - 1][5] == 0xff)
      mid_point[LCDH] = 5;
    else if (Pixle[LCDH - 1][LCDW - 5] == 0xff)
      mid_point[LCDH] = LCDW - 5;
    else
      mid_point[LCDH] = LCDW / 2;
  }
  else
    mid_point[LCDH] = LCDW / 2;
  for (i = LCDH - 1; i > 0; i--)
  {
    for (j = mid_point[i + 1]; j >= 0; j--)
    {
      if (Pixle[i][j] == 0 || j == 0)
      {
        left_point[i] = j;
        break;
      }
    }
    for (j = mid_point[i + 1]; j <= LCDW - 1; j++)
    {
      if (Pixle[i][j] == 0 || j == LCDW - 1)
      {
        right_point[i] = j;
        break;
      }
    }
    mid_point[i] = (left_point[i] + right_point[i]) / 2;
    if (Pixle[i - 1][mid_point[i]] == 0 || i == 0)
    {
      for (j = i; j > 0; j--)
      {
        mid_point[j] = mid_point[i];
        left_point[j] = mid_point[i];
        right_point[j] = mid_point[i];
      }
      break;
    }
  }
}

/************************************************************
���������ơ�portrait_line
����    �ܡ�����Ѳ�ߺ���
����    ������
���� �� ֵ����
��ʵ    ����portrait_line();
��ע�������
***********************************************************/

void portrait_line(void)
{
  uint8 i, j;
  for (i = 0; i < LCDW; i++)
  {
    for (j = LCDH - 1; j >= 0; j--)
    {
      if (Pixle[j][i] == 0 || j == 0)
      {
        above_arr[i] = j;
        break;
      }
    }
  }
}

void connect_line(uint8 x1, uint8 y1, uint8 x2, uint8 y2) //���ߺ���������Ԫ����Ҫ���ߣ����ֶ���һ���߽磩
{

  short i, j, swap;
  float k;
  if (y1 > y2)
  {
    swap = x1;
    x1 = x2;
    x2 = swap;
    swap = y1;
    y1 = y2;
    y2 = swap;
  }
  if (x1 == x2)
  {
    for (i = y1; i < y2 + 1; i++)
      //      a[i]=y1++;
      Pixle[i][x1] = 0;
  }
  else if (y1 == y2)
  {
    for (i = x1; i < x2 + 1; i++)
      //      a[i]=x1++;
      Pixle[y1][i] = 0;
  }
  else
  {
    k = ((float)x2 - (float)x1) / ((float)y2 - (float)y1);
    for (i = y1; i <= y2; i++)
      Pixle[i][(short)(x1 + (i - y1) * k)] = 0;
  }
}

/************************************************************

���������ơ�Straight_line_judgment
����    �ܡ�ֱ���жϺ���
����    ����arrΪ��������
���� �� ֵ��1Ϊֱ�� 0Ϊ��ֱ��
��ʵ    ����Straight_line_judgment(left_arr);
��ע�����ֻ�ж�20-55
�����Ǻܺ���
************************************************************/
int sumR = 0;

void Straight_line_judgment(void)
{
  int i;

  for (i = 30; i > 15; i--)
  {
    if ((right_point[i] - right_point[i - 1] < 3) && right_point[i] - right_point[i - 1] > 0)
      sumR++;
  }
  if (sumR > 14)
  {
    Rightzhiline = 1;
    sumR = 0;
  }
  else
    Rightzhiline = 0;
}

void cunbaidian(void) //ÿһ�еİ�ɫ���������ÿһ�еİ�ɫ��������������ж�����Ԫ��
{
  for (uint8 lie = 0; lie < LCDW; lie++)
  {
    cross_white[lie] = 0;
    ru_num = 0;
  }
  //  //��׵� ��
  for (uint8 lie = 0; lie < LCDW; lie++)
  {
    for (uint8 hang = LCDH - 1; hang > 0; hang--) // 40
    {
      if (Pixle[hang][lie] == 1)
      {
        cross_white[lie]++;
      }
    }
  }

  /////////////////���� �׵�

  for (uint8 hang = 0; hang < LCDH; hang++)
  {
    cross_zuowhite[hang] = 0;
  }

  for (uint8 hang = LCDH - 1; hang > 0; hang--)
  {
    for (uint8 lie = 0; lie < LCDW / 2; lie++)
    {
      if (Pixle[hang][lie] == 1)
      {
        cross_zuowhite[hang]++;
      }
    }
  }

  /////////////////���� �׵�

  for (uint8 hang = 0; hang < LCDH; hang++)
  {
    cross_youwhite[hang] = 0;
  }

  for (uint8 hang = LCDH - 1; hang > 0; hang--)
  {
    for (uint8 lie = LCDW - 1; lie > LCDW / 2; lie--)
    {
      if (Pixle[hang][lie] == 1)
      {
        cross_youwhite[hang]++;
      }
    }
  }

  //////////////////////////////�а׵�
  for (uint8 hang = 0; hang < LCDH; hang++)
  {
    cross_hangwhite[hang] = 0;
  }

  //��׵�        ��
  for (uint8 hang = LCDH - 1; hang > 0; hang--)
  {
    for (uint8 lie = 0; lie < LCDW; lie++)
    {
      if (Pixle[hang][lie] == 1)
      {
        cross_hangwhite[hang]++;
      }
    }
    if (hang < 50)
    {
      if (cross_hangwhite[hang] > 110)
        ru_num++;
    }
  }
}

void misslinecount(void)
{
  right_count = 0;
  left_count = 0;

  for (uint8 i = 28; i > 10; i--)
  {
    if (left_point[i] < 1)
    {
      left_count++;
    }
    if (right_point[i] > 75)
    {
      right_count++;
    }
  }
}
/************************************************************

���������ơ�saidaokuandu
����    �ܡ��������Ȳ���
����    ������
���� �� ֵ����
��ʵ    ����
��ע�������

************************************************************/
void saidaokuandu(void)
{
  for (img_y = 29; img_y >= 10; img_y--)
  {
    point_len[img_y] = right_point[img_y] - left_point[img_y];

    if (left_point[img_y] < 5)
      lost_left[img_y] = 1; //�����ж�
    else
      lost_left[img_y] = 0;

    if (right_point[img_y] > 75)
      lost_right[img_y] = 1; //�Ҷ����ж�
    else
      lost_right[img_y] = 0;
  }
}
/************************************���Իع��������б��************************************/
// y = Ax+B
float B, A;
int regression(int startline, int endline)
{
  float SumUp = 0, SumDown = 0, avrX = 0, avrY = 0;
  int i = 0, SumX = 0, SumY = 0, SumLines = 0;

  SumLines = endline - startline; // startline Ϊ��ʼ�У� //endline ������ //SumLines

  for (i = startline; i < endline; i++)
  {
    SumX += mid_point[i];
    SumY += i; //����Middle_blackΪ������ߵ�����
  }
  avrX = SumX / SumLines; // X��ƽ��ֵ
  avrY = SumY / SumLines; // Y��ƽ��ֵ
  SumUp = 0;
  SumDown = 0;
  for (i = startline; i < endline; i++)
  {
    SumUp += (mid_point[i] - avrY) * (i - avrX);
    SumDown += (i - avrX) * (i - avrX);
  }
  if (SumDown == 0)
    B = 0;
  else
    B = (int)(SumUp / SumDown);
  A = (SumY - B * SumX) / SumLines; //�ؾ�
                                    // return B;  //����б��
}

/************************************************************

���������ơ�garage__dispose
����    �ܡ���⴦������
����    ������
���� �� ֵ����
��ʵ    ����garage__dispose();
��ע�������

************************************************************/

void garage__dispose(void) //ʶ������ߣ�ʶ��ڰ�����ﵽ��ֵ��Ϊ�����߱�־
{
  white_black = 0;
  black_white = 0;
  // garage_count= 0 ;

  ///////////��������ߣ����
  for (uint8 hang = 35; hang > 15; hang--)
  {
    for (uint8 lie = right_point[left_lost_flag + 5]; lie > 10; lie--)
    {
      if (Pixle[hang][lie] == 1 && Pixle[hang][lie - 2] == 0)
      {
        white_black++;
      }

      if (Pixle[hang][lie] == 0 && Pixle[hang][lie - 2] == 1)
      {
        black_white++;
      }
    }

    if (white_black > 15 && black_white > 15)
    {
      garage_count++;
      if (garage_count > 4)
      {
        garage_flag = 1;

        garage_delay = 1;

        shizi_flag = 0; //�ر�ʮ��ʶ��
        lefthuandao_flag = 0;
        leftstate = 0;
      }
    }
  }

  if (garage_flag && garage_delay > 20)
  {
    zebra_count++;
    garage_count = 0;
    garage_flag = 0;
    garage_delay = 0;
    chekushibie = 0;   //�رճ���ʶ��
    huandaoshibie = 1; //����ʶ��Բ��
    Horizontal_line();
  }

  if (zebra_count && garage_flag)
    ruku_flag = 1;
}

void saidaoyuansu()
{
  cunbaidian();

  san_white = (cross_hangwhite[20] + cross_hangwhite[21] + cross_hangwhite[22]) / 3; //
  zuo_white = (cross_zuowhite[20] + cross_zuowhite[21] + cross_zuowhite[22]) / 3;
  you_white = (cross_youwhite[20] + cross_youwhite[21] + cross_youwhite[22]) / 3;
  biaozhun = cross_hangwhite[1];
  mid_white = cross_white[40]; //����ʮ�ֺ�����·��
  mid_white1 = cross_white[41];
  mid_white2 = cross_white[39];
  shang_white = cross_hangwhite[10]; // 10
  Right_huandao2 = cross_white[65];  //    Right_huandao2=cross_white[70];
  Right_huandao3 = cross_white[10];

  if ((!lefthuandao_flag) && (!righthuandao_flag) && (!sancha_flag) && (!shizi_flag) && (!podao_flag))
  {
    if (chekushibie)
      garage__dispose();
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if ((!lefthuandao_flag) && (!righthuandao_flag) && (!sancha_flag) && (!shizi_flag) && (!garage_flag) && (!podao_flag)) //Ԫ�ض�û��ʶ�𵽣���ʼʶ��Ԫ��
  {
    if (right_count > 10 || left_count > 10) // �����ж������ ����Ԫ��ʶ��
    {

      ////////////////////////////////////�µ�
      if (point_len[10] > 40 && point_len[20] > 60)
      {
        podao_flag = 1;
        podaostate = 1;
        shizishibie++;
        chekushibie++;
      }
      ////////////////////////////////////ʮ��
      if (right_lost_flag != -1 && left_lost_flag != -1 && mid_white > 47 && right_count > 10 && left_count > 10)
      {
        if (shizishibie > 0)
          shizi_flag = 1;
      }

      ////////////////////////////////////�󻷵�Ԫ��

      //        if((right_lost_flag==-1||right_lost_flag>45)&&left_lost_flag!=-1)  //��߶��ߣ��ұ߲���
      //            {
      //                 if(mid_white>48&&Right_huandao2<44&&right_count<5)//����ʮ��,бʮ��
      //                    {
      //                        if(left_lost_flag<40)
      //                        {
      //                            if(left_count>10&&left_count<25&&Right_huandao2>34)                 //����СS��
      //                            {
      //                                if((right_point[20]-right_point[15]<13)&&(right_point[25]-right_point[20]<13))      // ������� ��֤���ұ���ֱ�����ǻ���
      //                                {
      //                                    if(huandaoshibie>0)//������֮��������ʶ��
      //                                    {
      //                                        lefthuandao_flag=1;                   //�����󻷵���־λ
      //                                        leftstate=1 ;                          //�󻷵�״̬1
      //                                    }
      //                                }
      //                            }
      //                        }
      //                    }
      //             }

      ////////////////////////////////////�һ���Ԫ��

      if ((left_lost_flag == -1 || left_lost_flag > 24) && right_lost_flag != -1) //�ұ߶��ߣ���߲���
      {
        if (right_lost_flag < 40)
        {
          if (right_count > 10 && right_count < 25) //����СS��
          {
            if ((left_point[10] - left_point[15] < 11) && (left_point[15] - left_point[20] < 11)) // ������� ��֤���ұ���ֱ�����ǻ���
            {
              if (huandaoshibie > 0)
              {
                if (left_point[20] < 20 && left_point[25] < 20) //��ֹ������ʶ�𻷵�
                {
                  righthuandao_flag = 1; //�����󻷵���־λ
                  rightstate = 1;        //�󻷵�״̬1
                }
              }
            }
          }
        }
      }

      //////////////////////////////////////����·��
      if (right_count > 10 && left_count > 10 && (mid_white <= 45 || mid_white1 <= 45 || mid_white2 <= 45) && shang_white < 32) //���߶������м�׵�������ʮ��
      {
        sancha_flag = 1;
        sanchastate = 1;
      }
    }
  }
  else
  {
    shizi_flag = 0;
  }
  podao_dispose();
  crossroads_dispose();
  roadabout_dispose();
  roadjunction_dispose();
}

/************************************************************

���������ơ�podao_dispose
����    �ܡ�podao��������
����    ������
���� �� ֵ����
��ʵ    ����podao_dispose();
��ע�������

************************************************************/
void podao_dispose(void)
{
  if (podao_flag)
  {
    switch (podaostate)
    {
    case 1:
      if (point_len[10] > 17 && point_len[10] < 24) //ֱ������19��59
        podaostate = 2;
      break;

    case 2:
    {

      podaostate = 0;
    }
    break;
    }
    if (point_len[15] > 40 && point_len[15] < 50 && point_len[20] > 40 && point_len[20] < 70)

      podao_flag = 0;
    podaostate = 0;
  }
}
/************************************************************

���������ơ�crossroads_dispose
����    �ܡ�ʮ�ִ�������
����    ������
���� �� ֵ����
��ʵ    ����crossroads_dispose();
��ע�������

************************************************************/

extern int left_lost_flag;
extern int right_lost_flag;

void crossroads_dispose(void)
{
  int i, max = 1, maxi, min = LCDW, mini;
  //������Ҷ���ͬʱ��������Ϊʮ���������
  if (shizi_flag)
  {
    if (left_lost_flag > 40) //�����������������������������������������������������������������������������������������������µ�
    {
      lx1 = 3;
      ly1 = 59;
    }
    else
    {
      for (i = 45; i > 10; i--)
      {
        if (left_point[i] > max && i > left_lost_flag)
        {
          max = left_point[i];
          maxi = i;
        }
      }
      lx1 = max;
      ly1 = maxi;
    }
    if (right_lost_flag > 56) //�����������������������������������������������������������������������������������������������µ�
    {
      rx1 = LCDW - 3;
      ry1 = 59;
    }
    else
    {
      for (i = 45; i > 10; i--)
      {
        if (right_point[i] < min && i > right_lost_flag)
        {
          min = right_point[i];
          mini = i;
        }
      }
      rx1 = min;
      ry1 = mini;
    }
    for (i = 4; i < LCDW / 2 - 3; i++) //���������������������������������������������������������������������������������������������������ϵ�
    {
      if (above_arr[i] > above_arr[i + 2] && above_arr[i + 2] > above_arr[i + 4] && above_arr[i] < left_lost_flag && above_arr[i] < ly1)
      {
        lx2 = i;
        ly2 = above_arr[i];
        connect_line(3, 59, lx2, ly2);
        ; // connect_line(lx1,ly1,lx2,ly2);
        // mend_flag=1;
        Horizontal_line();
        break;
      }
    }
    for (i = LCDW - 3; i > LCDW / 2 - 3; i--) //���������������������������������������������������������������������������������������������������ϵ�
    {
      if (above_arr[i] > above_arr[i - 2] && above_arr[i - 2] > above_arr[i - 4] && above_arr[i] < right_lost_flag && above_arr[i] < ry1)
      {
        rx2 = i;
        ry2 = above_arr[i];
        connect_line(77, 59, rx2, ry2);
        // mend_flag=1;
        Horizontal_line();
        break;
      }
    }
  }
  //  if(right_lost_flag ==-1&&left_lost_flag==-1&&right_count<10&&left_count<10)
  //       {
  //         shizi_flag = 0;
  //
  //      }
}

/************************************************************

���������ơ�roadabout_dispose
����    �ܡ�����Ԫ�ش�������
����    ������
���� �� ֵ����
��ʵ    ����roadabout_dispose();
��ע�������

************************************************************/

void roadabout_dispose(void)
{
  Left_huandao1 = cross_white[2];
  Left_huandao2 = cross_white[4];
  Left_huandao3 = cross_white[6];
  Right_huandao1 = cross_white[70];

  if (lefthuandao_flag == 1)
  {

    switch (leftstate)
    {
    case 1:                   //��һ�ζ��ߣ����½ǹյ���40�����ҿ�ʼ����
      if (Left_huandao1 < 40) //һֱ�����Բ���ߵ�50�У�����ڶ��׶�
      {
        leftstate = 2;
      }
      break;

    case 2:

      if (Left_huandao1 > 40) //���½�ΪԲ��
      {
        leftstate = 4;
        huandaoshibie = 0;
      }

      break;

    case 4: //����
      if (Right_huandao1 < 15)
      {
        leftstate = 5;
      }
      break;

    case 5: //���������ߣ�������������
      if (Right_huandao1 > 29)
      {
        leftstate = 6;
      }
      break;

    case 6:
      if (right_lost_flag == -1)
      {
        leftstate = 0;
        lefthuandao_flag = 0;
      }
    }

    if (leftstate == 1) //����ǰ�����յ�����
    {
      int max = -1, maxi, min = LCDW, mini;
      if (left_lost_flag > 56) //�����������������������������������������������������������������������������������������������µ�
      {
        lx4 = 3;
        ly4 = 59;
      }
      else
      {
        for (uint8 i = 59; i > 0; i--)
        {
          if (left_point[i] > max && i > left_lost_flag)
          {
            max = left_point[i];
            maxi = i;
          }
        }
        lx4 = max;
        ly4 = maxi;
      }

      for (uint8 i = 1; i < LCDH - 3; i++) //����������������������������������������������������������������������������������������������������Բ����
      {
        if (left_point[i] < left_point[i + 1] && left_point[i + 1] > left_point[i + 2] && left_point[i + 1] > lx4)
        {
          ly5 = i + 1;
          lx5 = left_point[i + 1];
          break;
        }
      }

      connect_line(lx4, ly4 - 20, lx5, ly5);
      Horizontal_line();
    }

    //��ڲ���
    if (leftstate == 4)
    {
      for (uint8 i = 4; i < 58; i++) //���������������������������������������������������������������������������������������������������ϵ�
      {
        if (above_arr[i] > above_arr[i + 1] && above_arr[i + 1] > above_arr[i + 2] && above_arr[i] < left_lost_flag) //
        {
          lx7 = i;
          ly7 = above_arr[i];
          break;
        }
      }
      connect_line(lx7 + 15, ly7, 79, 40);
      Horizontal_line();
      //���ϵ����ӵ����µ�
    }

    if (leftstate == 6)
    {
      int min = LCDW - 2, mini;

      if (right_lost_flag > 56) //�����������������������������������������������������������������������������������������������µ�
      {
        lx8 = LCDW - 3;
        ly8 = 59;
      }
      else
      {
        for (uint8 i = 55; i > 25; i--)
        {
          if (right_point[i] < right_point[i + 1] && i > right_lost_flag)
          {
            min = right_point[i];
            mini = i;
          }
        }
        lx8 = min;
        ly8 = mini;
      }

      connect_line(40, 20, 70, 55);
      Horizontal_line();
    }
  }

  ////�һ���

  if (righthuandao_flag == 1)
  {

    switch (rightstate)
    {
    case 1:                    //��һ�ζ��ߣ����½ǹյ���40�����ҿ�ʼ����
      if (Right_huandao1 < 41) //һֱ�����Բ���ߵ�50�У�����ڶ��׶�
      {
        rightstate = 2;
      }
      break;

    case 2:
      if (Right_huandao1 > 47) //���½�ΪԲ��
      {
        rightstate = 4;
        huandaoshibie = 0;
      }
      break;

    case 4: //����
      if (Left_huandao1 < 28)
      {
        rightstate = 5;
      }
      break;

    case 5: //���������ߣ�������������
      if (Left_huandao1 > 38)
      {
        rightstate = 6;
      }
      break;

    case 6:
      if (left_lost_flag == -1) //������
      {

        rightstate = 7;
      }
      break;

    case 7:
    {
      if (right_lost_flag == -1)
      {
        rightstate = 0;
        righthuandao_flag = 0;
      }
    }
    }

    if (rightstate == 4)
    {

      for (uint8 i = 79; i > 20; i--) //���������������������������������������������������������������������������������������������������ϵ�
      {
        if (above_arr[i] > above_arr[i - 1] && above_arr[i - 1] > above_arr[i - 2] && above_arr[i] < right_lost_flag) //
        {
          rx7 = i;
          ry7 = above_arr[i];
          break;
        }
      }
      connect_line(rx7 - 15, ry7, 1, 40); //���ϵ����ӵ����µ�
      Horizontal_line();
    }

    if (rightstate == 6)
    {
      int max = 0, maxi = LCDW - 1;

      if (left_lost_flag > 56) //�����������������������������������������������������������������������������������������������µ�
      {
        rx8 = 3;
        ry8 = 59;
      }
      else
      {
        for (uint8 i = 59; i > 0; i--)
        {
          if (left_point[i] > max && i > left_lost_flag)
          {
            max = left_point[i];
            maxi = i;
          }
        }
        rx8 = max;
        ry8 = maxi;
        connect_line(30, 15, 1, 40);
        Horizontal_line();
      }
    }
  }
}

///************************************************************
//
//���������ơ�roadjunction_dispose
//����    �ܡ�����·�ڴ�������
//����    ������
//���� �� ֵ����
//��ʵ    ����roadjunction_dispose();
//��ע�������

//************************************************************/

void roadjunction_dispose(void)
{

  if (sancha_flag)
  {

    int max = 1, maxi, min = LCDW, min_0 = 1, mini;
    switch (sanchastate)
    {
      //            case 1:
      //            if(shang_white<38)//mid_white<38
      //            {
      //             sanchastate = 2;
      //            }
      //            break;

    case 1:
      if (right_lost_flag == -1 || left_lost_flag == -1)
      {
        sanchastate = 4;
      }
      break;

    case 4:
      if (mid_white > 48)
      {
        sanchastate = 0;
        sancha_flag = 0;
        sancha_count++;
      }
      break;
    }

    if (sanchastate == 1) //  ʶ������·�ڣ����½��������Ϲյ�
    {
      if (sancha_count < 2)
      {
        if (right_lost_flag > 55) //�����������������������������������������������������������������������������������������������µ�
        {
          lx11 = LCDW - 3;
          ly11 = 59;
        }
        else
        {
          for (uint8 i = 59; i > 35; i--)
          {
            if (right_point[i] < min && i > right_lost_flag)
            {
              min = right_point[i];
              mini = i;
            }
          }
          lx11 = min;
          ly11 = mini;
        }

        for (uint8 i = 40; i < 75; i++) //�������������������������������������������������������������������������������������������������ϵ�
        {
          if (above_arr[i - 4] < above_arr[i + 1] && above_arr[i + 1] > above_arr[i + 5] && above_arr[i + 1] < ly11)
          {
            lx12 = i + 1;
            ly12 = above_arr[i + 1];
            break;
          }
        }
      }
      if (sancha_count >= 2)
      {
        if (left_lost_flag > 55) //�����������������������������������������������������������������������������������������������µ�
        {
          lx11 = 3;
          ly11 = 59;
        }
        else
        {
          for (uint8 i = 59; i > 35; i--)
          {
            if (left_point[i] > min_0 && i > left_lost_flag)
            {
              min_0 = left_point[i];
              mini = i;
            }
          }
          lx11 = min_0;
          ly11 = mini;
        }

        for (uint8 i = 20; i < 65; i++) //�������������������������������������������������������������������������������������������������ϵ�
        {
          if (above_arr[i - 4] < above_arr[i + 1] && above_arr[i + 1] > above_arr[i + 6] && above_arr[i + 1] < ly11)
          {
            lx12 = i + 1;
            ly12 = above_arr[i + 1];
            break;
          }
        }
      }
      if (sancha_count == 4)
        sancha_count = 0;
      connect_line(lx11, ly11, lx12, ly12);
      Horizontal_line();
    }
  }
}
