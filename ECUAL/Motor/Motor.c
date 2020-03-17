/*
 * Motor.c
 *
 * Created: 2/18/2020 2:58:57 PM
 *  Author: Az
 */ 
/*- INCLUDES --------------------------------------------------------------------------------------------------------------*/
#include "Motor.h"
#include "Motor_Cfg.h"
#include "../../MCAL/PWM/PWM.h"
/*- FUNCTION DEFINITIONS --------------------------------------------------------------------------------------------------*/
/*
*  Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
*
*  @param uint8_t Motor_Number
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Motor_Init(uint8_t Motor_Number)
{
   switch (Motor_Number)
   {
      case MOTOR_1:;
         /*set directions of motor 1 enable bit*/
         strDioCfg_t motor_en1_config = 
         {
            MOTOR_EN_1_GPIO,
            MOTOR_EN_1_BIT,
            OUTPUT    
         };
         DIO_init(&motor_en1_config);      
         /*set direction of motor terminal "A" */
         strDioCfg_t motor_1a_config =
         {
            MOTOR_OUT_1A_GPIO,
            MOTOR_OUT_1A_BIT,
            OUTPUT
         };
         DIO_init(&motor_1a_config);      
         /*set direction of motor terminal "B" */
         strDioCfg_t motor_1b_config =
         {
            MOTOR_OUT_1B_GPIO,
            MOTOR_OUT_1B_BIT,
            OUTPUT
         };
         DIO_init(&motor_1b_config);      
      break;
      case MOTOR_2:;
         /*set directions of motor 2 enable bit*/
         strDioCfg_t motor_en2_config =
         {
            MOTOR_EN_2_GPIO,
            MOTOR_EN_2_BIT,
            OUTPUT
         };
         DIO_init(&motor_en2_config);         
         /*set direction of motor terminal "A" */
         strDioCfg_t motor_2a_config =
         {
            MOTOR_OUT_2A_GPIO,
            MOTOR_OUT_2A_BIT,
            OUTPUT
         };
         DIO_init(&motor_2a_config);         
         /*set direction of motor terminal "B" */
         strDioCfg_t motor_2b_config =
         {
            MOTOR_OUT_2B_GPIO,
            MOTOR_OUT_2B_BIT,
            OUTPUT
         };
         DIO_init(&motor_2b_config);        
      break;
   }
   return E_OK;
}

/*
*  Description	: Controls the motor direction from getting the motor number and the direction.
*
*  @param uint8_t Motor_Number
*  @param uint8_t Motor_Direction
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction)
{
   switch(Motor_Number)
   {
      case MOTOR_1:
         switch(Motor_Direction)
         {
            case MOTOR_STOP:         
               /*write 0 on MOTOR_EN_1_BIT*/            
               DIO_Write(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,LOW);
               /*write on terminals "A" & "B" of MOT_1 : 0 0*/
               DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
               DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
            break;
            case MOTOR_FORWARD:
               /*write 1 on MOTOR_EN_1_BIT*/
               DIO_Write(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,HIGH);
               /*write on terminals "A" & "B" of MOT_1 : 0 1*/
               DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
               DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,HIGH);
            break;
            case MOTOR_BACKWARD:
               /*write 1 on MOTOR_EN_1_BIT*/
               DIO_Write(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,HIGH);
               /*write on terminals "A" & "B" of MOT_1 : 1 0*/
               DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,HIGH);
               DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
            break;
         }
      break;
      case MOTOR_2:
         switch(Motor_Direction)
         {
            case MOTOR_STOP:
               /*write 0 on MOTOR_EN_2_BIT*/
               DIO_Write(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,LOW);
               /*write on terminals "A" & "B" of MOT_2 : 0 0*/
               DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
               DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
            break;
            case MOTOR_FORWARD:
               /*write 1 on MOTOR_EN_2_BIT*/
               DIO_Write(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,HIGH);
               /*write on terminals "A" & "B" of MOT_2 : 0 1*/
               DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
               DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,HIGH);
            break;
            case MOTOR_BACKWARD:
               /*write 1 on MOTOR_EN_2_BIT*/
               DIO_Write(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,HIGH);
               /*write on terminals "A" & "B" of MOT_2 : 1 0*/
               DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,HIGH);
               DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
            break;
         }
      break;
   }
   return E_OK;
}


/*
*  Description	: Controls the motor direction from getting the motor number and the direction.
*
*  @param uint8_t Motor_Number
*  @param uint8_t Mot_Speed
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed)
{
   /* Motor speed : represents a percent value , so its value is validated against the range [0-100]*/
   if((Mot_Speed >= 0) && (Mot_Speed <= 100))
   {
      /* Initialize HwPWM */
      Pwm_Init(&gstrPwmConfig);
      /* Initialize the motor */
      Motor_Init(Motor_Number);
      /* Set a direction and start move : we let the default direction is forward */
      Motor_Direction(Motor_Number,MOTOR_FORWARD);
      switch(Motor_Number)
      {
         case MOTOR_1:
            /* Start HwPWM for PWM_CH1A */
            Pwm_Start(PWM_CH1A,Mot_Speed,PWM_FREQ);            
         break;
         case MOTOR_2:
            /* Start HwPwm for PWM_CH1B */
            Pwm_Start(PWM_CH1B,Mot_Speed,PWM_FREQ);
         break;         
      }      
      /*return success*/
      return E_OK;
   }
   else
   {
      return E_NOK; /* Speed is not a valid value*/
   }  
}

/*
*  Description	: Controls the motor speed from getting the motor number and the speed.
*
*  @param uint8_t Motor_Number
*  @param uint8_t Speed
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed)
{
   /* Motor speed : represents a percent value , so its value is validated against the range [0-100]*/
   if((Speed >= 0) && (Speed <= 100))
   {
      switch(Motor_Number)
      {
         case MOTOR_1:
            /* Update PWM(Ton) for PWM_CH1A */
            Pwm_Start(PWM_CH1A,Speed,PWM_FREQ);
         break;
         case MOTOR_2:
            /* Update Pwm(Ton) for PWM_CH1B */
            Pwm_Start(PWM_CH1B,Speed,PWM_FREQ);
         break;
      }
      /*return success*/
      return E_OK;
   }
   else
   {
      return E_NOK; /* Speed is not a valid value*/
   }
   
}

/*
*  Description	: Stops the motor.
*
*  @param uint8_t Motor_Number
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Motor_Stop(uint8_t Motor_Number)
{
   switch (Motor_Number)
   {
      case MOTOR_1:
      case MOTOR_2:
         /* Stop PWM*/
         Pwm_Stop(PWM_CH1B);         
      break;         
   }
   return E_OK;
}

 /*
 *  Description	: Returns status of the motor whether initialized or not
 *
 *  @param uint8_t Motor_Number
 *  @param uint8_t * Mot_status (I/O param)
 *
 *  @return ERROR_STATUS
 */
 ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status)
 {
   return E_OK; 
 }
