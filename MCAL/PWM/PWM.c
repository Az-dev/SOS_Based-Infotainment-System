/*
 * PWM.c
 *
 * Created: 2/17/2020 11:30:51 PM
 *  Author: Az
 */
/*- INCLUDE --------------------------------------------------------------------------------------------------------------*/
#include "PWM.h"
/*- GLOBAL STATIC VARIABLES ----------------------------------------------------------------------------------------------*/
volatile static uint8_t gu8_t1Prescaler = 0;
/*- FUNCTION DEFINITIONS -------------------------------------------------------------------------------------------------*/
/*
*  Description: initialize the PWM configuration
*
*  @param strPwmCfg_t * Pwm_Cfg
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Pwm_Init(strPwmCfg_t *Pwm_Cfg)
{
   if(Pwm_Cfg != NULL)
   {
      switch(Pwm_Cfg->Channel)
      {
         case PWM_CH0:;
            /* timer 0 to be implemented if needed */
         break;
         case PWM_CH2:;
            /* timer 0 to be implemented if needed*/         
         break;
         case PWM_CH1A:
         case PWM_CH1B:
            /* Set prescaler of timer1 */
            gu8_t1Prescaler = Pwm_Cfg->Prescaler;
            /* Set TCCR1 */
            TCCR1 |= T1_COMP_MODE_ICR1_BOTTOM;
            TCCR1 |= 0xA000;  /*COM1A1/COM1B1 = 1 & COM1A0/COM1B0 = 0  -----> Clear OC1A/OC1B on compare match when up-counting. Set OC1A/OC1B on compare match when down counting.*/
         break;
      }
      return E_OK;
   }
   else  
   {
      return E_NOK;
   }
   
}

/*
*  Description: starts the PWM on the dedicated channel with the required duty cycle and frequency
*
*  @param uint8_t Channel
*  @param uint8_t Duty
*  @param uint32_t Frequncy
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy)
{
   /* Calculating TOP value */
   uint32_t au32_top_initial = (uint32_t)(CPU_F / (2 * Frequncy));
   /* Calculate initial value for OCR1A and OCR1B */
   uint32_t au32_ocr_initial = (uint32_t)(Duty * (au32_top_initial / 100));   
   /* Set OCR1A , OCR1B , ICR1 */
   switch(Channel)
   {
      case PWM_CH1A:
         OCR1A = (uint16_t)au32_ocr_initial;
      break;
      case PWM_CH1B:
         OCR1B = (uint16_t)au32_ocr_initial;
      break;
   }   
   ICR1  = (uint16_t)au32_top_initial;
   /* Set TCCR1B to start timer1 */
   TCCR1B |= gu8_t1Prescaler;   
   /* return success*/
   return E_OK;   
}

/*
*  Description: updates the duty cycle and frequency of the dedicated channel
*
*  @param uint8_t Channel
*  @param uint8_t Duty
*  @param uint32_t Frequncy
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequncy)
{
   /* Calculating TOP value */
   uint32_t au32_top_update = (uint32_t)(CPU_F / (2 * Frequncy));
   /* Calculate initial value for OCR1A and OCR1B */
   uint32_t au32_ocr1_update = (uint32_t)(Duty * (au32_top_update / 100));
   /* Update OCR1A , OCR1B */
   switch(Channel)
   {
      case PWM_CH1A:
         OCR1A = (uint16_t)au32_ocr1_update;         
      break;
      case PWM_CH1B:
         OCR1B = (uint16_t)au32_ocr1_update;
      break;
   }
   /* Update ICR1*/   
   ICR1  = (uint16_t)au32_top_update; 
   /* return success*/
   return E_OK;  
}

/*
*  Description: responsible of Stopping the PWM by clearing the prescaler of the corresponding channel
*
*  @param uint8_t Channel
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Pwm_Stop(uint8_t Channel)
{
   switch(Channel)
   {
      case PWM_CH1A:
      case PWM_CH1B:
         TCCR1B = T1_NO_CLOCK;
      break;
      case PWM_CH0:;
         /* Not used currently */
      break;      
      case PWM_CH2:;
         /* Not used currently */
      break;      
   }
   /* return success */
   return E_OK;   
} 


