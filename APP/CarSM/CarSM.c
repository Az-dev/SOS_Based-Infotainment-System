/*
 * CarSM.c
 *
 * Created: 2/19/2020 8:16:11 AM
 *  Author: Az
 */ 
/*- INCLUDES -----------------------------------------------------------------------------------------------------------------------*/
#include "CarSM.h"
#include "../Steering/Steering.h"
#include "../../ECUAL/Us/Us.h"
#include "../../ECUAL/SwDelay/SwDelay.h"
#include "../../ECUAL/LCD/char_lcd.h"

/*- DEFINES -----------------------------------------------------------------------------------------------------------------------*/
#define UP_BOUNDARY_DISTANCE   35
#define DOWN_BOUNDARY_DISTANCE 25

/*- FUNCTIONS DFINITIONS ----------------------------------------------------------------------------------------------------------*/
/*
*  Description : Initiate the car state machine with state"forward at speed 20%",
*
*  @param void
*
*  @param ERROR_STATUS
*/
ERROR_STATUS Car_SM_Init(void)
{   
   /*---------------------------------------------------- (  Initialization Phase )------------------------------------------------*/  
   /* 1 - Initialize Ultrasonic and SwICU for the purpose of distance calculations ----*/
   Us_Init();
   Icu_Init(&Icu_config);   
   /* 2- Initialize Steering ----*/
   Steering_Init();   
   /* 3 - Triggering Ultrasonic module ---*/
   Us_Trigger();  
   /*---- Return Success ----*/
   return E_OK;   
}

/*
 * Description : changes car state according to the ultrasonic input.
 *               car has 3 states to move in:
 *               1 - Moving Straight Forward       -----> when distance between car and object > 35.
 *               2 - Moving BackWard & Turn left   -----> when distanc between car and object  < 25.
 *               3 - Turn left                     -----> when distance between car and object <= 35 && <= 25.
 * 
 * @param void
 *
 * ERROR_STATUS
*/
ERROR_STATUS Car_SM_Update(void)
{   
   uint32_t au32_distance = 0;
   uint8_t arr_read[10];
   Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL, &au32_distance);
   /*---- Initialize and Test LCD ----*/
   LCD_init();       
   while(1)
   {
      /*---- Read Distance -----*/
      //Us_GetDistance(&au32_distance);
      Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL, &au32_distance);
      au32_distance = ((au32_distance * 64)/58);
      /*---- Display Distance --*/
      itoa_(au32_distance, (char*)arr_read, 10);
      LCD_send_string((char*)arr_read);
      softwareDelayMs(200);
      LCD_clear();
      /*---- Delay before triggering sensor again -----*/      
      Us_Trigger();             
      /*---- Check Boundary distances to take action ----*/
      if(au32_distance < (uint32_t)DOWN_BOUNDARY_DISTANCE)
      {
         /* Move BackWard & Turn left */        
         Steering_SteerCar(CAR_FORWARD, 50);
         softwareDelayMs(30);
         //Steering_SteerCar(CAR_STOP, 35);
         //softwareDelayMs(15);
         Steering_SteerCar(CAR_LEFT, 40);
         softwareDelayMs(7);
         
      }else if((au32_distance >= (uint32_t)DOWN_BOUNDARY_DISTANCE) && (au32_distance <= (uint32_t)UP_BOUNDARY_DISTANCE)){
         /* Turn left */
         Steering_SteerCar(CAR_RIGHT, 50);         
         softwareDelayMs(5);
         //Steering_SteerCar(CAR_STOP, 35);
         //softwareDelayMs(15);
         
      }else{
         /* Move Straight forward */
         Steering_SteerCar(CAR_BACKWARD, 35);
         softwareDelayMs(10);
         //Steering_SteerCar(CAR_STOP, 35);
         //softwareDelayMs(50); 
      } 
          
   }   
   /*---- Return Fail if loop is broken for any reason ----*/
   return E_NOK;   
}
