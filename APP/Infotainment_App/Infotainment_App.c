/*
 * SOS_App.c
 *
 * Created: 3/15/2020 9:43:46 PM
 *  Author: Az
 */ 
 /*- INCLUDES ---------------------------------------------------------------------------------------------------------------------*/
 #include "Infotainment_App.h"
 #include "../../SL/SOS/SOS.h"
 #include "../../SL/SOS/SOS_PB_Cfg.h"
 #include "../../MCAL/Timer/Timer.h"
 #include "../../MCAL/Timer/Timer_Cfg.h"
 #include "../../ECUAL/LCD_SOS/LCD_SOS.h"
 #include "../../ECUAL/PUSHBTN_SOS/PUSHBTN_SOS.h"
 /*- GLOBALS ----------------------------------------------------------------------------------------------------------------------*/
 /* Questions and Answers */
  static uint8_t ga_question1[QUESTION_STRING_SIZE] = "this is 1";
  static uint8_t ga_question2[QUESTION_STRING_SIZE] = "this is 2";
  static uint8_t ga_question3[QUESTION_STRING_SIZE] = "this is 3";
  static uint8_t ga_question4[QUESTION_STRING_SIZE] = "this is 4";
  static uint8_t ga_question5[QUESTION_STRING_SIZE] = "this is 5";
  static uint8_t ga_correctAnswers[QUESTION_STRING_SIZE] = 
  {
   YES,
   YES,
   YES,
   NO,
   NO
  };

  /* Global PushBtns States */
  static uint8_t gu8_btn0State = RELEASED;   /* Note that : btn0 represents Yes */
  static uint8_t gu8_btn1State = RELEASED;   /* Note that : btn1 represents NO */

  /* True or false */
  static uint8_t True = 0;

  static uint8_t gu8_outCounter = 0;
 
 /*- FUNCTION DEFINITIONS ---------------------------------------------------------------------------------------------------------*/
  /*----------------- Tasks Definitions ----------------------*/
  /* 
  *   Description : Check periodically state of push BTN0/BTN1 
  *
  *   @param void 
  *
  *   @return void
  */
  static void GetPushBtnState(void)
  {
      static uint8_t btn0_press_count = 0;
      static uint8_t btn1_press_count = 0;
      /* Get Btns States */
      PUSHBTN_Get_BTN0_Status(&gu8_btn0State);      
      /* Check if which btn0 is pressed */
      switch(gu8_btn0State)
      {
         case PRESSED:
            btn0_press_count++;
            if(2 == btn0_press_count) /* So it is still pressed*/
            {
               /* Force/Ensure pressed state */
               gu8_btn0State = PRESSED;
               /* Reset the counter */
               btn0_press_count = 0;
            }            
         break;
         case RELEASED:
             /* Force/Ensure pressed state */
             gu8_btn0State = RELEASED;
             /* Reset the counter */
             btn0_press_count = 0;            
         break;
      }
      /* Check if which btn1 is pressed */
      PUSHBTN_Get_BTN1_Status(&gu8_btn1State);
      /* Check if which btn1 is pressed */
      switch(gu8_btn1State)
      {
         case PRESSED:
            btn1_press_count++;
            if(2 == btn1_press_count) /* So it is still pressed*/
            {
               /* Force/Ensure pressed state */
               gu8_btn1State = PRESSED;
               /* Reset the counter */
               btn1_press_count = 0;
            }
         break;
         case RELEASED:
            /* Force/Ensure pressed state */
            gu8_btn1State = RELEASED;
            /* Reset the counter */
            btn1_press_count = 0;
         break;
      }      
  }
  
  /* 
  *   Description : Sets System Configuration 
  *
  *   @param void 
  *
  *   @return void
  */  
  static void SysConfigTask(void)
  {   
      /* LCD config */
      LCD_Config_pins();
      /* Keypad or buttons config*/
      PUSHBTN_Config();
      /* Config Buzzer */
      PORTB_DIR = 0x08;
      /* Config LEDS */
      PORTB_DIR= 0xf0;
      /* Update state of state machine */
      Set_SM_State(INIT_DISPLAY);
  }

  /* 
  *   Description : Initializes Display 
  *
  *   @param void 
  *
  *   @return void
  */
  static void InitDisplay(void)
  {
      static uint8_t Display_init_state = DISPLAY_EN;
      switch (Display_init_state)
      {
         case DISPLAY_EN:            
            LCD_En_pulse();            
            Display_init_state = SEND_COMMAND_1;
         break;
         case SEND_COMMAND_1:            
            LCD_Send_command(0x33);
            Display_init_state = SEND_COMMAND_2;
         break;
         case SEND_COMMAND_2:
            LCD_Send_command(0x32);
            Display_init_state = SEND_COMMAND_3;
         break;
         case SEND_COMMAND_3:
            LCD_Send_command(Four_bit);
            Display_init_state = SEND_COMMAND_4;
         break;
         case SEND_COMMAND_4:
            LCD_Send_command(Cursor_on);
            Display_init_state = SEND_COMMAND_5;
         break;
         case SEND_COMMAND_5:
            LCD_Send_command(Lcd_clear);
            Display_init_state = SEND_COMMAND_6;
         break;
         case SEND_COMMAND_6:
            LCD_Send_command(Increment_cursor);
            Display_init_state = SEND_COMMAND_7;
         break;
         case SEND_COMMAND_7:
            LCD_Send_command(Cursor_off);
            /* Update system state */
            Set_SM_State(SEND_QUESTION);
         break;

      }
  }

  /* 
  *   Description : Displays/Sends Question to user. 
  *
  *   @param void 
  *
  *   @return void
  */
  static void SendQuestion(void)
  {
      static uint8_t su8_questionNumState = Q1;
      /* Question Character Send State */
      uint8_t au8_charSendState = 0;
      switch(su8_questionNumState)
      {
         case Q1:                                    
            /* Send the first Question procedure */
            au8_charSendState = LCD_Send_string((char *)ga_question1);
            /* Check String Display Completion */
            if(LCD_CHAR_SEND_SUCCESS == au8_charSendState)
            {
               /* We are still sending the current question */               
               su8_questionNumState = Q1;
            }
            else if(LCD_STRING_SEND_COMPLETE == au8_charSendState)
            {
               /* Clear the lcd */
               //LCD_Clear();
               /* Move to the next question */
               su8_questionNumState = Q2;
               //su8_questionNumState = 250;
               Set_SM_State(WAIT_ANSWER);                        
            }
                                    
         break;
         case Q2:            
            /* Send the first Question */
            au8_charSendState = LCD_Send_string((char *)ga_question2);
            /* Check String Display Completion */
            if(LCD_CHAR_SEND_SUCCESS == au8_charSendState)
            {
               /* We are still sending the current question */
               su8_questionNumState = Q2;
            }
            else if(LCD_STRING_SEND_COMPLETE == au8_charSendState)
            {
               /* Clear Lcd*/
               //LCD_Clear();
               /* Move to the next question */
               su8_questionNumState = Q3;
               //su8_questionNumState = 250;
               Set_SM_State(WAIT_ANSWER);
            }            
         break;
         case Q3:            
            /* Send the first Question */
            au8_charSendState = LCD_Send_string((char *)ga_question3);
            /* Check String Display Completion */
            if(LCD_CHAR_SEND_SUCCESS == au8_charSendState)
            {
               /* We are still sending the current question */
               su8_questionNumState = Q3;
            }
            else if(LCD_STRING_SEND_COMPLETE == au8_charSendState)
            {
               /*Clear LCD*/
               //LCD_Clear();
               /* Move to the next question */
               su8_questionNumState = Q4;
               //su8_questionNumState = 250;
               Set_SM_State(WAIT_ANSWER);
            }            
         break;
         case Q4:            
            /* Send the first Question */
            au8_charSendState = LCD_Send_string((char *)ga_question4);
            /* Check String Display Completion */
            if(LCD_CHAR_SEND_SUCCESS == au8_charSendState)
            {
               /* We are still sending the current question */
               su8_questionNumState = Q4;
            }
            else if(LCD_STRING_SEND_COMPLETE == au8_charSendState)
            {
               /* Clear LCD*/
               //LCD_Clear();
               /* Move to the next question */
               su8_questionNumState = Q5;
               //su8_questionNumState = 250;
               Set_SM_State(WAIT_ANSWER);
            }
         break;
         case Q5:            
            /* Send the first Question */
            au8_charSendState = LCD_Send_string((char *)ga_question5);
            /* Check String Display Completion */
            if(LCD_CHAR_SEND_SUCCESS == au8_charSendState)
            {
               /* We are still sending the current question */
               su8_questionNumState = Q5;
            }
            else if(LCD_STRING_SEND_COMPLETE == au8_charSendState)
            {
               /* Clear LCD */
               //LCD_Clear();
               /* Move to the next question */
               su8_questionNumState = Q1;
               //su8_questionNumState = 250;
               Set_SM_State(WAIT_ANSWER);
            }            
         break;    
      }
      /* Update System state : Wait for answer state */
      //Set_SM_State(SEND_QUESTION);
      //Set_SM_State(WAIT_ANSWER);      
  }

  /* 
  *   Description : Waits for user action on buttons to answer questions. 
  *
  *   @param void 
  *
  *   @return void
  */
  static void WaitAns(void)
  {
      static uint8_t su8_ansCounter = 0;
      /* Reset Answer counter */
      if (QUESTION_STRING_SIZE == su8_ansCounter) su8_ansCounter = 0;           
      /* Check BTNS state */     
      if(PRESSED == gu8_btn0State)  /* Represent Yes */
      {
         /* Check if answer is correct or not */
         if(YES == ga_correctAnswers[su8_ansCounter])
         {
            /* Output correct : Toggle Leds */            
            True = 1;       
         }
         else
         {
            /* Output incorrect : fire buzzer */            
            True = 0;

         }
//          /* Clear the current question */
//          LCD_Clear();
//          /* Move to the next Question */
//          Set_SM_State(SEND_QUESTION);
            Set_SM_State(REPORT_RESULT);
      }

      /* Case of Btn1 is pressed */
      if(PRESSED == gu8_btn1State) 
      {
         /* Check if answer is correct or not */
         if(NO == ga_correctAnswers[su8_ansCounter])
         {
            /* Output correct : Toggle Leds */
            True = 1;
            
         }
         else
         {
            /* Output incorrect : fire buzzer */
            True = 0;

         }        
//          /* Clear the current question */
//          LCD_Clear();
//          /* Move to the next Question */
//          Set_SM_State(SEND_QUESTION);
            Set_SM_State(REPORT_RESULT);
      }
  }

  /* 
  *   Description : Toggles LEDS (case of correct answer) or Toggle Buzzer (case of incorrect answer)
  *
  *   @param void 
  *
  *   @return void
  */
  static void ReportResult(void)
  {
      if(True)
      {
         PORTB_DATA ^= 0xf0;
      }
      else
      {
         PORTB_DATA ^= 0x08;
      }
      /* Clear the current question */
      LCD_Clear();
      /* Move to the next Question */
      Set_SM_State(FINISHED_REPORT_RESULT);
  }

  void FinishedReportResult(void)
  {
      if(True)
      {
         PORTB_DATA ^= 0xf0;
      }
      else
      {
         PORTB_DATA ^= 0x08;
      }
      gu8_outCounter++;

      if(gu8_outCounter == 5)
      {
         /* Clear the current question */
         LCD_Clear();
         /* Move to the next Question */
         Set_SM_State(SEND_QUESTION);
         /* Reset counter*/
         gu8_outCounter = 0;
      }      
  }



/* 
  *   Description : Add Tasks to System and Fire Dispatcher.
  *
  *   @param void 
  *
  *   @return void
  */  
void SOS_Run(void)
{
   /* Initialize state machine state*/
   Set_SM_State(CONFIG);
   /* Initialize SOS with suitable configuration */
   SOS_Init(&gstrSOSConfig);
   /* Add Tasks */
   SOS_Start_Timer(2,SysConfigTask,PERIODIC,CONFIG);
   SOS_Start_Timer(5,InitDisplay,PERIODIC,INIT_DISPLAY);
   SOS_Start_Timer(60,SendQuestion,PERIODIC,SEND_QUESTION);
   SOS_Start_Timer(65,WaitAns,PERIODIC,WAIT_ANSWER);
   /* start capturing push BTNS state when waiting for ans*/
   SOS_Start_Timer(30,GetPushBtnState,PERIODIC,WAIT_ANSWER); /* execute it periodically every 20ms when you are waiting answer */
   SOS_Start_Timer(5,ReportResult,PERIODIC,REPORT_RESULT); /* execute it periodically every 20ms when you are waiting answer */
   SOS_Start_Timer(100,FinishedReportResult,PERIODIC,FINISHED_REPORT_RESULT); /* execute it periodically every 20ms when you are waiting answer */

   //SOS_Start_Timer();
   /* Start Timer */
   Timer_Start(TIMER_0,0);   
   while (1)
   {
      SOS_Dispatch();
   }

}
 

  



  
  
  

 
 