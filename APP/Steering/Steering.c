/*
 * Steering.c
 *
 * Created: 2/19/2020 7:40:37 AM
 *  Author: Az
 */
/*- INCLUDES ----------------------------------------------------------------------------------------------------------------------*/
#include "Steering.h"

/*- FUNCTIONS DEFINITIONS ---------------------------------------------------------------------------------------------------------*/
/**
 * Description: Initiates the module.
 * 
 * @param void
 *
 * @return ERROR_STATUS 							
 */
ERROR_STATUS Steering_Init(void)
{
   /*---- Initialize motors ----*/   
   Motor_Init(MOTOR_1);
   Motor_Init(MOTOR_2);
   /*---- Set motors directions ----*/
   Motor_Direction(MOTOR_1,MOTOR_FORWARD);
   Motor_Direction(MOTOR_2,MOTOR_FORWARD);
   /*---- Start Motors ----*/   
   Motor_Start(MOTOR_1,INITIAL_SPEED);
   Motor_Start(MOTOR_2,INITIAL_SPEED);
   /*---- Return Success ----*/
   return E_OK;  
}

/**
 * Description: This function controls the command and the speed of the car.
 *
 * @param uint8_t Steering_CarCmd 
 * @param uint8_t speed
 *
 * @return ERROR_STATUS							
 */
ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
{
   /*---- Updating Motors Speed ----*/
   Motor_SpeedUpdate(MOTOR_1,speed);
   Motor_SpeedUpdate(MOTOR_2,speed);
   /*---- switch over different direction states ----*/
   switch(Steering_CarCmd)
   {
      case CAR_STOP:
         Motor_Direction(MOTOR_1,MOTOR_STOP);
         Motor_Direction(MOTOR_2,MOTOR_STOP);         
      break;		   
      case CAR_FORWARD:
         Motor_Direction(MOTOR_1,MOTOR_FORWARD);
         Motor_Direction(MOTOR_2,MOTOR_FORWARD);
      break;			
      case CAR_BACKWARD:
         Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
         Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
      break;			
      case CAR_LEFT:
         Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
         Motor_Direction(MOTOR_2,MOTOR_FORWARD);
      break;				
		case CAR_RIGHT:
         Motor_Direction(MOTOR_1,MOTOR_FORWARD);
         Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
      break;		   
   }
   /*---- return success ----*/
   return E_OK;  
} 
