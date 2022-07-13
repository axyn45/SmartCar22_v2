#include"garage.h"


/*****************车库***************************************/
void OutInGarage (uint8 inout, uint8 lr)//  inout 为1 入库  lr为1  右
{
    sint32 ps = 0;
    char txt[20];
    sprintf(txt, "start", Feed_speed);
    TFTSPI_P8X16Str(0, 5, txt,u16WHITE,u16BLACK);       //字符串显示
    if (lr)           // 1右出入库
    {
        if (inout)    // 1右入库
        {
            ps = Feed_flag;
            MotorCtrl4w(1500,1500,1500,1500);//3000

            while (Feed_flag < ps + 200)
                               {
                                   Feed_speed=ENC_GetCounter(ENC2_InPut_P33_7);//前进为正值//编码器4
                                   Feed_flag += Feed_speed;

                              }

                       ps = Feed_flag;
                       DJ_PID(80);    // 直行大约10cm
                       /*
                       ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //继续前进
                       ATOM_PWM_SetDuty(ATOMPWM4, 200, 12500);
                       */
                       MotorCtrl4w(200,200,200,200);

                       while (Feed_flag < ps + 700)
                       {
                           Feed_speed=ENC_GetCounter(ENC2_InPut_P33_7);//前进为正值//编码器4
                           Feed_flag += Feed_speed;

                      }

/*
                       ATOM_PWM_SetDuty(ATOMPWM5, 1000, 12500);
                       ATOM_PWM_SetDuty(ATOMPWM4, 1000, 12500);
*/
                       MotorCtrl4w(1000,1000,1000,1000);

            while (1);                   // 入库完毕，永久停车
        }
        else  // 0右出库
        {
            sprintf(txt, "start1", Feed_speed);
            TFTSPI_P8X16Str(0, 5, txt,u16WHITE,u16BLACK);       //字符串显示
            // 2020年新加出库元素，此处为盲走出库
            ps = Feed_flag;
            DJ_PID(40);    // 直行大约10cm

            ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //继续前进
            ATOM_PWM_SetDuty(ATOMPWM4, 1500, 12500);

            MotorCtrl4w(1500,1500,1500,1500);//3000
            sprintf(txt, "start2", Feed_speed);
            TFTSPI_P8X16Str(0, 5, txt,u16WHITE,u16BLACK);       //字符串显示
            while (Feed_flag < ps + 1400)
            {
                MotorCtrl4w(1500,1500,1500,1500);//3000

                sprintf(txt, "Feed_flag:%05d", Feed_flag);
                TFTSPI_P8X16Str(0, 7, txt,u16WHITE,u16BLACK);
                Feed_speed=ENC_GetCounter(ENC2_InPut_P33_7);//前进为正值//编码器4
                Feed_flag += Feed_speed;

           }
            sprintf(txt, "start3", Feed_speed);
            TFTSPI_P8X16Str(0, 6, txt,u16WHITE,u16BLACK);       //字符串显示
            ps = Feed_flag;
            DJ_PID(75);     // 舵机向右打死为出库做准备
            /*
            ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //继续前进
            ATOM_PWM_SetDuty(ATOMPWM4, 1500, 12500);
            */
            MotorCtrl4w(1500,1500,1500,1500);//3000

            while (Feed_flag < ps + 1600)
            {
                 Feed_speed=ENC_GetCounter(ENC2_InPut_P33_7);//前进为正值//编码器4
                 Feed_flag += Feed_speed;
            }
        }
    }
    else // 0：左出入库；
    {
        if (inout) // 1左入库
        {
             ps = Feed_flag;
            DJ_PID(40);  // 回中准备倒车
            /*ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //继续前进
            ATOM_PWM_SetDuty(ATOMPWM4, 2000, 12500);
            */
            MotorCtrl4w(2000,2000,2000,2000);//2000

            while (Feed_flag < ps + 2000) // 继续前进大约35cm
            {
                delayms(10);
            }
            /*ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);
            ATOM_PWM_SetDuty(ATOMPWM4, 1000, 12500);      // 反转刹车
            */
            MotorCtrl4w(1000,1000,1000,1000);//2000

            delayms(300);  //刹车时间可以整定
            ps = Feed_flag;
            DJ_PID(5);    // 舵机向左打死
//            ATOM_PWM_SetDuty(ATOMPWM5, 2000, 12500);  //后退
//            ATOM_PWM_SetDuty(ATOMPWM4, 0, 12500);
            MotorCtrl4w(2000,2000,2000,2000);//2000

            while (Feed_flag > ps - 2000) // 从停车位出库，大约要512编码器2000个脉冲，龙邱512带方向编码器1米5790个脉冲
            {
                delayms(10);
            }
            ps = Feed_flag;
            DJ_PID(40);  // 回中倒车
//            ATOM_PWM_SetDuty(ATOMPWM5, 2000, 12500);  //后退
//            ATOM_PWM_SetDuty(ATOMPWM4, 0, 12500);
            MotorCtrl4w(2000,2000,2000,2000);//2000

            while (Feed_flag > ps - 800)  // 小车后退为正值，并累加到出库为止
            {
                delayms(10);
            }
//            ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);
//            ATOM_PWM_SetDuty(ATOMPWM4, 1000, 12500);      // 反转刹车
            MotorCtrl4w(1000,1000,1000,1000);//2000

            delayms(300);                // 电机反转刹车，防止滑出赛道，时间根据速度调整
//            ATOM_PWM_SetDuty(ATOMPWM5, 1000, 12500);
//            ATOM_PWM_SetDuty(ATOMPWM4, 1000, 12500);      // 停车
            MotorCtrl4w(1000,1000,1000,1000);//2000

            while (1);                   // 入库完毕，永久停车
        }
        else  // 左出库
        {
            // 2020年新加出库元素，此处为盲走出库
            ps = Feed_flag;
            DJ_PID(40);    // 直行大约10cm
//            ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //继续前进
//            ATOM_PWM_SetDuty(ATOMPWM4, 2000, 12500);
            MotorCtrl4w(2000,2000,2000,2000);//2000

            while (Feed_flag < ps + 600)
            {
                delayms(10);
            }

            ps = Feed_flag;
            DJ_PID(5);     // 舵机向左打死为出库做准备
//            ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //继续前进
//            ATOM_PWM_SetDuty(ATOMPWM4, 3000, 12500);
            MotorCtrl4w(2000,2000,2000,2000);//2000

            while (Feed_flag < ps + 1200)
            {
                delayms(10);
            }
        }
    }
}


