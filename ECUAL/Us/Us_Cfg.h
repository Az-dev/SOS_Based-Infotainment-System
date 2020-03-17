/*
 * Us_Cfg.h
 *
 * Created: 2/18/2020 11:10:33 PM
 *  Author: Az
 */ 


#ifndef US_CFG_H_
#define US_CFG_H_
/*- INCLUDES ------------------------------------------------------------------------------------------------------------------------*/ 
#include "../../registers.h"
/*- DEFINES -------------------------------------------------------------------------------------------------------------------------*/
//#define ULTRA_EN_GPIO      (GPIOB)
//#define ULTRA_ENABLE_BIT   (BIT3)
#define ULTRA_EN_GPIO      (GPIOC)
#define ULTRA_ENABLE_BIT   (BIT4)   
#define ULTRA_OUT_GPIO     (GPIOB)
#define ULTRA_OUT_BIT      (BIT2)

#endif /* US_CFG_H_ */