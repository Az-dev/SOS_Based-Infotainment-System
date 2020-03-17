/*
 * TMU.c
 *
 * Created: 2/24/2020 4:14:52 PM
 *  Author: Az
 */ 
/*- INCLUDES -------------------------------------------------------------------------------------------------------*/
#include "../../MCAL/Timer/Timer.h"
#include "../../MCAL/Timer/Timer_Cfg.h"
#include "TMU.h"
/*- GLOBAL VARIABLES -----------------------------------------------------------------------------------------------*/
static strTask_t garrTaskTMUBuffer[TMU_BUFFER_SIZE];  /* internal TMU tasks buffer*/
static sint16_t gindex = -1;  
static volatile uint16_t gu16_preloader = 0;        /* this variable is (volatile,not static) as it must be shown to TIMER's ISR*/
static volatile uint8_t gu8_tickFlag = 0;         /* Initial condition '0' not to execute*/
/*- FUNCITONS DEFINITIONS ------------------------------------------------------------------------------------------*/
/*---- Start Of Call Backs ----*/
/*
*  Description : a Call back of ISR on Over flow -of timer_0-
*  @param void
*  @return void
*/
static void TMU_T0_OV_CallBack(void)
{
   /*---- TMU Over Flow Procedure ----*/
   /* 1 - Rise execute flag or tick flag */
   gu8_tickFlag = 1;
   /* 2 - Reload TCNT ---*/         
   Timer_SetValue(TIMER_0 , (T0_OV_VAL - gu16_preloader));       
}

/*
*  Description : a Call back of ISR on Over flow -of timer_1-
*  @param void
*  @return void
*/
static void TMU_T1_OV_CallBack(void)
{
   /*---- TMU Over Flow Procedure ----*/
   /* 1 - Rise execute flag or tick flag*/
   gu8_tickFlag = 1;
   /* 2 - Reload TCNT ---*/
   Timer_SetValue(TIMER_1 , (T1_OV_VAL - gu16_preloader));
}

/*
*  Description : a Call back of ISR on Over flow -of timer_2-
*  @param void
*  @return void
*/
static void TMU_T2_OV_CallBack(void)
{
   /*---- TMU Over Flow Procedure ----*/
   /* 1 - Rise execute flag or tick flag*/
   gu8_tickFlag = 1;
   /* 2 - Reload TCNT ---*/
   Timer_SetValue(TIMER_2 , (T2_OV_VAL - gu16_preloader));
}
/*---- End Of Call Backs ----*/

/*
*  Description : Initializes the given timer channel with the given resolution.
*
*  @param  const strTMU_Cfg_t *  strTMU_Init
*
*  @return EnmTMUError_t
*/
EnmTMUError_t TMU_Init(const strTMU_Cfg_t * strTMU_Init)
{
   /* Define Error state */
   uint8_t au8_errorState;
   /* Check pointer value */ 
   if(NULL != strTMU_Init)
   {
      /* Initializes the given timer */
      switch(strTMU_Init->timer_channel)
      {
         case TIMER_0:
            /* Initialize timer0 */
            Timer_Init(&gstrTimer0TmuConfig);
            /* Calculate the value to be set to the timer according to the prescaler set in configuration */
            switch(gstrTimer0TmuConfig.u16_prescal)
            {
               case T0_PRESCALER_64:;
                  /* not used currently*/
               break;
               case T0_PRESCALER_256:;
                  /* not used currently*/
               break;
               case T0_PRESCALER_1024:
                  gu16_preloader = (uint16_t)(((double)INVERSE_TICK_TIME_PRESCALE_1024 / MILLI_SECONDS) * strTMU_Init->resolution);
                  Timer_SetValue(TIMER_0 , (T0_OV_VAL - gu16_preloader));
               break;               
            }
            /* Set timer0 call Back */            
            Timer_SetCallBack(TIMER_0,TOV_CALL_BACK,TMU_T0_OV_CallBack);            
         break;
         case TIMER_1:
            /*Initialize timer1*/
            Timer_Init(&gstrTimer1TmuConfig);
            /* Calculate the value to be set to the timer according to the prescaler set in configuration */
            switch(gstrTimer1TmuConfig.u16_prescal)
            {
               case T1_PRESCALER_64:;
                  /* not used currently*/
               break;
               case T1_PRESCALER_256:;
                  /* not used currently*/
               break;
               case T1_PRESCALER_1024:
                  gu16_preloader = (uint16_t)(((double)INVERSE_TICK_TIME_PRESCALE_1024 / MILLI_SECONDS) * strTMU_Init->resolution);
                  Timer_SetValue(TIMER_1 , (T1_OV_VAL - gu16_preloader));
               break;
            }
            /* Set timer1 call Back */
            Timer_SetCallBack(TIMER_1,TOV_CALL_BACK,TMU_T1_OV_CallBack);
         break;
         case TIMER_2:
            /*Initialize timer2*/
            Timer_Init(&gstrTimer2TmuConfig);
            /* Calculate the value to be set to the timer according to the prescaler set in configuration */
            switch(gstrTimer2TmuConfig.u16_prescal)
            {
               case T2_PRESCALER_64:;
                  /* not used currently*/
               break;
               case T2_PRESCALER_256:;
                  /* not used currently*/
               break;
               case T2_PRESCALER_1024:
                  gu16_preloader = (uint16_t)(((double)INVERSE_TICK_TIME_PRESCALE_1024 / MILLI_SECONDS) * strTMU_Init->resolution);
                  Timer_SetValue(TIMER_2 , (T2_OV_VAL - gu16_preloader));
               break;
            }
            /* Set timer2 call Back */
            Timer_SetCallBack(TIMER_2,TOV_CALL_BACK,TMU_T2_OV_CallBack);
         break;
      }
      au8_errorState = INIT_OK;      
   }else{
      au8_errorState = INIT_NOK;
   }   
   /* Return error state */
   return au8_errorState;
}


/*
*
*
*
*/
EnmTMUError_t TMU_DeInit();

/*
*  Description : Iterate on the tasks to decide on the task to be executed.
*  
*  @param void
*
*  @return EnmTMUError_t
*/
EnmTMUError_t TMU_Dispatch(void)
{
    /* Define Error state */
   uint8_t au8_errorState;   
   /* Check if the buffer not empty */
   if((0 <= gindex) && (1 == gu8_tickFlag))
   {
      sint16_t au16_iter = 0;      
      /* 1 - pull down execute flag or tick flag */
      gu8_tickFlag = 0;
      
      /* Search for the Task of the given function within TMU buffer*/
      for(;au16_iter <= gindex; au16_iter++)
      {
         /* Increment task internal tick count */
         garrTaskTMUBuffer[au16_iter].tick_counts++;
         /* Check if task ticks count has reached to the required tick value -which is (task.counter)- to determine whether to execute task's function or not */
         if((garrTaskTMUBuffer[au16_iter].tick_counts) == (garrTaskTMUBuffer[au16_iter].counter))
         { 
            /* 2 - Reset task tick_counts*/ 
            garrTaskTMUBuffer[au16_iter].tick_counts = 0;          
            /* 3 - Execute Task Function */
            garrTaskTMUBuffer[au16_iter].fn();                      
            /* 4 - See Whether the task is periodic or one shoot -after its execution- */
            if(ONESHOOT == garrTaskTMUBuffer[au16_iter].work_mode)
            {
               /* Case of buffer contains only one element */
               if(0 == gindex)               
               {
                  /* Decrement gindex*/
                  gindex = -1;
               }                
               else
               {
                  /* remove the Task : by replacing it with the last task in the buffer */
                  garrTaskTMUBuffer[au16_iter] = garrTaskTMUBuffer[gindex];
                  /* Decrement gindex */
                  gindex--;                  
               }               
            }
         }                                  
      }           
   }
   else
   {
      /* return error code array is empty */;
      au8_errorState = BUFFER_EMPTY;      
   }
   return au8_errorState;  
}

/*
*  Description : Adds a Task instance to TMU tasks Buffer.
*
*  @param uint16_t duration
*  @param void (* task_fn)(void)
*  uint8_t work_mode                //States whether the task to be add will be PERIODIC or ONESHOOT
*
*  @param EnmTMUError_t
*/
EnmTMUError_t TMU_Start_Timer(uint16_t duration , void (* task_fn)(void) , uint8_t work_mode)
{
   /*--- Start Debug Point (success) ----*/
   /* Create a new task */
   /*
   strTask_t *austr_Task = NULL;
   austr_Task->fn = task_fn;
   austr_Task->counter = duration;
   austr_Task->work_mode = work_mode;
   garrTaskTMUBuffer[0] = *austr_Task;
   return 0;
   */
   /*--- End Debug Point ---*/
   /* Define Error state */
   uint8_t au8_errorState = 0;
   
   if(NULL != task_fn)
   {
      /*---- Enable Interrupt ----*/
      /*---- Add Task to TMU Buffer while buffer is not full ----*/
      if(TMU_BUFFER_SIZE > gindex)
      {
         /* Create a new task */
         strTask_t *austr_Task = NULL;
         austr_Task->fn = task_fn;
         austr_Task->counter = duration;
         austr_Task->work_mode = work_mode;
         austr_Task->tick_counts = 0;
         /* Increment gindex : to point to the next empty location to store the new task */
         gindex++;         
         /* Append the task to TMU buffer */
         garrTaskTMUBuffer[gindex] = *austr_Task;         
      }else{
         /* return error code buffer is full*/
         au8_errorState = BUFFER_FULL;
      }
   }else{
      au8_errorState = INVALID_TASK_PARAM;
   }  
   return au8_errorState;
}

/*
*  Description : Removes a task form TMU queue.
*
*  @param void (* task_fn)(void)
*
*  @return EnmTMUError_t
*/
EnmTMUError_t TMU_Stop_Timer(void (* task_fn)(void))
{
   /* Define Error state */
   uint8_t au8_errorState;
   
   if(NULL != task_fn)
   {
      /* Check if the buffer not empty */
      if(0 < gindex)
      {
         uint16_t au16_iter = (uint16_t)gindex;
         /* Search for the Task of the given function within TMU buffer*/
         for(;au16_iter >= 0; au16_iter--)
         {
            if(garrTaskTMUBuffer[au16_iter].fn == task_fn)
            {
               /* Then remove the Task : by replacing it with the last task in the buffer */
               garrTaskTMUBuffer[au16_iter] = garrTaskTMUBuffer[gindex];
               /* Increment the size */
               gindex++;
            }
         }
         }else{
         /* return error code array is empty */
         au8_errorState = BUFFER_EMPTY;
      }      
   }else{
      /* Invalid Task Paramters*/
      au8_errorState = INVALID_TASK_PARAM;
   }
   return au8_errorState;   
}
