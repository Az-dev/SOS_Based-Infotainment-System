/*
 * Us.h
 *
 * Created: 2/18/2020 11:10:15 PM
 *  Author: Az
 */ 


#ifndef US_H_
#define US_H_

/*- INCLUDES -----------------------------------------------------------------------------------------------------------------------*/
#include "../../std_types.h"
#include "../../common_macros.h"
#include "../../MCAL/DIO/DIO.h"
#include "../SwDelay/SwDelay.h"
#include "../SwICU/SwICU.h"

/*- FUNCTION PROTOTYPES -----------------------------------------------------------------------------------------------------------*/

/*
*  Description  :  This function initiate the UltraSonic by set the value of the Dio_Dirction of
*                  the pin trigger as an output then initiate the ICU to use it to calculate the 
*                  On time of the ECHO signal.
*  @param void
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Us_Init(void);

/*
*  Description : This function send the  pulse, to trigger pin of the UltraSonic to enhance the  ECUO signal
*                    
*  @param void
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Us_Trigger(void);

/*
*  Description : This function get the time of high signal of ECUO pulse, then use it to calculate the distance,
*                then return the value in the Distance parameter.            
*                       
*
*  @param uint16_t *Distance
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Us_GetDistance(uint16_t *Distance);





#endif /* US_H_ */