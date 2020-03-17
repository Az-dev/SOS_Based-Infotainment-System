/*
 * LCD_SOS.h
 *
 * Created: 3/15/2020 10:00:59 PM
 *  Author: Az
 */
#ifndef LCD_SOS_H_
#define LCD_SOS_H_

/*- INCLUDES -----------------------------------------------------------------------------------------------------------*/
#include "../../std_types.h"
#include "../../registers.h"
#include "../../MCAL/DIO/DIO.h"
/*- DEFINES -----------------------------------------------------------------------------------------------------------*/
#define LCD_RS_PIN	0x02 	//define MCU pin connected to LCD RS
#define LCD_RS_PORT	GPIOA

#define LCD_RW_PIN	0x04 	//define MCU pin connected to LCD R/W
#define LCD_RW_PORT	GPIOA

#define LCD_EN_PIN	0x08	//define MCU pin connected to LCD E
#define LCD_EN_PORT	GPIOA

#define LCD_D4_PIN	0x10	//define MCU pin connected to LCD D4
#define LCD_D4_PORT	GPIOA

#define LCD_D5_PIN	0x20	//define MCU pin connected to LCD D5
#define LCD_D5_PORT	GPIOA

#define LCD_D6_PIN	0x40	//define MCU pin connected to LCD D6
#define LCD_D6_PORT	GPIOA

#define LCD_D7_PIN	0x80	//define MCU pin connected to LCD D7
#define LCD_D7_PORT	GPIOA

/* LCD Commands definition */
#define Lcd_clear           0x01
#define Return_home         0x02
#define Decrement_cursor    0x04
#define Shift_display_right 0x05
#define Increment_cursor    0x06
#define Shift_display_left  0x07
#define Shift_cursor_left   0x10
#define Shift_cursor_right  0x14
#define Four_bit            0x28
#define Eight_bit           0x38
#define Cursor_off          0x0C
#define Cursor_on           0x0E

/* cursor position to DDRAM mapping */
#define LCD_DDRAM           7	//DB7: set DD RAM address
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54

/* Error Enum */
typedef enum EnmLCDErr
{
   LCD_UNDEFINED_ERROR = 0,
   LCD_INVALID_INPUT_PARAMS = 1,
   LCD_CHAR_SEND_SUCCESS = 2,
   LCD_CHAR_SEND_FAIL = 3,
   LCD_STRING_SEND_COMPLETE = 4,
}EnmLCDErr_t;

/*- FUNCTION DECLARATION ----------------------------------------------------------------------------------------------*/
/*
 * Description : Configures LCD Pins.
 * 
 * @param void
 *
 * @return void
 */
void LCD_Config_pins(void);

/*
 * Description : Enable Pulse Of LCD.
 * 
 * @param void
 *
 * @return void
 */ 
void LCD_En_pulse(void);

/*
 * Description : Sends a nibble for LCD.
 * 
 * @param uint8_t data
 *
 * @return void
 */
void LCD_Send_nibble(uint8_t data); 

/*
 * Description : Sends a command for LCD.
 * 
 * @param uint8_t data
 *
 * @return void
 */
void LCD_Send_command(uint8_t data);	

/*
 * Description : Sends a character for LCD.
 * 
 * @param uint8_t data
 *
 * @return void
 */
void LCD_Send_char(char data);

/*
 * Description : Sends a String for LCD.
 * 
 * @param EnmLCDErr_t char * data
 *
 * @return EnmLCDErr_t
 */		
EnmLCDErr_t LCD_Send_string(char* data);

/*
 * Description : Sends a clear for LCD.
 * 
 * @param void
 *
 * @return void
 */	
void LCD_Clear(void);

#endif /* LCD_SOS_H_ */