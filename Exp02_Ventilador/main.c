/* ###################################################################
**     Filename    : main.c
**     Project     : Projeto2
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-03-28, 21:08, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED_PLACA.h"
#include "BitIoLdd1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "PDC1.h"
#include "RESpin1.h"
#include "SCEpin1.h"
#include "D_Cpin1.h"
#include "WAIT1.h"
#include "KSDK1.h"
#include "SM1.h"
#include "RTC1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "LED_PLACA_GREEN.h"
#include "BitIoLdd2.h"
#include <string.h>
#include <stdio.h>
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
/* Global variables for Bluetooth */
int endOfCMD;
int counterBT = 0;
char BTchar;
char BTcharBUFF[20];
/* Global variables for RTC */
void *MyRTCPtr;
LDD_RTC_TTime TimePtr;
int year = 0;
/* Time Interruption variables */
int counter = 0;

/* Functions */
void processCMD ();
/* Other variables */
int pizza;
int main(void)
{
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  PDC1_WriteLineStr(3, "EA076");
  PDC1_WriteLineStr(4, "Ventilador");
  for(;;) {
	  //RTC1_GetTime(RTC1_DeviceData, &timeDate);
	  if (counter < 10) {
		  PDC1_WriteLineStr(1, "MENOR10");
	  } else if (counter < 20) {
		  PDC1_WriteLineStr(1, "MENOR20");
	  } else {
		  counter = 0;
	  }
	  if (endOfCMD) {
		  processCMD();
	  }
	  MyRTCPtr = RTC1_Init(pizza, FALSE);
	  RTC1_GetTime(MyRTCPtr, &TimePtr);
	  year = TimePtr.Year;

  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
void processCMD () {

    if (BTcharBUFF[counterBT] != "*"){
        endOfCMD = 0;
        counterBT = 0;
    }
    else {
        char par[10];
        int parINT;
        // strncmp returns 0 if the comparison matches
        if (!strncmp(BTcharBUFF, "VEL", 3)){
            strncpy(par, BTcharBUFF + 4, 3);
            parINT = atoi(par);
            //printf("%d\n\n", parINT);
        }
        else if (!strncmp(BTcharBUFF, "VENT", 4)){
            endOfCMD = 0;
        }
        else if (!strncmp(BTcharBUFF, "EXAUST", 6)){
            endOfCMD = 0;
        }
        else if (!strncmp(BTcharBUFF, "PARA", 4)){
            endOfCMD = 0;
        }
        else if (!strncmp(BTcharBUFFCMD, "ANO", 3)){
            strncpy(par, BTcharBUFF + 4, 4);
        }
        else if (!strncmp(BTcharBUFF, "MÊS", 3)){
            endOfCMD = 0;
        }
        else if (!strncmp(BTcharBUFF, "DIA", 3)){
            endOfCMD = 0;
        }
        else if (!strncmp(BTcharBUFF, "SEM", 3)){
            endOfCMD = 0;
        }
        else if (!strncmp(BTcharBUFF, "HORA", 4)){
            endOfCMD = 0;
        }
        else if (!strncmp(BTcharBUFFCMD, "MIN", 3)){
            endOfCMD = 0;
        }
        else if (!strncmp(BTcharBUFF, "SEG", 3)){
            endOfCMD = 0;
        } else {
            endOfCMD = 0;
        }

        
    }
    endOfCMD = 0;
}