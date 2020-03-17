/*
 * softwareDelay.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef SWDELAY_H_
#define SWDELAY_H_
/*- INCLUDES --------------------------------------------------------------------------------------------------------------*/
#include "../../std_types.h"
/*- FUNCTION PROTOTYPES ---------------------------------------------------------------------------------------------------*/
/**
 * Description: this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param a_delay_in_ms: the milli-seconds
 */
void softwareDelayMs(uint32_t u32_delay_in_ms);

#endif /* SWDELAY_H_ */