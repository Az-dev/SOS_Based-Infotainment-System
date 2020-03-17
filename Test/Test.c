/*
 * Test.c
 *
 * Created: 2/18/2020 9:30:37 AM
 *  Author: Az
 */ 
/*- INCLUDES -------------------------------------------------------------------------------------------------------------*/
#include "Test.h"
#include "../ECUAL/LCD/char_lcd.h"
#include "../ECUAL/SwDelay/SwDelay.h"
#include "../MCAL/Timer/Timer.h"
#include "../MCAL/Timer/Timer_Cfg.h"
#include "../SL/TMU/TMU.h"
#include "../SL/TMU/TMU_PB_Cfg.h"
#include "../MCAL/SPI/SPI.h"
#include "../MCAL/SPI/SPI_Cfg.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/USART/usart.h"
#include "../MCAL/USART/usart_Cfg.h"
#include "../interrupt.h"
#include "../SL/SOS/SOS.h"
#include "../SL/SOS/SOS_PB_Cfg.h"
/*- FUNCTION DEFINITIONS ------------------------------------------------------------------------------------------------*/

enum states
{
   INIT = 0,
   MID = 1,
   LAST = 2,
};
void taskA(void)
{
   
   PORTA_DIR = 0xff;
   PORTA_DATA ^= 0x10;
   /* Update state machine state */
   Set_SM_State(MID);
      
   
    
}

void taskB(void)
{
   
   PORTA_DIR = 0xff;
   PORTA_DATA ^= 0x20;
   /* Update state machine state */
   //Set_SM_State(LAST);
  
    
   
   
}

void taskC(void)
{
   PORTA_DIR = 0xff;
   PORTA_DATA ^= 0x40;
   /* Update state machine state */
   Set_SM_State(INIT);   
   
   
}

void taskD(void)
{
   PORTA_DIR = 0xff;
   PORTA_DATA ^= 0x80;
   /* Update state machine state */
   //Set_SM_State(INIT);  
}

void SosTest(void)
{   
   /* Initialize state machine state*/   
   Set_SM_State(INIT);
   /*end setup state machine */
   SOS_Init(&gstrSOSConfig);
   SOS_Start_Timer(10,taskA,PERIODIC,INIT);
   SOS_Start_Timer(20,taskB,PERIODIC,MID);
   SOS_Start_Timer(30,taskC,PERIODIC,LAST);
   //SOS_Start_Timer(30,taskD,PERIODIC,LAST);   
   Timer_Start(TIMER_0,0);   
   while(1)
   {
      SOS_Dispatch();
   }
}

void cpu_sleep()
{
   /* Idle mode */
   MCUCR &= ~(1<<5) & ~(1<<6) & ~(1<<4);
   /* Sleep enable */
   MCUCR |= (1<<7);
   __asm__ __volatile__("sleep" "\n\t" ::);
}

/*
*  Description : Tests TMU unit.
*
*  @param void
*
*  @return void
*/
void TmuTest(void)
{
   //PORTA_DIR = 0xff;
   TMU_Init(&gstrTMUConfig);
   TMU_Start_Timer(5,taskA,PERIODIC);
   TMU_Start_Timer(10,taskB,PERIODIC);
   TMU_Start_Timer(20,taskC,PERIODIC);
   TMU_Start_Timer(60,taskD,ONESHOOT);
   Timer_Start(TIMER_0,0);
   while(1)
   {
      //PORTA_DATA |= 0x08;
      TMU_Dispatch();
      //PORTA_DATA &= ~(0x08);
      //cpu_sleep();
   }
}

void myUsartFullDuplexInterruptTest(void)
{
   sei();   
   uint8_t ch = 0;
   uint8_t state = 0;     
   Usart_Init(&usart_init_config);        
   while(1)
   {
      //state = getReceptionState();    (replace it because it is now deprecated) 
      switch(state)
      {
         case USART_BYTE_TRANSMIT_SUCCESS:
            /* Read byte transmitted to udr*/
            UsartReadRx(&ch);             
            /* Write a the same character to be transmitted again*/
            UsartWriteTx(&ch);
         break;
    
      }
      
   }
}

void masterSpi(void)
{
   sei();
   /* Define data byte*/
   uint8_t data = 5;
   /* Define state */
   uint8_t state = 0;
   /* Initialize master */
   SPI_Init(&gstr_MasterCfg);
   /* Configure SS pin */
   PORTB_DIR = 0b10110000;
   /* Initiate data byte write */
   SPI_WriteByte(data);    
   while(1)
   {
      state = SPI_GetTransmissionStatus();
      
      switch(state)
      {
         case SPI_TRANSMISSION_SUCCESS:
            /* 1 - Read the trancieved byte in slave */
            SPI_ReadByte(&data);
            //TCNT2 = data;
            data++;
            softwareDelayMs(100);
            /* 2- write the new data byte*/
            SPI_WriteByte(data);
            softwareDelayMs(100);           
         break;
      }     
   }
}

/*
* Description: Tests SPI module in slave mode
*
*  @param void
*
*  @return void
*/
void slaveSpi(void)
{
     
    sei();      
    /* Initialize master */
    SPI_Init(&gstr_SlaveCfg);
    /* Configure SS pin */
    PORTB_DIR = 0b01000000;       
    while(1);
    
       
}

/*
*  Description : tests Timer module.
*
*  @param void
*
*  @param void
*/
void TimerTest(void)
{
   /*
   Timer_Init(&gstrTimer0TmuConfig); ---> Test passed with different structs of configurations
   Timer_Init(&gstrTimerConfig);    
   Timer_Start(TIMER_0,0);         ---> Test passed with different structs of configurations
   Timer_Start(TIMER_2,0);         ---> Test passed with different structs of configurations
   while(1);
   */
   
   /*Initialize timer 2*/
   //Timer_Init(&gstrTimerConfig);
   /* Start timer 2*/
   //Timer_Start(TIMER_2,0);
   //while (1)
   //{
   //   softwareDelayMs(5000); 
   //   break;   /* Breaking the loop for the purpose of testing Timer_Stop() */
   //}
   /* Stop timer 2*/ 
   //Timer_Stop(TIMER_2);   
}


/*
*  Description : tests DIO module.
*
*  @param void
*
*  @param void
*/
void DioTest(void)
{
   /* Creating strDioCfg_t instance*/
   strDioCfg_t ledCfg = 
   {
      GPIOB,
      (BIT4|BIT5|BIT6|BIT7),
      OUTPUT
   };
   /* Initializing DIO for LEDS ports */
   DIO_init(&ledCfg);
   while (1)
   {
      /* Writing to the port*/
      DIO_Write(GPIOB,(BIT4|BIT5|BIT6|BIT7),HIGH);
      /*Delay*/
      softwareDelayMs(1000);
      /* Writing to the port*/
      DIO_Write(GPIOB,(BIT4|BIT5|BIT6|BIT7),LOW);
      /*Delay*/
      softwareDelayMs(1000);   
   }
      
}

/*
*  Description : tests HwPwm module.
*
*  @param void
*
*  @param void
*/
void HwPwmTest(void)
{
   uint8_t iter = 0;
   /* Initialize pins*/
   strDioCfg_t gstrDioConfig =
   {
      GPIOD,
      (BIT2|BIT3),
      HIGH
   };
   DIO_init(&gstrDioConfig);
   DIO_Write(GPIOD,(BIT4|BIT5),LOW);
   /* Initialize PWM */
   Pwm_Init(&gstrPwmConfig);
   /* Start HWPWM*/
   Pwm_Start(PWM_CH1B,(uint8_t)iter,(uint32_t)PWM_FREQ);   
   while(1){
      for(;iter<100;iter+=10)
      {
         Pwm_Update(PWM_CH1B,(uint8_t)iter,(uint32_t)PWM_FREQ);
         /* Delay*/
         softwareDelayMs(5000);         
      }     
   }      
}

/*
*  Description : test motor control
*
*  @param void
*
*  @param void
*/
void MotorTest(void)
{
   uint8_t iter = 0;
   /* Initialize motors */
   Motor_Init(MOTOR_1);
   Motor_Init(MOTOR_2);
   /* Set motors directions*/
   Motor_Direction(MOTOR_1,MOTOR_FORWARD);
   Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
   /* Start Motor*/
   Motor_Start(MOTOR_1,0);
   Motor_Start(MOTOR_2,0);
   
   while(1)
   {
      /*--- Increasing the speed for a period of time ---*/
      for(;iter<100;iter+=5)
      {
         Motor_SpeedUpdate(MOTOR_1,iter);
         Motor_SpeedUpdate(MOTOR_2,iter);
         softwareDelayMs(1000);         
      }
      /*--- Decreasing the speed for a period of time ---*/
      for(;iter>0;iter-=5)
      {
         Motor_SpeedUpdate(MOTOR_1,iter);
         Motor_SpeedUpdate(MOTOR_2,iter);
         softwareDelayMs(1000);
      }      
      /* Delay */
      softwareDelayMs(3000);      
      /* Set motors directions forward again and move for 3 seconds*/
      Motor_Direction(MOTOR_1,MOTOR_FORWARD);
      Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
      Motor_SpeedUpdate(MOTOR_1,50);
      Motor_SpeedUpdate(MOTOR_2,50);      
      softwareDelayMs(3000);
      /*stop for 2 seconds*/
      Motor_Stop(MOTOR_1); /* this stops both of them*/
      Motor_Stop(MOTOR_2);
      softwareDelayMs(5000);
      /* Set motors directions backward again and move for 3 seconds*/
      Motor_Direction(MOTOR_1,MOTOR_FORWARD);
      Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
      Motor_SpeedUpdate(MOTOR_1,20);
      Motor_SpeedUpdate(MOTOR_2,70);
      softwareDelayMs(5000);
      /*stop for 2 seconds*/
      Motor_Stop(MOTOR_1); /* this stops both of them*/
      Motor_Stop(MOTOR_2);      
   }   
}

/*
*  Description : test ICU control
*
*  @param void
*
*  @param void
*/
void IcuTest(void)
{
    uint32_t u32_test_string;
    uint8_t test_arr[10];      
   /*---- Initialize ICU -----------*/
   Icu_Init(&Icu_config);
   /*---- Initialize and Test LCD ----*/   
   LCD_init();
   LCD_send_string("Test String");
   softwareDelayMs(2000);
   LCD_clear();
   softwareDelayMs(1000);      
   while(1)
   {     
      Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL, &u32_test_string);
      u32_test_string = ((u32_test_string*272)/1000);
      itoa_(u32_test_string, (char*)test_arr, 10);
      LCD_send_string((char*)test_arr);
      softwareDelayMs(1000);
      LCD_clear();
      softwareDelayMs(1000);      
   }
}

void UsTest(void)
{
   Us_Init();
   while(1)
   {
      Us_Trigger();
   }  
}

/*
*  Description : test ICU control
*
*  @param void
*
*  @param void
*/
void IcuWithUsTest(void)
{
   uint32_t u32_string_test;
   uint8_t arr_test[10];
   /*---- Initialize and Test LCD ----*/
   LCD_init();
   LCD_send_string("Test String");
   softwareDelayMs(1000);
   LCD_clear();
   //softwareDelayMs(1000);
   /*---- Initialize UltraSonic ----*/
   Us_Init();
   /*---- Initialize ICU -----------*/
   Icu_Init(&Icu_config);     
   /*---- Trigger Sensor ----------*/
   Us_Trigger();  
   while(1)
   {
      //Us_GetDistance(&au16_distance);        
      Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL, &u32_string_test);
      u32_string_test = ((u32_string_test * 64)/58);
      itoa_(u32_string_test, (char*)arr_test, 10);
      LCD_send_string((char*)arr_test);
      softwareDelayMs(500);
      LCD_clear();
      //softwareDelayMs(1000);
      /*---- Delay before triggering sensor again -----*/
      softwareDelayMs(1000);
      Us_Trigger();      
   }
}




