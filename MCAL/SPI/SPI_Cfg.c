/*
 * SPI_Cfg.c
 *
 * Created: 3/2/2020 2:47:40 PM
 *  Author: Az
 */ 
/*- INCLUDES ------------------------------------------------------------------------------------------------------*/
#include "SPI.h"
/*- STRUCTS ------------------------------------------------------------------------------------------------------*/


/*------------------------------------------  BCM SPI CONFIG ------------------------------------*/
/*--- SPI configuration struct (Master) BCM Transmit ---*/
str_SPI_Cfg_t gstr_MasterCfg = 
{
   SPI_DIS,
   SPIE_EN,
   DORD_HIGH,
   MSTR_SEL,
   CLK_POL_PHA_MODE_0,
   Fosc_128,
   SPI_2X_DIS, 
   0b10110000  
};

/*--- SPI configuration struct (Slave) BCM Receive ---*/
str_SPI_Cfg_t gstr_SlaveCfg =
{
   SPI_DIS,
   SPIE_EN,
   DORD_HIGH,
   SLV_SEL,
   CLK_POL_PHA_MODE_0,
   Fosc_128,
   SPI_2X_DIS,
   0b01000000   
};
