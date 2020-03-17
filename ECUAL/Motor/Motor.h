/*
 * Motor.h
 *
 * Created: 2/18/2020 2:58:12 PM
 *  Author: Az
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

/*- INCLUDES ---------------------------------------------------------------------------------------------------------------*/
#include "../../common_macros.h"
#include "../../std_types.h"
/*- DEFINES ---------------------------------------------------------------------------------------------------------------*/
#define MOTOR_1			1
#define MOTOR_2 		   2

#define MOTOR_STOP 		0
#define MOTOR_FORWARD 	1
#define MOTOR_BACKWARD 	2

/*- FUNCTION PROTOTYPES --------------------------------------------------------------------------------------------------*/
/*
*  Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
*
*  @param uint8_t Motor_Number
*
*  @return ERROR_STATUS
*/
extern ERROR_STATUS Motor_Init(uint8_t Motor_Number);

/*
*  Description	: Controls the motor direction from getting the motor number and the direction.
*
*  @param uint8_t Motor_Number
*  @param uint8_t Motor_Direction
*
*  @return ERROR_STATUS
*/
extern ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction);

/*
*  Description	: Controls the motor direction from getting the motor number and the direction.
*
*  @param uint8_t Motor_Number
*  @param uint8_t Mot_Speed
*
*  @return ERROR_STATUS
*/
extern ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed);

/*
*  Description	: Controls the motor speed from getting the motor number and the speed.
*
*  @param uint8_t Motor_Number
*  @param uint8_t Speed
*
*  @return ERROR_STATUS
*/
extern ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed);

/*
*  Description	: Stops the motor.
*
*  @param uint8_t Motor_Number
*
*  @return ERROR_STATUS
*/
extern ERROR_STATUS Motor_Stop(uint8_t Motor_Number);

 /*
 *  Description	: Returns status of the motor whether initialized or not
 *
 *  @param uint8_t Motor_Number
 *  @param uint8_t * Mot_status
 *
 *  @return ERROR_STATUS
 */
 extern ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status);

#endif // MOTOR_H_