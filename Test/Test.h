/*
 * Test.h
 *
 * Created: 2/18/2020 9:31:24 AM
 *  Author: Az
 */ 


#ifndef TEST_H_
#define TEST_H_
/*- INCLUDES -------------------------------------------------------------------------------------------------------------*/
#include "../ECUAL/SwDelay/SwDelay.h"
#include "../MCAL/DIO/DIO.h"
#include "../std_types.h"
#include "../common_macros.h"
#include "../MCAL/PWM/PWM.h"
#include "../ECUAL/Motor/Motor.h"
#include "../ECUAL/SwICU/SwICU.h"
#include "../ECUAL/Us/Us.h"
/*- FUNCTION PROTOTYPES ---------------------------------------------------------------------------------------------------*/

/*
*  Description :represents a test for sos.
*  
*  @param void
*  @param void
*/
void SosTest(void);

/*
*  Description : tests usart as reciever/transmitter in interrupt mode.
*
*  @param void
*
*  @return void
*/
void myUsartFullDuplexInterruptTest(void);

/*
*  Description : tests Timer module.
*
*  @param void
*
*  @param void
*/
void TimerTest(void);

/*
*  Description : tests DIO module.
*
*  @param void
*
*  @param void
*/
void DioTest(void);

/*
*  Description : tests HwPwm module.
*
*  @param void
*
*  @param void
*/
void HwPwmTest(void);

/*
*  Description : test motor control
*
*  @param void
*
*  @param void
*/
void MotorTest(void);

/*
*  Description : test ICU control
*
*  @param void
*
*  @param void
*/
void IcuTest(void);

/*
*  Description : test ICU control
*
*  @param void
*
*  @param void
*/
void UsTest(void);

/*
*  Description : test ICU with ultrasonic control
*
*  @param void
*
*  @param void
*/
void IcuWithUsTest(void);

/*
*  Description : Tests Tmu unit.
*
*  @param void
*
*  @return void
*/
void TmuTest(void);

/*
* Description: Tests SPI module in master mode
*
*  @param void 
*
*  @return void
*/
void masterSpi(void);

/*
* Description: Tests SPI module in slave mode
*
*  @param void
*
*  @return void
*/
void slaveSpi(void);

#endif /* TEST_H_ */