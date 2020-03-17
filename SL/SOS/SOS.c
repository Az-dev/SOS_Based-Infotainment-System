/*
 * SOS.c
 *
 * Created: 2/24/2020 4:14:52 PM
 *  Author: Az
 */ 
/*- INCLUDES -------------------------------------------------------------------------------------------------------*/
#include "../../MCAL/Timer/Timer.h"
#include "../../MCAL/Timer/Timer_Cfg.h"
#include "SOS.h"
/*- GLOBAL VARIABLES -----------------------------------------------------------------------------------------------*/
static strTaskSos_t garrTaskSOSBuffer[SOS_BUFFER_SIZE];  /* internal SOS tasks buffer*/
static sint16_t gindex = -1;  
static volatile uint16_t gu16_preloader = 0;        /* this variable is (volatile,not static) as it must be shown to TIMER's ISR*/
static volatile uint8_t gu8_tickFlag = 0;         /* Initial condition '0' not to execute*/

/* System states related params*/
static uint8_t gu8_SM_State = 0;   /* Stores State machine current state */
/*- FUNCITONS DEFINITIONS ------------------------------------------------------------------------------------------*/
/*---- Start Of Call Backs ----*/
/*
*  Description : a Call back of ISR on Over flow -of timer_0-
*  @param void
*  @return void
*/
static void SOS_T0_OV_CallBack(void)
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
static void SOS_T1_OV_CallBack(void)
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
static void SOS_T2_OV_CallBack(void)
{
   /*---- TMU Over Flow Procedure ----*/   
   /* 1 - Rise execute flag or tick flag*/
   gu8_tickFlag = 1;
   /* 2 - Reload TCNT ---*/
   Timer_SetValue(TIMER_2 , (T2_OV_VAL - gu16_preloader));
}
/*---- End Of Call Backs ----*/

/*
*  Description : Sets the given state machine current state.
*
*  @param uint8_t  state 
*
*  @return void
*/
void Set_SM_State(uint8_t state)
{
   gu8_SM_State = state;
}

/*
*  Description : Initialized the given timer channel with the given resolution.
*
*  @param const strSOS_Cfg_t *  strSOS_Init
*
*  @return EnmSOSError_t
*/
EnmSOSError_t SOS_Init(const strSOS_Cfg_t * strSOS_Init)
{
   /* Define Error state */
   uint8_t au8_errorState;
   /* Check pointer value */ 
   if(NULL != strSOS_Init)
   {
      /* Initializes the given timer */
      switch(strSOS_Init->timer_channel)
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
                  gu16_preloader = (uint16_t)(((double)INVERSE_TICK_TIME_PRESCALE_1024 / MILLI_SECONDS) * strSOS_Init->resolution);
                  Timer_SetValue(TIMER_0 , (T0_OV_VAL - gu16_preloader));
               break;               
            }
            /* Set timer0 call Back */
            Timer_SetCallBack(TIMER_0,TOV_CALL_BACK,SOS_T0_OV_CallBack);           
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
                  gu16_preloader = (uint16_t)(((double)INVERSE_TICK_TIME_PRESCALE_1024 / MILLI_SECONDS) * strSOS_Init->resolution);
                  Timer_SetValue(TIMER_1 , (T1_OV_VAL - gu16_preloader));
               break;
            }
            /* Set timer1 call Back */
            Timer_SetCallBack(TIMER_1,TOV_CALL_BACK,SOS_T1_OV_CallBack);
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
                  gu16_preloader = (uint16_t)(((double)INVERSE_TICK_TIME_PRESCALE_1024 / MILLI_SECONDS) * strSOS_Init->resolution);
                  Timer_SetValue(TIMER_2 , (T2_OV_VAL - gu16_preloader));
               break;
            }
            /* Set timer2 call Back */
            Timer_SetCallBack(TIMER_2,TOV_CALL_BACK,SOS_T2_OV_CallBack);
         break;
      }
      au8_errorState = SOS_INIT_OK;      
   }else{
      au8_errorState = SOS_INIT_NOK;
   }   
   /* Return error state */
   return au8_errorState;
}


/*
*
*
*
*/
EnmSOSError_t SOS_DeInit();

/*
*  Description : Iterate on the tasks to decide on the task to be executed.
*
*  @param void
*
*  @return EnmSOSError_t
*/
EnmSOSError_t SOS_Dispatch(void)
{
    /* Define Error state */
   uint8_t au8_errorState;   
   /* Check if the buffer not empty and excute or tick flag has been fired or not*/
   if((0 <= gindex) && (1 == gu8_tickFlag))
   {
      sint16_t au16_iter = 0;      
      /* 1 - pull down execute flag or tick flag */
      gu8_tickFlag = 0;
      
      /* Search for the Task of the given function within SOS buffer*/
      for(;au16_iter <= gindex; au16_iter++)
      {
         /* Increment task internal tick count */
         garrTaskSOSBuffer[au16_iter].tick_counts++;
         /* Check if task ticks count has reached to the required tick value -which is (task.counter)- to determine whether to execute task's function or not */
         if((garrTaskSOSBuffer[au16_iter].tick_counts) == (garrTaskSOSBuffer[au16_iter].counter))
         { 
            /* 2 - Reset task tick_counts*/ 
            garrTaskSOSBuffer[au16_iter].tick_counts = 0;
            
            if(gu8_SM_State == garrTaskSOSBuffer[au16_iter].task_state)
            {
               /* 2 - Execute Task Function */
               garrTaskSOSBuffer[au16_iter].fn();               
               /* 3 - See Whether the task is periodic or one shoot -after its execution- */
               if(ONESHOOT == garrTaskSOSBuffer[au16_iter].work_mode)
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
                     garrTaskSOSBuffer[au16_iter] = garrTaskSOSBuffer[gindex];
                     /* Decrement gindex */
                     gindex--;
                  }
               }               
            }           
         }                                  
      }           
   }
   else
   {
      /* return error code array is empty */;
      au8_errorState = SOS_BUFFER_EMPTY;      
   }
   return au8_errorState;  
}

/*
*  Description : Adds a Task instance to SOS tasks Buffer.
*
*  @param uint16_t duration
*  @param void (* task_fn)(void)                // A function-pointer to task function
*  @param uint8_t work_mode                //States whether the task to be add will be PERIODIC or ONESHOOT
*  @param uint8_t task_state             //Defines at which state this task will be executed
*
*  @return EnmSOSError_t
*/
EnmSOSError_t SOS_Start_Timer(uint16_t duration , void (* task_fn)(void)  , uint8_t work_mode , uint8_t task_state)
{
   /*--- Start Debug Point (success) ----*/
   /* Create a new task */
   /*
   strTaskSos_t *austr_Task = NULL;
   austr_Task->fn = task_fn;
   austr_Task->counter = duration;
   austr_Task->work_mode = work_mode;
   garrTaskSOSBuffer[0] = *austr_Task;
   return 0;
   */
   /*--- End Debug Point ---*/
   /* Define Error state */
   uint8_t au8_errorState = 0;
   
   if(NULL != task_fn)
   {
      /*---- Enable Interrupt ----*/
      /*---- Add Task to SOS Buffer while buffer is not full ----*/
      if(SOS_BUFFER_SIZE > gindex)
      {
         /* Create a new task */
         strTaskSos_t *austr_Task = NULL;
         austr_Task->fn = task_fn;
         austr_Task->counter = duration;
         austr_Task->work_mode = work_mode;
         austr_Task->task_state =  task_state;
         austr_Task->tick_counts = 0;
                           
         /* Increment gindex : to point to the next empty location to store the new task */
         gindex++;         
         /* Append the task to SOS buffer */
         garrTaskSOSBuffer[gindex] = *austr_Task;         
      }else{
         /* return error code buffer is full*/
         au8_errorState = SOS_BUFFER_FULL;
      }
   }else{
      au8_errorState = SOS_INVALID_TASK_PARAM;
   }  
   return au8_errorState;
}

/*
*  Description : Removes a task form SOS queue.
*
*  @param void (* task_fn)(void)
*
*  @return EnmSOSError_t
*/
EnmSOSError_t SOS_Stop_Timer(void (* task_fn)(void))
{
   /* Define Error state */
   uint8_t au8_errorState;
   
   if(NULL != task_fn)
   {
      /* Check if the buffer not empty */
      if(0 < gindex)
      {
         uint16_t au16_iter = (uint16_t)gindex;
         /* Search for the Task of the given function within SOS buffer*/
         for(;au16_iter >= 0; au16_iter--)
         {
            if(garrTaskSOSBuffer[au16_iter].fn == task_fn)
            {
               /* Then remove the Task : by replacing it with the last task in the buffer */
               garrTaskSOSBuffer[au16_iter] = garrTaskSOSBuffer[gindex];
               /* Increment the size */
               gindex++;
            }
         }
         }else{
         /* return error code array is empty */
         au8_errorState = SOS_BUFFER_EMPTY;
      }      
   }else{
      /* Invalid Task Paramters*/
      au8_errorState = SOS_INVALID_TASK_PARAM;
   }
   return au8_errorState;   
}
