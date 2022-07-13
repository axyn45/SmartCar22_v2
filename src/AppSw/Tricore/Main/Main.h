/*!
  * @file     Main.h
  *
  * @brief    
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     Tab�� 4���ո�
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2020��6��11��
  */ 
#ifndef SRC_APPSW_TRICORE_MAIN_MAIN_H_
#define SRC_APPSW_TRICORE_MAIN_MAIN_H_

#include <stdint.h>



extern IfxCpu_mutexLock mutexCpu0InitIsOk;   /** CPU0 ��ʼ����ɱ�־λ  */

extern IfxCpu_mutexLock mutexTFTIsOk;        /** TFT18ʹ�ñ�־λ  */
/**
 * ��ʱ�� 5ms��50ms��־λ
 */
extern volatile unsigned char cpu1Flage5ms;
extern volatile unsigned char cpu1Flage50ms;

/* �����ٶ�  */
extern volatile signed short targetSpeed;
/* ���ϱ�־λ */
extern volatile unsigned char evadibleFlage;

int core0_main (void);
void CAR_Drive_duty(void);         //��������
#endif /* SRC_APPSW_TRICORE_MAIN_MAIN_H_ */
