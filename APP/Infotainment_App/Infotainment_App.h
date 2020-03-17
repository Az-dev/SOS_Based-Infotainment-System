/*
 * Infotainment_App.h
 *
 * Created: 3/15/2020 9:47:24 PM
 *  Author: Az
 */ 

#ifndef INFOTAINMENT_APP_H_
#define INFOTAINMENT_APP_H_

/*- DEFINES & TYPEDEFS -----------------------------------------------------------------------------------------------*/
#define QUESTION_STRING_SIZE 100
/* SYSTEM STATES */
typedef enum syStates
{
   CONFIG = 1, /* Config state that replaces ONESHOOT :xD*/
   INIT_DISPLAY = 2,
   SEND_QUESTION = 3,
   CLEAR_QUESTION = 4,
   WAIT_ANSWER = 5,
   REPORT_RESULT = 6,
   FINISHED_REPORT_RESULT = 7
}syStates_t;

/* Display Init States */
#define DISPLAY_EN     100
#define SEND_COMMAND_1 101 
#define SEND_COMMAND_2 102
#define SEND_COMMAND_3 103
#define SEND_COMMAND_4 104
#define SEND_COMMAND_5 105
#define SEND_COMMAND_6 106
#define SEND_COMMAND_7 107

/* Questions Numbers States */
#define Q1 120
#define Q2 121
#define Q3 122
#define Q4 123
#define Q5 124 

/* Answers */
#define YES 1
#define NO  0

/*- FUNCTION DEFINITIONS ----------------------------------------------------------------------------------------------*/
/* 
*  Description : Add Tasks to System and Fire Dispatcher.
*
*  @param void 
*
*  @return void
*/
extern void SOS_Run(void);

#endif /* INFOTAINMENT_APP_H_ */