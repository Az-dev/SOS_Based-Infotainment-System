/*
 * TMU.h
 *
 * Created: 2/24/2020 4:15:10 PM
 *  Author: Az
 */ 


#ifndef TMU_H_
#define TMU_H_
/*- INCLUDES ------------------------------------------------------------------------------------------------------*/
#include "../../std_types.h"
#include "TMU_PREB_Cfg.h"
/*- DEFINES -------------------------------------------------------------------------------------------------------*/
#define PERIODIC 0
#define ONESHOOT 1

/*---- TIMER CHANNEL ----*/
#define  TIMER_0  0
#define  TIMER_1  1
#define  TIMER_2  2

/*- TYPEDEFS ------------------------------------------------------------------------------------------------------*/
//typedef void (* fn)(void);
/*------- Error Enum -------*/
typedef enum EnmTMUError
{
   INIT_OK  = 0,
   INIT_NOK = 1,
   BUFFER_FULL = 3,
   BUFFER_EMPTY = 4,
   INVALID_TASK_PARAM = 5,   
}EnmTMUError_t;
/*------- Task Struct ------*/
typedef struct strTask
{
   uint16_t counter;       /* represents the time interval after which task must be executed */
   //uint8_t ready_flag; 
   uint8_t work_mode;
   uint16_t tick_counts;  /* Internal tick counter for a task */
   void (* fn)(void) ;
}strTask_t;

/*------- configuration Struct -----*/ 
typedef struct strTMU_Cfg
{
   uint8_t timer_channel; 
   uint16_t resolution;
}strTMU_Cfg_t;

/*- FUNCIONS PROTOYPES --------------------------------------------------------------------------------------------*/
/*
*  Description : Initialized the given timer channel with the given resolution.   
*  
*  @param const strTMU_Cfg_t *  strTMU_Init
*
*  @return EnmTMUError_t
*/
extern EnmTMUError_t TMU_Init(const strTMU_Cfg_t * strTMU_Init);

/*
*
*
*
*/
extern EnmTMUError_t TMU_DeInit();

/*
*  Description : Iterate on the tasks to decide on the task to be executed.
*
*  @param void
*
*  @return EnmTMUError_t
*/
extern EnmTMUError_t TMU_Dispatch(void);

/*
*  Description : Adds a Task instance to TMU tasks Buffer.
*
*  @param uint16_t duration
*  @param void (* task_fn)(void)                // A function-pointer to task function
*  uint8_t work_mode                //States whether the task to be add will be PERIODIC or ONESHOOT
*
*  @param EnmTMUError_t
*/
extern EnmTMUError_t TMU_Start_Timer(uint16_t duration , void (* task_fn)(void)  , uint8_t work_mode);

/*
*  Description : Removes a task form TMU queue.
*
*  @param void (* task_fn)(void)
*
*  @return EnmTMUError_t
*/
extern EnmTMUError_t TMU_Stop_Timer(void (* task_fn)(void));

#endif /* TMU_H_ */