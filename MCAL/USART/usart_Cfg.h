#ifndef __USART_CFG_H__
#define __USART_CFG_H__
/*- INCLUDES ------------------------------------------------------------------------------------------------------*/
#include "../../MCAL/DIO/DIO.h"
/*- DEFINES -------------------------------------------------------------------------------------------------------*/
#define USART_GPIO      (GPIOD)
#define USART_RX_BIT    (BIT0)
#define USART_TX_BIT    (BIT1)
/*- EXTERNS -------------------------------------------------------------------------------------------------------*/
extern const gstr_usart_init_t usart_init_config;

/* BCM related configurations*/
extern const gstr_usart_init_t usart_init_config_transmit;
extern const gstr_usart_init_t usart_init_config_receive;



#endif /* END OF __USART_CFG_H__ */