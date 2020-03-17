/*
 * PWM.h
 *
 * Created: 2/17/2020 11:30:35 PM
 *  Author: Az
 */ 
#ifndef PWM_H_
#define PWM_H_
/*- INCLUDE --------------------------------------------------------------------------------------------------------------*/
#include "../../std_types.h"
#include "../../registers.h"
/*- DEFINES---------------------------------------------------------------------------------------------------------------*/
#define PWM_CH0               (0)
#define PWM_CH1A              (1)
#define PWM_CH1B              (2)
#define PWM_CH2               (3)

/*
#define	PWM_PRESCALER_NO	   (0)
#define	PWM_PRESCALER_8		(1)
#define	PWM_PRESCALER_32		(2)
#define	PWM_PRESCALER_64		(3)
#define	PWM_PRESCALER_128		(4)
#define	PWM_PRESCALER_256		(5)
#define	PWM_PRESCALER_1024	(6)
*/

/*---- TIMER 1 ----*/
#define T1_NORMAL_MODE           0x0000
#define T1_COMP_MODE_OCR1A_TOP   0x0008
#define T1_COMP_MODE_ICR1_TOP    0x0018
#define T1_FAST_PWM_NON_OCR1A    0X0318
#define T1_COMP_MODE_ICR1_BOTTOM 0x0010

#define T1_NO_CLOCK        0x0000
#define T1_PRESCALER_NO    0x0001
#define T1_PRESCALER_8     0x0002
#define T1_PRESCALER_64    0x0003
#define T1_PRESCALER_256   0x0004
#define T1_PRESCALER_1024  0x0005

#define  PWM_FREQ             (250)
/*- TYPEDEFS -------------------------------------------------------------------------------------------------------------*/
typedef struct strPwmCfg_t
{
   uint8_t Channel;
   uint8_t Prescaler;
}strPwmCfg_t;
/*- CONSTANTS ------------------------------------------------------------------------------------------------------------*/
extern strPwmCfg_t gstrPwmConfig;

/*- FUNCTIONS PROTOTYPES --------------------------------------------------------------------------------------------------*/
/*
*  Description: initialize the PWM configuration
*
*  @param strPwmCfg_t * Pwm_Cfg
*  
*  @return ERROR_STATUS
*/
extern ERROR_STATUS Pwm_Init(strPwmCfg_t *Pwm_Cfg);

/*
*  Description: starts the PWM on the dedicated channel with the required duty cycle and frequency
*
*  @param uint8_t Channel
*  @param uint8_t Duty
*  @param uint32_t Frequncy
*
*  @return ERROR_STATUS				
*/
extern ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy);

/*
*  Description: updates the duty cycle and frequency of the dedicated channel
*
*  @param uint8_t Channel
*  @param uint8_t Duty
*  @param uint32_t Frequncy
*
*  @return ERROR_STATUS
*/
extern ERROR_STATUS Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequncy);

/*
*  Description: responsible of Stopping the PWM by clearing the prescaler of the corresponding channel
*
*  @param uint8_t Channel
*
*  @return ERROR_STATUS
*/
extern ERROR_STATUS Pwm_Stop(uint8_t Channel);

#endif /* PWM_H_ */