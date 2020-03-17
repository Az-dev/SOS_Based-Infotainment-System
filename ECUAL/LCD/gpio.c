/*
 * gpio.c
 *
 * Created: 12/3/2019 2:34:35 PM
 *  Author: Amr
 */ 

#include "../../std_types.h"
#include "gpio.h"
#include "../../registers.h"
/**
 * Description: set port direction (which is DDR register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param direction: set the port direction and takes the following values
 * 				- 0x00 -> Input
 * 				- 0xff -> Output
 */
void gpioPortDirection(uint8 port, uint8 direction)
{
	switch (port)
	{
		case GPIOA:
		PORTA_DIR = direction;
		break;
		case GPIOB:
		PORTB_DIR = direction;
		break;
		case GPIOC:
		PORTC_DIR = direction;
		break;
		case GPIOD:
		PORTD_DIR = direction;
		break;
		default:
		break;
	}
}

/**
 * Description: set the port value (which is PORT register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value: set the port value and takes the following values
 * 				- 0x00 -> Low
 * 				- 0xff -> High
 */
void gpioPortWrite(uint8 port, uint8 value)
{
	switch (port)
	{
		case GPIOA:
		PORTA_DATA = value;
		break;
		case GPIOB:
		PORTB_DATA = value;
		break;
		case GPIOC:
		PORTC_DATA = value;
		break;
		case GPIOD:
		PORTD_DATA = value;
		break;
		default:
		break;
	}
}

/**
 * Description: toggle the port value (which is PORT register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 */
void gpioPortToggle(uint8 port)
{
	switch (port)
	{
		case GPIOA:
		PORTA_DATA = ~gpioPortRead(port);
		break;
		case GPIOB:
		PORTB_DATA = ~gpioPortRead(port);
		break;
		case GPIOC:
		PORTC_DATA = ~gpioPortRead(port);
		break;
		case GPIOD:
		PORTD_DATA = ~gpioPortRead(port);
		break;
		default:
		break;
	}
}

/**
 * Description: read the current port value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioPortRead(uint8 port)
{
	uint8 ret = 0;
	switch (port)
	{
		case GPIOA:
		ret = PORTA_PIN;
		break;
		case GPIOB:
		ret = PORTB_PIN;
		break;
		case GPIOC:
		ret = PORTC_PIN;
		break;
		case GPIOD:
		ret = PORTD_PIN;
		break;
		default:
		break;
	}
	return ret;
}

/*===========================PIN Control===============================*/
/**
 * Description: set selected pins (more than one pin [ORed]) direction
 *
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pins the user need to set its direction and takes
 * 				any member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 *
 * @param direction: set the pins direction and takes the following values
 * 				- 0x00 -> Input
 * 				- 0xff -> Output
 */
void gpioPinDirection(uint8 port, uint8 pins, uint8 direction)
{
	if (direction == 0x01)
	{
		direction = 0b11111111;
	}
	else if (direction == 0x00)
	{
		direction = 0b00000000;
	}
	
	switch (port)
	{
		case GPIOA:
		PORTA_DIR = (PORTA_DIR & (~pins)) | (pins & direction);
		break;
		case GPIOB:
		PORTB_DIR = (PORTB_DIR & (~pins)) | (pins & direction);
		break;
		case GPIOC:
		PORTC_DIR = (PORTC_DIR & (~pins)) | (pins & direction);
		break;
		case GPIOD:
		PORTD_DIR = (PORTD_DIR & (~pins)) | (pins & direction);
		break;
		default:
		break;
	}
}

/**
 * Description: set selected pins (more than one pin [ORed]) values
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pins the user need to write its values and takes
 * 				any member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @param value
 */
void gpioPinWrite(uint8 port, uint8 pins, uint8 value)
{
	if (value == 0x01)
	{
		value = 0b11111111;
	}
	else if (value == 0x00)
	{
		value = 0b00000000;
	}
	
	switch (port)
	{
		case GPIOA:
		PORTA_DATA = (PORTA_DATA & (~pins)) | (pins & value);
		break;
		case GPIOB:
		PORTB_DATA = (PORTB_DATA & (~pins)) | (pins & value);
		break;
		case GPIOC:
		PORTC_DATA = (PORTC_DATA & (~pins)) | (pins & value);
		break;
		case GPIOD:
		PORTD_DATA = (PORTD_DATA & (~pins)) | (pins & value);
		break;
		default:
		break;
	}
}

/**
 * Description: toggle selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				only one member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 */
void gpioPinToggle(uint8 port, uint8 pins)
{
	switch (port)
	{
		case GPIOA:
		PORTA_DATA =  (PORTA_PIN ^ pins);
		break;
		case GPIOB:
		PORTB_DATA =  (PORTB_PIN ^ pins);
		break;
		case GPIOC:
		PORTC_DATA =  (PORTC_PIN ^ pins);
		break;
		case GPIOD:
		PORTD_DATA =  (PORTD_PIN ^ pins);
		break;
		default:
		break;
	}
}

/**
 * Description: read selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param pin: the selected pin the user need to read it's value and takes
 * 				only one member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @return
 */
uint8 gpioPinRead(uint8 port, uint8 pin)
{
	uint8 ret = 0;
	switch (port)
	{
		case GPIOA:
		ret = (PORTA_PIN & pin);
		break;
		case GPIOB:
		ret = (PORTB_PIN & pin);
		break;
		case GPIOC:
		ret = (PORTC_PIN & pin);
		break;
		case GPIOD:
		ret = (PORTD_PIN & pin);
		break;
		default:
		break;
	}
	if (ret != 0)
	{
		ret = 0x01;
	}
	else
	{
		ret = 0x00;
	}
	return ret;
}

/*===========================Upper Nibble Control===============================*/
/**
 * Description: set the upper nibble direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param direction
 */
void gpioUpperNibbleDirection(uint8 port, uint8 direction)
{
	if (direction == 0x01)
	{
		direction = 0b11110000;
	}
	else if (direction == 0x00)
	{
		direction = 0b00000000;
	}
	
	switch (port)
	{
		case GPIOA:
		PORTA_DIR =  (PORTA_DIR & 0x0f) | (direction);
		break;
		case GPIOB:
		PORTB_DIR =  (PORTB_DIR & 0x0f) | (direction);
		break;
		case GPIOC:
		PORTC_DIR =  (PORTC_DIR & 0x0f) | (direction);
		break;
		case GPIOD:
		PORTD_DIR =  (PORTD_DIR & 0x0f) | (direction);
		break;
		default:
		break;
	}
}

/**
 * Description: write the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value
 */
void gpioUpperNibbleWrite(uint8 port, uint8 value)
{
	if (value == 0x01)
	{
		value = 0b11110000;
	}
	else if (value == 0x00)
	{
		value = 0b00000000;
	}
	
	switch (port)
	{
		case GPIOA:
		PORTA_DATA =  (PORTA_DATA & 0x0f) | (value);
		break;
		case GPIOB:
		PORTB_DATA =  (PORTB_DATA & 0x0f) | (value);
		break;
		case GPIOC:
		PORTC_DATA =  (PORTC_DATA & 0x0f) | (value);
		break;
		case GPIOD:
		PORTD_DATA =  (PORTD_DATA & 0x0f) | (value);
		break;
		default:
		break;
	}
}

/**
 * Description: toggle the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 */
void gpioUpperNibbleToggle(uint8 port)
{
	switch (port)
	{
		case GPIOA:
		PORTA_DATA =  (PORTA_PIN ^ 0xf0);
		break;
		case GPIOB:
		PORTB_DATA =  (PORTB_PIN ^ 0xf0);
		break;
		case GPIOC:
		PORTC_DATA =  (PORTC_PIN ^ 0xf0);
		break;
		case GPIOD:
		PORTD_DATA =  (PORTD_PIN ^ 0xf0);
		break;
		default:
		break;
	}
}

/**
 * Description: read the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioUpperNibbleRead(uint8 port)
{
	uint8 ret = 0;
	switch (port)
	{
		case GPIOA:
		ret =  (PORTA_PIN & 0xf0);
		break;
		case GPIOB:
		ret =  (PORTB_PIN & 0xf0);
		break;
		case GPIOC:
		ret =  (PORTC_PIN & 0xf0);
		break;
		case GPIOD:
		ret =  (PORTD_PIN & 0xf0);
		break;
		default:
		break;
	}
	return ret;
}

/*===========================Lower Nibble Control===============================*/
/**
 * Description: set the lower nibble direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param direction
 */
void gpioLowerNibbleDirection(uint8 port, uint8 direction)
{
	if (direction == 0x01)
	{
		direction = 0b00001111;
	}
	else if (direction == 0x00)
	{
		direction = 0b00000000;
	}
	
	switch (port)
	{
		case GPIOA:
		PORTA_DIR =  (PORTA_DIR & 0xf0) | (direction);
		break;
		case GPIOB:
		PORTB_DIR =  (PORTB_DIR & 0xf0) | (direction);
		break;
		case GPIOC:
		PORTC_DIR =  (PORTC_DIR & 0xf0) | (direction);
		break;
		case GPIOD:
		PORTD_DIR =  (PORTD_DIR & 0xf0) | (direction);
		break;
		default:
		break;
	}
}

/**
 * Description: write the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value
 */
void gpioLowerNibbleWrite(uint8 port, uint8 value)
{
	if (value == 0x01)
	{
		value = 0b00001111;
	}
	else if (value == 0x00)
	{
		value = 0b00000000;
	}
	
	switch (port)
	{
		case GPIOA:
		PORTA_DATA =  (PORTA_DATA & 0xf0) | (value);
		break;
		case GPIOB:
		PORTB_DATA =  (PORTB_DATA & 0xf0) | (value);
		break;
		case GPIOC:
		PORTC_DATA =  (PORTC_DATA & 0xf0) | (value);
		break;
		case GPIOD:
		PORTD_DATA =  (PORTD_DATA & 0xf0) | (value);
		break;
		default:
		break;
	}
}

/**
 * Description: toggle the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 */
void gpioLowerNibbleToggle(uint8 port)
{
	switch (port)
	{
		case GPIOA:
		PORTA_DATA =  (PORTA_PIN ^ 0x0f);
		break;
		case GPIOB:
		PORTB_DATA =  (PORTB_PIN ^ 0x0f);
		break;
		case GPIOC:
		PORTC_DATA =  (PORTC_PIN ^ 0x0f);
		break;
		case GPIOD:
		PORTD_DATA =  (PORTD_PIN ^ 0x0f);
		break;
		default:
		break;
	}
}

/**
 * Description: read the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioLowerNibbleRead(uint8 port)
{
	uint8 ret = 0;
	switch (port)
	{
		case GPIOA:
		ret =  (PORTA_PIN & 0x0f);
		break;
		case GPIOB:
		ret =  (PORTB_PIN & 0x0f);
		break;
		case GPIOC:
		ret =  (PORTC_PIN & 0x0f);
		break;
		case GPIOD:
		ret =  (PORTD_PIN & 0x0f);
		break;
		default:
		break;
	}
	return ret;
}