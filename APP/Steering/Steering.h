/*
 * Steering.h
 *
 * Created: 2/19/2020 7:40:21 AM
 *  Author: Az
 */ 


#ifndef STEERING_H_
#define STEERING_H_

/*- INCLUDES ----------------------------------------------------------------------------------------------------------------------*/
#include "../../std_types.h"
#include "../../common_macros.h"
#include "../../ECUAL/Motor/Motor.h"
/*- DEFINES -----------------------------------------------------------------------------------------------------------------------*/
/*Command Macros to call the steering api*/
#define		CAR_STOP		   0
#define		CAR_FORWARD		1
#define		CAR_BACKWARD	2
#define		CAR_RIGHT		3
#define		CAR_LEFT		   4

#define INITIAL_SPEED      20

/*- STEERING FUNCTIONS' PROTOTYPES ------------------------------------------------------------------------------------------------*/
/**
 * Description: Initiates the module.
 * 
 * @param void
 *
 * @return ERROR_STATUS 							
 */
ERROR_STATUS Steering_Init(void);

/**
 * Description: This function controls the command and the speed of the car.
 *
 * @param uint8_t Steering_CarCmd 
 * @param uint8_t speed
 *
 * @return ERROR_STATUS							
 */
ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed);

#endif /* STEERING_H_ */