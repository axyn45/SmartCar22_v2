#include "garage.h"

/*****************����***************************************/
void OutInGarage(uint8 inout, uint8 lr) //  inout Ϊ1 ���  lrΪ1  ��
{
    sint32 ps = 0;
    char txt[20];
    sprintf(txt, "start", Feed_speed);
    TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK); //�ַ�����ʾ
    if (lr)                                         // 1�ҳ����
    {
        if (inout) // 1�����
        {
            ps = Feed_flag;
            MotorCtrl4w(1500, 1500, 1500, 1500); // 3000

            while (Feed_flag < ps + 200)
            {
                Feed_speed = ENC_GetCounter(ENC2_InPut_P33_7); //ǰ��Ϊ��ֵ//������4
                Feed_flag += Feed_speed;
            }

            ps = Feed_flag;
            DJ_PID(80); // ֱ�д�Լ10cm
            /*
            ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //����ǰ��
            ATOM_PWM_SetDuty(ATOMPWM4, 200, 12500);
            */
            MotorCtrl4w(200, 200, 200, 200);

            while (Feed_flag < ps + 700)
            {
                Feed_speed = ENC_GetCounter(ENC2_InPut_P33_7); //ǰ��Ϊ��ֵ//������4
                Feed_flag -= Feed_speed;
            }

            /*
                                   ATOM_PWM_SetDuty(ATOMPWM5, 1000, 12500);
                                   ATOM_PWM_SetDuty(ATOMPWM4, 1000, 12500);
            */
            MotorCtrl4w(1000, 1000, 1000, 1000);

            while (1)
                ; // �����ϣ�����ͣ��
        }
        else // 0�ҳ���
        {
            sprintf(txt, "start1", Feed_speed);
            TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK); //�ַ�����ʾ
            // 2020���¼ӳ���Ԫ�أ��˴�Ϊä�߳���
            ps = Feed_flag;
            DJ_PID(40);    // ֱ�д�Լ10cm
//
//            ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //����ǰ��
//            ATOM_PWM_SetDuty(ATOMPWM4, 1500, 12500);

            MotorCtrl4w(1500, 1500, 1500, 1500); // 3000
            sprintf(txt, "start2", Feed_speed);
            TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK); //�ַ�����ʾ
            while (Feed_flag < ps + 1400)
            {
                MotorCtrl4w(1500, 1500, 1500, 1500); // 3000

                sprintf(txt, "Feed_flag:%05d", Feed_flag);
                TFTSPI_P8X16Str(0, 7, txt, u16WHITE, u16BLACK);
                Feed_speed = ENC_GetCounter(ENC2_InPut_P33_7); //ǰ��Ϊ��ֵ//������4
                Feed_flag += Feed_speed;
            }
            sprintf(txt, "start3", Feed_speed);
            TFTSPI_P8X16Str(0, 6, txt, u16WHITE, u16BLACK); //�ַ�����ʾ
            ps = Feed_flag;
            DJ_PID(70);     // ������Ҵ���Ϊ������׼��
            /*
            ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //����ǰ��
            ATOM_PWM_SetDuty(ATOMPWM4, 1500, 12500);
            */
            MotorCtrl4w(1500, 1500, 1500, 1500); // 3000

            while (Feed_flag < ps + 1600)
            {
                Feed_speed = ENC_GetCounter(ENC2_InPut_P33_7); //ǰ��Ϊ��ֵ//������4
                Feed_flag += Feed_speed;
            }
        }
    }
    else // 0�������⣻
    {
        if (inout) // 1�����
        {
            ps = Feed_flag;
            DJ_PID(40); // ����׼������
            /*ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //����ǰ��
            ATOM_PWM_SetDuty(ATOMPWM4, 2000, 12500);
            */
            MotorCtrl4w(1500, 1500, 1500, 1500); // 2000

            while (Feed_flag < ps + 2000) // ����ǰ����Լ35cm
            {
                delayms(10);
            }
            /*ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);
            ATOM_PWM_SetDuty(ATOMPWM4, 1000, 12500);      // ��תɲ��
            */
            MotorCtrl4w(1500, 1500, 1500, 1500); // 2000

            delayms(300); //ɲ��ʱ���������
            ps = Feed_flag;
            DJ_PID(5);                           // ����������
                                                 //            ATOM_PWM_SetDuty(ATOMPWM5, 2000, 12500);  //����
                                                 //            ATOM_PWM_SetDuty(ATOMPWM4, 0, 12500);
            MotorCtrl4w(1500, 1500, 1500, 1500); // 2000

            while (Feed_flag > ps - 2000) // ��ͣ��λ���⣬��ԼҪ512������2000�����壬����512�����������1��5790������
            {
                delayms(10);
            }
            ps = Feed_flag;
            DJ_PID(40);                          // ���е���
                                                 //            ATOM_PWM_SetDuty(ATOMPWM5, 2000, 12500);  //����
                                                 //            ATOM_PWM_SetDuty(ATOMPWM4, 0, 12500);
            MotorCtrl4w(1500, 1500, 1500, 1500); // 2000

            while (Feed_flag > ps - 800) // С������Ϊ��ֵ�����ۼӵ�����Ϊֹ
            {
                delayms(10);
            }
            //            ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);
            //            ATOM_PWM_SetDuty(ATOMPWM4, 1000, 12500);      // ��תɲ��
            MotorCtrl4w(1500, 1500, 1500, 1500); // 2000

            delayms(300);                        // �����תɲ������ֹ����������ʱ������ٶȵ���
                                                 //            ATOM_PWM_SetDuty(ATOMPWM5, 1000, 12500);
                                                 //            ATOM_PWM_SetDuty(ATOMPWM4, 1000, 12500);      // ͣ��
            MotorCtrl4w(1500, 1500, 1500, 1500); // 2000

            while (1)
                ; // �����ϣ�����ͣ��
        }
        else // �����
        {
            // 2020���¼ӳ���Ԫ�أ��˴�Ϊä�߳���
            ps = Feed_flag;
            DJ_PID(40);                          // ֱ�д�Լ10cm
                                                 //            ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //����ǰ��
                                                 //            ATOM_PWM_SetDuty(ATOMPWM4, 2000, 12500);
            MotorCtrl4w(1500, 1500, 1500, 1500); // 2000

            while (Feed_flag < ps + 600)
            {
                delayms(10);
            }

            ps = Feed_flag;
            DJ_PID(5);                           // ����������Ϊ������׼��
                                                 //            ATOM_PWM_SetDuty(ATOMPWM5, 0, 12500);  //����ǰ��
                                                 //            ATOM_PWM_SetDuty(ATOMPWM4, 3000, 12500);
            MotorCtrl4w(1500, 1500, 1500, 1500); // 2000

            while (Feed_flag < ps + 1200)
            {
                delayms(10);
            }
        }
    }
}
