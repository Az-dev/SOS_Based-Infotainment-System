/*
 * CarSM.h
 *
 * Created: 2/19/2020 8:16:45 AM
 *  Author: Az
 */ 


#ifndef CARSM_H_
#define CARSM_H_
/*- INCLUDES -----------------------------------------------------------------------------------------------------------------------*/
#include "../../common_macros.h"
#include "../../std_types.h"
#include "../../ECUAL/SwDelay/SwDelay.h"

/*- FUNCTIONS DECLARATION ---------------------------------------------------------------------------------------------------------*/

/*
*  Description : Initiate the car state machine with state"forward at speed 80%",
*
*  @param void
*
*  @param ERROR_STATUS
*/
ERROR_STATUS Car_SM_Init(void);

/*
 * Description : changes car state according to the ultrasonic input.
 * 
 * @param void
 *
 * ERROR_STATUS
*/
ERROR_STATUS Car_SM_Update(void);

#endif /* CARSM_H_ */