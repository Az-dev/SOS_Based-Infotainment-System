/*
 * SwICU.c
 *
 * Created: 2/18/2020 8:57:03 PM
 *  Author: Az
 */ 
/*- INCLUDES -----------------------------------------------------------------------------------------------------------------------*/
#include "../SwICU/SwICU.h"
#include "../SwDelay/SwDelay.h"
#include "../../MCAL/Timer/Timer.h"
#include "../../MCAL/Timer/Timer_Cfg.h"
/*- GLOBAL VARIABLES DEFINITIONS ---------------------------------------------------------------------------------------------------*/
volatile static uint8_t gu8_onFallPulseCapture_flag = 0;  /* this flag is when a Rising-to-Falling pulse is captured */
volatile static uint16_t gu16_Icu_Time; 
/*
volatile uint8_t gu_distance_read_flag = LOW;
*/
/*- FUNCTION DEFINITIONS ----------------------------------------------------------------------------------------------------------*/
/*
*  Description  : Initializes the ICU by initializing the timer and enabling the global interrupt
*
*  @param strIcuCfg_t * Icu_Cfg
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Icu_Init(strIcuCfg_t * Icu_Cfg)
{
   /** Debug Point **/
   PORTB_DIR = 0xf0;
   /*---------------*/
   switch(Icu_Cfg->ICU_Ch_Timer)
   {
      case ICU_TIMER_CH0:
         /* not used for now */
      break;
      case ICU_TIMER_CH1:
         /* not used for now */
      break;
      case ICU_TIMER_CH2:
         switch(Icu_Cfg->ICU_Ch_No)
         {
            case ICU_CH0:
               /* not used for now */
            break;
            case ICU_CH1:
               /* not used for now */
            break;
            case ICU_CH2:
               /* Initialize Timer 2 */
               Timer_Init(&gstrTimerConfig);
               /* Set Global Interrupt */
               sei();               
               /*Disable INT2*/               
               //GICR &= ~(BIT5);
               /*Set ISC2 to (1) : that will fire INT2 on rising edge */               
               //MCUCSR |= BIT6;
               /*Reset INTF2 flag bit by setting 1*/               
               //GIFR |= BIT5;
               /*Enable INT2*/               
               //GICR |= (BIT5);               
            break;
         }                  
      break;
   }
   /* return success */
   return E_OK;
}

/*
*  Description	: calculates the time between 2 edges
*
*  @param uint8_t Icu_Channel
*  @param uint8_t Icu_EdgeToEdge
*  @param uint32_t * Icu_Time      (I/O param)
*  @return ERROR_STATUS
*/
ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time)
{ 
   switch(Icu_Channel)
   {
      case ICU_CH0:
         /*-- Not used for now --*/
      break;
      case ICU_CH1:
         /*-- Not used for now --*/
      break;
      case ICU_CH2:
         /* Selecting working edge on which the interrupt will be configured */
         switch(Icu_EdgeToEdge)
         {
            case ICU_RISE_TO_RISE:  /*-- Input will be captured between every Rising-to-Rising edges --*/
               /*-- Not used for now --*/
            break;
            case ICU_FALE_TO_RISE:  /*-- Input will be captured between every Falling-to-Rising edges --*/
               /*- Changing Edges Procedure ---------*/
               /* 1 - Disable INT2 */
               GICR &= ~(BIT5);
               /* 2 - Set ISC2 to (0) : that will fire INT2 on falling edge --*/
               MCUCSR &= (~BIT6);
               /* 3 - Reset INTF2 flag bit by setting 1 --*/
               GIFR |= BIT5;
               /* 4 - Enable INT2 --*/
               GICR |= (BIT5);               
            break;
            case ICU_RISE_TO_FALL:  /*-- Input will be captured between every Rising-to-Falling edges --*/
               /*- Changing Edges Procedure ---------*/
               /* 1 - Disable INT2 */
               GICR &= ~(BIT5);
               /* 2 - Set ISC2 to (1) : that will fire INT2 on rising edge */
               MCUCSR |= BIT6;
               /* 3 - Reset INTF2 flag bit by setting 1 */
               GIFR |= BIT5;
               /* 4 - Enable INT2 */
               GICR |= (BIT5);
               /** Debug Point **/
               //PORTB_DATA = 1<<4 ; --> tested the ICU_RISE_TO_FALL case success
               /*---------------*/                                       
            break;
         }         
      break;
   }
   /*--- Polling gu_starting_edge to detect when to read ---*/
   while(gu8_onFallPulseCapture_flag == 0);
   /* Rest the flag again */
   gu8_onFallPulseCapture_flag = 0;
   /* read time of the pulse */   
   *Icu_Time = gu16_Icu_Time;  
   /* return success */
   return E_OK;
}

/*** INT2 ISR **********************************************************************************************************************/
ISR_INT2()
{
   if(MCUCSR & BIT6)  /* if ISC2 is set --> Rising edge */
   {
      /** Debug Point **/
      //PORTB_DATA |= 1<<5 ;      
      /*---------------*/           
      /*-- Start timer2 -------------------*/
      Timer_Start(TIMER_2,0);
      /*-- Change edge Procedure ----------*/
      /* 1 - Disable INT2 -----------------*/
      GICR &= ~(BIT5);
      /* 2 - Set ISC2 to (0) : that will fire INT2 on falling edge --*/
      MCUCSR &= (~BIT6);
      /* 3 - Reset INTF2 flag bit by setting 1 --*/
      GIFR |= BIT5;
      /* 4 - Enable INT2 --*/
      GICR |= (BIT5);
      /** Debug Point **/
      //softwareDelayMs(5);
      //PORTB_DATA |= 0<<5 ;
      /*---------------*/                        
   }
   else if(!(MCUCSR & BIT6)) /* if ISC2 is set to (0) --> Falling Edge */ /* assert its value !!!??*/
   {
      /** Debug Point **/      
      //PORTB_DATA = 1<<4 ;      
      /*---------------*/
      /*stop timer counter*/
      Timer_Stop(TIMER_2);      
      /*read TCNT2*/
      Timer_GetValue(TIMER_2,(uint16_t *)&gu16_Icu_Time);
      /*-- Set gu8_onFallPulseCapture_flag for 1 (to start reading time of the counted value) --*/
      gu8_onFallPulseCapture_flag = 1;      
      /*Reset TCNT2*/
      Timer_SetValue(TIMER_2,0);          
      /*------ change edge -----*/      
      /* 1 - Disable INT2 */
      GICR &= ~(BIT5);
      /* 2 - Set ISC2 to (1) : that will fire INT2 on rising edge */
      MCUCSR |= (BIT6);
      /* 3 - Reset INTF2 flag bit by setting 1*/
      GIFR |= BIT5;
      /* 4 - Enable INT2*/
      GICR |= (BIT5);
      /** Debug Point **/
      //softwareDelayMs(5);
      //PORTB_DATA |= 0<<4 ;
      /*---------------*/
   }     
}