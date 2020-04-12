/*
 * LCD_SOS.c
 *
 * Created: 3/15/2020 10:01:15 PM
 *  Author: Az
 */
 /*- INCLUDES ---------------------------------------------------------------------------------------------------------*/
 #include "LCD_SOS.h"
 /*- FUNCITONS DECLARATIONS --------------------------------------------------------------------------------------------*/
 /*
 * Description : Configures LCD Pins.
 * 
 * @param void
 *
 * @return void
 */
 void LCD_Config_pins(void)
 {
   
   strDioCfg_t LCD_Cfg_RS=
   {
      LCD_RS_PORT,
      LCD_RS_PIN,
      OUTPUT     
   };
   DIO_init(&LCD_Cfg_RS);  

   strDioCfg_t LCD_Cfg_RW =
   {
      LCD_RW_PORT,
      LCD_RW_PIN,
      OUTPUT
   };
   DIO_init(&LCD_Cfg_RW);

   strDioCfg_t LCD_Cfg_EN = 
   {
      LCD_EN_PORT,
      LCD_EN_PIN,
      OUTPUT
   };
   DIO_init(&LCD_Cfg_EN);

   strDioCfg_t LCD_Cfg_D4 = 
   {
      LCD_D4_PORT,
      LCD_D4_PIN,
      OUTPUT
   };
   DIO_init(&LCD_Cfg_D4);

   strDioCfg_t LCD_Cfg_D5 = 
   {
      LCD_D5_PORT,
      LCD_D5_PIN,
      OUTPUT
   };
   DIO_init(&LCD_Cfg_D5);

   strDioCfg_t LCD_Cfg_D6 = 
   {
      LCD_D6_PORT,
      LCD_D6_PIN,
      OUTPUT
   };
   DIO_init(&LCD_Cfg_D6);

   strDioCfg_t LCD_Cfg_D7 = 
   {
      LCD_D7_PORT,
      LCD_D7_PIN,
      OUTPUT
   };
   DIO_init(&LCD_Cfg_D7);    
 }

 /*
 * Description : Enable Pulse Of LCD.
 * 
 * @param void
 *
 * @return void
 */
 void LCD_En_pulse(void){
    DIO_Write(LCD_EN_PORT, LCD_EN_PIN, HIGH);
    DIO_Write(LCD_EN_PORT, LCD_EN_PIN, LOW);    
 }

 /*
 * Description : Sends a nibble for LCD.
 * 
 * @param uint8_t data
 *
 * @return void
 */
 void LCD_Send_nibble(uint8_t data){
    uint8_t mask = 1;
    data >>= 4;
    if(data&mask)
    DIO_Write(LCD_D4_PORT, LCD_D4_PIN, HIGH);
    else
    DIO_Write(LCD_D4_PORT, LCD_D4_PIN, LOW);

    mask *= 2;
    if(data&mask)
    DIO_Write(LCD_D5_PORT, LCD_D5_PIN, HIGH);
    else
    DIO_Write(LCD_D5_PORT, LCD_D5_PIN, LOW);

    mask *= 2;
    if(data&mask)
    DIO_Write(LCD_D6_PORT, LCD_D6_PIN, HIGH);
    else
    DIO_Write(LCD_D6_PORT, LCD_D6_PIN, LOW);

    mask *= 2;
    if(data&mask)
    DIO_Write(LCD_D7_PORT, LCD_D7_PIN, HIGH);
    else
    DIO_Write(LCD_D7_PORT, LCD_D7_PIN, LOW);
 }

 /*
 * Description : Sends a character for LCD.
 * 
 * @param uint8_t data
 *
 * @return void
 */
 void LCD_Send_char(char data)
 {
    DIO_Write(LCD_RS_PORT, LCD_RS_PIN, HIGH);

    LCD_Send_nibble(data); // Higher nibble first
    LCD_En_pulse();

    LCD_Send_nibble(data<<4);
    LCD_En_pulse();    
 }

 /*
 * Description : Sends a command for LCD.
 * 
 * @param uint8_t data
 *
 * @return void
 */
 void LCD_Send_command(uint8_t data)
 {
   DIO_Write(LCD_RS_PORT, LCD_RS_PIN, LOW);

   LCD_Send_nibble(data); // Higher nibble first
   LCD_En_pulse();

   LCD_Send_nibble(data<<4);
   LCD_En_pulse();
 } 

/*
 * Description : Sends a String for LCD.
 * 
 * @param EnmLCDErr_t char * data
 *
 * @return EnmLCDErr_t
 */
 EnmLCDErr_t LCD_Send_string(char * data)	
 {
    uint8_t au8_errorState = 0;
    /* Define char counter */
    static uint8_t su8_strCounter = 0;
    if(NULL != data)
    {
       /* Check last character is reached */
       if(data[su8_strCounter])   /*if not reached '\0' which is the end of the string */
       {
         LCD_Send_char(data[su8_strCounter]);
         /* Increment counter */
         su8_strCounter++;
         /*Report success */
         au8_errorState = LCD_CHAR_SEND_SUCCESS;     
       }
       else
       {
         /* Reset char counter */
         su8_strCounter = 0;
         /* Report finish */
         au8_errorState = LCD_STRING_SEND_COMPLETE;         
       }
      
    }
    else
    {
      au8_errorState = LCD_INVALID_INPUT_PARAMS;

    }
    return au8_errorState;
 }

 /*
 * Description : Sends a clear for LCD.
 * 
 * @param void
 *
 * @return void
 */
 void LCD_Clear(void)
 {
    LCD_Send_command(Lcd_clear);
 }





 
 
  



