#include"AD_sample.h"
/*********adc*****************/
uint16 ADC_0=0;
uint16 ADC_1=0;
uint16 ADC_2=0;
uint16 ADC_3=0;
uint16 ADC_4=0;
uint16 ADC_5=0;
uint16 AD_max[6] = {2500, 2500, 999, 999, 2500, 2500}; // �°��ӷŵ������궨���ֵ,�ᱻ����ˢ��
uint16 AD_min[6] = {120, 120, 999, 999, 120, 120}; // �°��Ӿ���Ҫ�궨��Сֵ,�ᱻ����ˢ��
uint16 Lleft1 = 0, Lleft2 = 0, Lright2 = 0, Lright1 = 0;  // ���ƫ����
uint16 mid1=0,mid2=0;
uint16 MagneticField = 0;     // �ų�ǿ��    magnetic field intensity,�ж�Բ���Ƿ����

/***********adc�ɼ��˲�********************/
void Get_ADC(void)
{
    uint16 ADC_0_1=0;
    uint16 ADC_1_1=0;
    uint16 ADC_2_1=0;
    uint16 ADC_3_1=0;
    uint16 ADC_4_1=0;
    uint16 ADC_5_1=0;
    uint16 i;
    for( i = 0; i < 12; i++)
    {
    ADC_0_1+=ADC_Read(ADC0);
    ADC_1_1+=ADC_Read(ADC1);
    ADC_2_1+=ADC_Read(ADC2);
    ADC_3_1+=ADC_Read(ADC3);
    ADC_4_1+=ADC_Read(ADC4);
    ADC_5_1+=ADC_Read(ADC5);
    }
    ADC_0 = ADC_0_1 / i;
    ADC_1 = ADC_1_1 / i;
    ADC_2 = ADC_2_1 / i;
    ADC_3 = ADC_3_1 / i;
    ADC_4 = ADC_4_1 / i;
    ADC_5 = ADC_5_1 / i;

    if (ADC_0 < AD_min[0])
        AD_min[0] =ADC_0;     // ˢ����Сֵ
       else if (ADC_0 > AD_max[0])
           AD_max[0] = ADC_0;     // ˢ�����ֵ

    if (ADC_1 < AD_min[1])
          AD_min[1] =ADC_1;     // ˢ����Сֵ
         else if (ADC_1 > AD_max[1])
             AD_max[1] = ADC_1;     // ˢ�����ֵ

    if (ADC_2 < AD_min[2])
            AD_min[2] =ADC_2;     // ˢ����Сֵ
           else if (ADC_2 > AD_max[2])
               AD_max[2] = ADC_2;     // ˢ�����ֵ

    if (ADC_3 < AD_min[3])
            AD_min[3] =ADC_3;     // ˢ����Сֵ
           else if (ADC_3 > AD_max[3])
               AD_max[3] = ADC_3;     // ˢ�����ֵ


    if (ADC_4 < AD_min[4])
          AD_min[4] =ADC_4;     // ˢ����Сֵ
         else if (ADC_4 > AD_max[4])
             AD_max[4] = ADC_4;     // ˢ�����ֵ

    if (ADC_5 < AD_min[5])
          AD_min[5] =ADC_5;     // ˢ����Сֵ
         else if (ADC_5 > AD_max[5])
             AD_max[5] = ADC_5;     // ˢ�����ֵ


    Lleft1 =  (ADC_0 - AD_min[0]) * 100 / (AD_max[0] - AD_min[0]);     // ��ƫ������һ����0--100����
    Lleft2 =  (ADC_1 - AD_min[1]) * 100 / (AD_max[1] - AD_min[1]);

    mid1 =  (ADC_2 - AD_min[2]) * 100 / (AD_max[2] - AD_min[2]);
    mid2 =  (ADC_3 - AD_min[3]) * 100 / (AD_max[3] - AD_min[3]);

    Lright2 = (ADC_4 -AD_min[4]) * 100 / (AD_max[4] - AD_min[4]);
    Lright1 = (ADC_5 -AD_min[5]) * 100 / (AD_max[5] - AD_min[5]);

    MagneticField=Lleft1 + Lleft2 + Lright2 + Lright1;// �ų�����ǿ��
}




void ADC_duty(void)
{
    mid_point[img_y_control]=(ADC_1*1+ADC_2*15+ADC_3*65+ADC_4*79)/(ADC_1+ADC_2+ADC_3+ADC_4);//��һ��������������
}




