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
#include "VENT.h"
#include "BitIoLdd3.h"
#include "EXAU.h"
#include "BitIoLdd4.h"
#include "PWM1.h"
#include "PwmLdd1.h"
#include "TU2.h"
#include <string.h>
#include <stdio.h>
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
int estado = 0; // 0 = parado, 1 = vent, 2 = exaust
/* Global variables for Bluetooth */
int endOfCMD;
int counterBT = 0;
char BTchar;
char BTcharBUFF[20];
int CMDinex = 0;
/* Global variables for RTC */
char dateSTR[20];
char timeDaySTR[20];
void *MyRTCPtr;
LDD_RTC_TTime TimePtr;
char yearSTR[12];
int year = 0;
char monthSTR[12];
int month = 0;
char daySTR[12];
int day = 0;
char dayOfWeekSTR[12];
int dayOfWeek = 0;
char hourSTR[12];
int hour = 0;
char minuteSTR[12];
int minute = 0;
char secondSTR[12];
int second = 0;
/* Time Interruption variables */
int counter = 0;

/* Functions */
void processCMD ();
void sendOK ();
/* Other variables */
int pizza;
int main(void)
{
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  MyRTCPtr = RTC1_Init(&pizza, FALSE);
  for(;;) {
	  //RTC1_GetTime(RTC1_DeviceData, &timeDate);

	  counter = 0;
	  if (endOfCMD) {
		  //LED_PLACA_NegVal();
		  processCMD();
		  
	  }

	  if (counter == 1) {
		  
		  RTC1_GetTime(MyRTCPtr, &TimePtr);
		  year = TimePtr.Year;
		  sprintf(yearSTR, "%d", year);
		  month = TimePtr.Month;
		  sprintf(monthSTR, "%d", month);
		  day = TimePtr.Day;
		  sprintf(daySTR, "%d", day);
		  dayOfWeek = TimePtr.DayOfWeek;
		  if (dayOfWeek == 0) strcpy(dayOfWeekSTR, "DOM");
		  else if (dayOfWeek == 1) strcpy(dayOfWeekSTR, "SEG");
		  else if (dayOfWeek == 2) strcpy(dayOfWeekSTR, "TER");
		  else if (dayOfWeek == 3) strcpy(dayOfWeekSTR, "QUA");
		  else if (dayOfWeek == 4) strcpy(dayOfWeekSTR, "QUI");
		  else if (dayOfWeek == 5) strcpy(dayOfWeekSTR, "SEX");
		  else if (dayOfWeek == 6) strcpy(dayOfWeekSTR, "SAB");
		  hour = TimePtr.Hour;
		  sprintf(hourSTR, "%d", hour);
		  minute = TimePtr.Minute;
		  sprintf(minuteSTR, "%d", minute);
		  second = TimePtr.Second;
		  sprintf(secondSTR, "%d", second);
		  
		  strncpy(dateSTR, yearSTR, 4);
		  dateSTR[4]='/';
		  if (month<10){
			  dateSTR[5]='0';
			  strncpy(dateSTR+6, monthSTR, 1);
		  } else {
			  strncpy(dateSTR+5, monthSTR, 2);
		  }
		  dateSTR[7]='/';
		  if (day<10){
			  dateSTR[8]='0';
			  strncpy(dateSTR+9, daySTR, 1);
		  } else {
			  strncpy(dateSTR+8, daySTR, 2);
		  }
		  dateSTR[10]=' ';
		  strncpy(dateSTR+11, dayOfWeekSTR, 3);
		  PDC1_WriteLineStr(3, dateSTR);
		  
		  
		  if (hour<10){
			  timeDaySTR[0]='0';
			  strncpy(timeDaySTR+1, hourSTR, 1);
		  } else {
			  strncpy(timeDaySTR, hourSTR, 2);
		  }
		  timeDaySTR[2] = ':';
		  if (minute<10){
			  timeDaySTR[3]='0';
			  strncpy(timeDaySTR+4, minuteSTR, 1);
		  } else {
			  strncpy(timeDaySTR+3, minuteSTR, 2);
		  }
		  timeDaySTR[5] = ':';
		  if (second<10){
			  timeDaySTR[6]='0';
			  strncpy(timeDaySTR+7, secondSTR, 1);
		  } else {
			  strncpy(timeDaySTR+6, secondSTR, 2);
		  }
		  PDC1_WriteLineStr(4, timeDaySTR);
		  
		  counter = 0;
	  }
	  //PDC1_WriteLineStr(4, yearSTR);
	  //PDC1_WriteLineStr(3, monthSTR);

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
    char par[10];
    int parINT;
    char msg[20];
    int i;


    //PDC1_WriteLineStr(5, BTcharBUFF);
    if (BTcharBUFF[counterBT] != '*'){
        endOfCMD = 0;
        counterBT = 0;
    }
    else {
        // strncmp returns 0 if the comparison matches
        if (!strncmp(BTcharBUFF, "VEL", 3)){
        	if (counterBT<5){
            	strcpy(msg, "\nPARAMETRO INEXISTENTE\n");
                for (i=0;i<strlen(msg);i++) {
                    AS1_SendChar(msg[i]);
                    WAIT1_Waitms(1);
                }
        	} else {
                strncpy(par, BTcharBUFF + 4, counterBT-4);
                parINT = atoi(par);
                if (parINT > 100){
                	strcpy(msg, "\nPARAMETRO INCORRETO\n");
                    for (i=0;i<strlen(msg);i++) {
                        AS1_SendChar(msg[i]);
                        WAIT1_Waitms(1);
                    }
                } else {
                    parINT = 100 - parINT;
                    parINT *= 2.55;
                    PWM1_SetRatio8(parINT);
                    par[3] = ' '; 
                    par[4] = '%';
                    PDC1_WriteLineStr(2, par);
                    sendOK();
                    AS1_SendChar('%');
                    AS1_SendChar('\n');
                    WAIT1_Waitms(1);
                }
        	}

        }
        else if (!strncmp(BTcharBUFF, "VENT", 4)){
        	if (estado == 2) {
                VENT_ClrVal();
                EXAU_ClrVal();
        		WAIT1_Waitms(1000);
        	}
        	estado = 1;
            VENT_SetVal();
            PDC1_WriteLineStr(1, "VENTILADOR");
            sendOK();
            AS1_SendChar('\n');
            WAIT1_Waitms(1);
        }
        else if (!strncmp(BTcharBUFF, "EXAUST", 6)){
        	if (estado == 1){
                VENT_ClrVal();
                EXAU_ClrVal();
        		WAIT1_Waitms(1000);
        	}
        	estado = 2;
            EXAU_SetVal();
            PDC1_WriteLineStr(1, "EXAUSTOR  ");
            sendOK();
            AS1_SendChar('\n');
            WAIT1_Waitms(1);
        }
        else if (!strncmp(BTcharBUFF, "PARA", 4)){
        	estado = 0;
            VENT_ClrVal();
            EXAU_ClrVal();
            PDC1_ClearLine(1);
            PDC1_WriteLineStr(1, "PARADO    ");
            sendOK();
            AS1_SendChar('\n');
            WAIT1_Waitms(1);
        }
        else if (!strncmp(BTcharBUFF, "ANO", 3)){
        	if (counterBT<5){
            	strcpy(msg, "\nPARAMETRO INEXISTENTE\n");
                for (i=0;i<strlen(msg);i++) {
                    AS1_SendChar(msg[i]);
                    WAIT1_Waitms(1);
                }
        	} else {
                strncpy(par, BTcharBUFF + 4, 4);
                parINT = atoi(par);
        		if ((parINT > 2099) || (parINT == 0)){
					strcpy(msg, "\nPARAMETRO INCORRETO\n");
					for (i=0;i<strlen(msg);i++) {
						AS1_SendChar(msg[i]);
						WAIT1_Waitms(1);
					}
				} else {
	    			//MyRTCPtr = RTC1_Init(pizza, FALSE);
	    			TimePtr.Year = parINT;
	    			if (TimePtr.Year == 2018) LED_PLACA_NegVal();
	    			RTC1_SetTime(MyRTCPtr, &TimePtr);
	    			counterBT = 3;
	    			sendOK();
	    		    AS1_SendChar('\n');
	    		    WAIT1_Waitms(1);
				}
        	}
        }
        else if (!strncmp(BTcharBUFF, "MES", 3)){
        	if (counterBT<5){
            	strcpy(msg, "\nPARAMETRO INEXISTENTE\n");
                for (i=0;i<strlen(msg);i++) {
                    AS1_SendChar(msg[i]);
                    WAIT1_Waitms(1);
                }
        	} else {
                strncpy(par, BTcharBUFF + 4, counterBT-4);
                parINT = atoi(par);
                if ((parINT > 12) || (parINT == 0)){
					strcpy(msg, "\nPARAMETRO INCORRETO\n");
					for (i=0;i<strlen(msg);i++) {
						AS1_SendChar(msg[i]);
						WAIT1_Waitms(1);
					}
				} else {
	    			//MyRTCPtr = RTC1_Init(pizza, FALSE);
	    			TimePtr.Month = parINT;
	    			RTC1_SetTime(MyRTCPtr, &TimePtr);
	    			counterBT = 3;
	    			sendOK();
	    		    AS1_SendChar('\n');
	    		    WAIT1_Waitms(1);
				}
        	}
        }
        else if (!strncmp(BTcharBUFF, "DIA", 3)){
        	if (counterBT<5){
            	strcpy(msg, "\nPARAMETRO INEXISTENTE\n");
                for (i=0;i<strlen(msg);i++) {
                    AS1_SendChar(msg[i]);
                    WAIT1_Waitms(1);
                }
        	} else {
                strncpy(par, BTcharBUFF + 4, counterBT-4);
                parINT = atoi(par);
                if ((parINT > 31) || (parINT == 0)){
					strcpy(msg, "\nPARAMETRO INCORRETO\n");
					for (i=0;i<strlen(msg);i++) {
						AS1_SendChar(msg[i]);
						WAIT1_Waitms(1);
					}
				} else {
	    			//MyRTCPtr = RTC1_Init(pizza, FALSE);
	    			TimePtr.Day = parINT;
	    			RTC1_SetTime(MyRTCPtr, &TimePtr);
	    			counterBT = 3;
	    			sendOK();
	    		    AS1_SendChar('\n');
	    		    WAIT1_Waitms(1);
				}
        	}
        }
        else if (!strncmp(BTcharBUFF, "SEM", 3)){
        	if (counterBT<5){
            	strcpy(msg, "\nPARAMETRO INEXISTENTE\n");
                for (i=0;i<strlen(msg);i++) {
                    AS1_SendChar(msg[i]);
                    WAIT1_Waitms(1);
                }
        	} else {
                strncpy(par, BTcharBUFF + 4, counterBT-4);
                parINT = atoi(par);
                if ((parINT > 7) || (parINT == 0)){
					strcpy(msg, "\nPARAMETRO INCORRETO\n");
					for (i=0;i<strlen(msg);i++) {
						AS1_SendChar(msg[i]);
						WAIT1_Waitms(1);
					}
				} else {
	    			//MyRTCPtr = RTC1_Init(pizza, FALSE);
	    			TimePtr.DayOfWeek = parINT+1;
	    			RTC1_SetTime(MyRTCPtr, &TimePtr);
	    			counterBT = 3;
	    			sendOK();
	    		    AS1_SendChar('\n');
	    		    WAIT1_Waitms(1);
				}
        	}
        }
        else if (!strncmp(BTcharBUFF, "HORA", 4)){
        	if (counterBT<6){
            	strcpy(msg, "\nPARAMETRO INEXISTENTE\n");
                for (i=0;i<strlen(msg);i++) {
                    AS1_SendChar(msg[i]);
                    WAIT1_Waitms(1);
                }
        	} else {
                strncpy(par, BTcharBUFF + 5, counterBT-5);
                parINT = atoi(par);
                if (parINT > 23){
					strcpy(msg, "\nPARAMETRO INCORRETO\n");
					for (i=0;i<strlen(msg);i++) {
						AS1_SendChar(msg[i]);
						WAIT1_Waitms(1);
					}
				} else {
	    			//MyRTCPtr = RTC1_Init(pizza, FALSE);
	    			TimePtr.Hour = parINT;
	    			RTC1_SetTime(MyRTCPtr, &TimePtr);
	    			counterBT = 4;
	    			sendOK();
	    		    AS1_SendChar('\n');
	    		    WAIT1_Waitms(1);
				}
        	}
        }
        else if (!strncmp(BTcharBUFF, "MIN", 3)){
        	if (counterBT<5){
            	strcpy(msg, "\nPARAMETRO INEXISTENTE\n");
                for (i=0;i<strlen(msg);i++) {
                    AS1_SendChar(msg[i]);
                    WAIT1_Waitms(1);
                }
        	} else {
                strncpy(par, BTcharBUFF + 4, counterBT-4);
                parINT = atoi(par);
                if (parINT > 59){
					strcpy(msg, "\nPARAMETRO INCORRETO\n");
					for (i=0;i<strlen(msg);i++) {
						AS1_SendChar(msg[i]);
						WAIT1_Waitms(1);
					}
				} else {
	    			//MyRTCPtr = RTC1_Init(pizza, FALSE);
	    			TimePtr.Minute = parINT;
	    			RTC1_SetTime(MyRTCPtr, &TimePtr);
	    			counterBT = 3;
	    			sendOK();
	    		    AS1_SendChar('\n');
	    		    WAIT1_Waitms(1);
				}
        	}
        }
        else if (!strncmp(BTcharBUFF, "SEG", 3)){
        	if (counterBT<5){
            	strcpy(msg, "\nPARAMETRO INEXISTENTE\n");
                for (i=0;i<strlen(msg);i++) {
                    AS1_SendChar(msg[i]);
                    WAIT1_Waitms(1);
                }
        	} else {
                strncpy(par, BTcharBUFF + 4, counterBT-4);
                parINT = atoi(par);
                if (parINT > 59){
					strcpy(msg, "\nPARAMETRO INCORRETO\n");
					for (i=0;i<strlen(msg);i++) {
						AS1_SendChar(msg[i]);
						WAIT1_Waitms(1);
					}
				} else {
	    			//MyRTCPtr = RTC1_Init(pizza, FALSE);
	    			TimePtr.Second = parINT;
	    			RTC1_SetTime(MyRTCPtr, &TimePtr);
	    			counterBT = 3;
	    			sendOK();
	    		    AS1_SendChar('\n');
	    		    WAIT1_Waitms(1);
				}
        	}
        } else {     	
        	strcpy(msg, "\nCOMANDO INEXISTENTE\n");
            for (i=0;i<strlen(msg);i++) {
                AS1_SendChar(msg[i]);
                WAIT1_Waitms(1);
            }
        }

        
    }
	endOfCMD = 0;
	counterBT = 0;
}

void sendOK () {
    AS1_SendChar('\n');
    WAIT1_Waitms(1);
    AS1_SendChar('O');
    WAIT1_Waitms(1);
    AS1_SendChar('K');
    WAIT1_Waitms(1);
    AS1_SendChar(' ');
    WAIT1_Waitms(1);
    int i;
    for (i=0;i<counterBT;i++) {
        AS1_SendChar(BTcharBUFF[i]);
        WAIT1_Waitms(1);
    }
}

