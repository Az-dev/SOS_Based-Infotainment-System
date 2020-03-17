/*
 * PWM_Cfg.c
 *
 * Created: 2/17/2020 11:31:08 PM
 *  Author: Az
 */ 
/*- INCLUDES -------------------------------------------------------------------------------------------------------------*/
#include "PWM.h"
/* #include "../DIO/DIO.h" */
/*- STRUCTS AND UNIONS ---------------------------------------------------------------------------------------------------*/
/*
strDioCfg_t gstrDioConfig = 
{
   GPIOD,
   (BIT2|BIT3),
   HIGH   
};
*/

strPwmCfg_t gstrPwmConfig = 
{
   PWM_CH1B,   
   T1_PRESCALER_NO   
};

/*- PIN AND PORT CONFIGURATION -------------------------------------------------------------------------------------------*/
/*
DIO_init(&gstrDioConfig);
DIO_Write(GPIOD,(BIT4|BIT5),LOW);
*/