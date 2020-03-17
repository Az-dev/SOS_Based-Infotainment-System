/*
 * Motor_Cfg.h
 *
 * Created: 2/18/2020 3:16:00 PM
 *  Author: Az
 */ 


#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_
/*- INCLUDES --------------------------------------------------------------------------------------------------------------*/
#include "../../MCAL/DIO/DIO.h"
/*- DEFINES ---------------------------------------------------------------------------------------------------------------*/
/*---- ENABLE 1 PORT AND PIN ----*/
#define MOTOR_EN_1_GPIO		(GPIOD)
#define MOTOR_EN_1_BIT		(BIT4)
/*---- ENABLE 2 PORT AND PIN ----*/
#define MOTOR_EN_2_GPIO		(GPIOD)
#define MOTOR_EN_2_BIT		(BIT5)
/*---- MOTOR 1A & 1B PORT & PINS ----*/
#define MOTOR_OUT_1A_GPIO	(GPIOD)
#define MOTOR_OUT_1B_GPIO	(GPIOD)
#define MOTOR_OUT_1A_BIT	(BIT2)
#define MOTOR_OUT_1B_BIT	(BIT3)
/*---- MOTOR 2A & 2B PORT & PINS ----*/
#define MOTOR_OUT_2A_GPIO	(GPIOD)
#define MOTOR_OUT_2B_GPIO	(GPIOD)
#define MOTOR_OUT_2A_BIT	(BIT6)
#define MOTOR_OUT_2B_BIT	(BIT7)

#endif /* MOTOR_CFG_H_ */