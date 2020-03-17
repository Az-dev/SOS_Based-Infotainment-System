/*
 * SOS.c
 *
 * Created: 3/15/2020 4:37:17 PM
 * Author : Az
 */ 

/*- INCLUDES -------------------------------------------------------------------------------------------------------------------*/
#include "Test/Test.h"
#include "APP/CarSM/CarSM.h"
#include "APP/BCM_BasedApp/BCM_Based.h"
#include "APP/Infotainment_App/Infotainment_App.h"
/*- Main FUNCTION DEFINITION ---------------------------------------------------------------------------------------------------*/
int main(void)
{

   /*------------------- START TMU APPLICATION  ------------------------*/
   //TmuTest();
   /*------------------- END TMU APPLICATION   ------------------------*/
   
   /*------------------- START SOS APPLICATION  ------------------------*/
   //SosTest();
   SOS_Run();
   /*------------------- END SOS APPLICATION   ------------------------*/
   
   /*------------------- START CAR APPLICATION  ------------------------*/
   //Car_SM_Init();
   //Car_SM_Update();
   /*------------------- END CAR APPLICATION   ------------------------*/
   
   /*---------------------- Start test ----------------------------*/
   //TimerTest(); /* ---> test passed*/
   /* DioTest();  ----> test passed */
   /* HwPwmTest(); ---> bypassed    */
   /* MotorTest(); ---> test passed and approved HwPWM */
   /* IcuTest();   ---> Finallly passed */
   //UsTest();
   //IcuWithUsTest(); /*--> Fully passed :xD */
   //masterSpi();  //---->success
   //slaveSpi();  //-----> success
   //myUsartFullDuplexInterruptTest(); // ----> test passed for both transmission and reciption
   /*---------------------- End test ------------------------------*/
   
   /*--------------------- Start BCM test -----------------------------*/
   //BCM_Transmit();  /* Burn its hex on master */
   //BCM_Receive();   /* Burn its hex on slave */
   /*--------------------- End BCM test -------------------------------*/
   
   
   
}

