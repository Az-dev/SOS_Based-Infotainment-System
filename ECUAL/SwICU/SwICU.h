/*
 * SwICU.h
 *
 * Created: 2/18/2020 8:57:20 PM
 *  Author: Az
 */ 


#ifndef SWICU_H_
#define SWICU_H_
/*- INCLUDES -----------------------------------------------------------------------------------------------------------------------*/
#include "../../std_types.h"
#include "../../interrupt.h"
#include "../../common_macros.h"
#include "../../MCAL/DIO/DIO.h"
/*- DEFINES ------------------------------------------------------------------------------------------------------------------------*/
#define ICU_CH0			   (0)			/* defines External Interrupt 0 */
#define ICU_CH1			   (1)       	/* defines External Interrupt 1 */
#define ICU_CH2			   (2)			/* defines External Interrupt 2 */

#define ICU_TIMER_CH0	   (0)			/* defines Timer 0 */
#define ICU_TIMER_CH1	   (1)			/* defines Timer 1 */
#define ICU_TIMER_CH2	   (2)			/* defines Timer 2 */

#define ICU_RISE_TO_RISE	(0)
#define ICU_RISE_TO_FALL	(1)
#define ICU_FALE_TO_RISE	(2)

#define FALLING       (0)
#define RISING        (1)
/*- STRUCTS & UNIONS ----------------------------------------------------------------------------------------------------------------*/
typedef struct strIcuCfg{
	uint8_t ICU_Ch_No;		/* To choose the External Interrupt number */
	uint8_t ICU_Ch_Timer;     /* To choose the Timer number */
}strIcuCfg_t;
/*- GLOBAL VARIABLES ----------------------------------------------------------------------------------------------------------------*/
extern strIcuCfg_t Icu_config;
/*- FUNCTION PROTOTYPES ------------------------------------------------------------------------------------------------------------*/

/*
*  Description  : Initializes the ICU by initializing the timer and enabling the global interrupt	
*
*  @param strIcuCfg_t * Icu_Cfg
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Icu_Init(strIcuCfg_t * Icu_Cfg);

/*
*  Description	: calculates the time between 2 edges		
*
*  @param uint8_t Icu_Channel
*  @param uint8_t Icu_EdgeToEdge
*  @param uint32_t * Icu_Time      (I/O param)
*  @return ERROR_STATUS
*/
ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time);

#endif /* SWICU_H_ */