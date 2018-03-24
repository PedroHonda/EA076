/* ###################################################################
**     Filename    : Events.c
**     Project     : Semaforo
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-03-07, 21:12, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void setSemaGreen();
void setSemaYellow();
void setSemaRed();
void setPedGreen();
void setPedRed();
void TI1_OnInterrupt(void)
{
    static int cButton = 0;
    static int cSema = 0;
    static int cLight = 0;
    static int cDark = 0;
    static int isButton = 0;
    static int isLight = 1;
    static int period = 0; // period = 0: day, period = 1: night
	static int init = 0;
	if (init == 0) {
		setSemaGreen();
		PEDRED_ClrVal();
		PEDGREEN_SetVal();
		init++;
	}
    switch (period) {
        // DAY
        case 0: 
            // If the current value is Dark
            // ----------------NEED TO CHECK HERE FOR PIN/VARIABLE_NAME DESTINATED TO LIGHT
            if (LIGHT_GetVal() == 1) {
                cDark++;
                if (cDark > 10)
                    isLight = 0;
            } else {
                cDark = 0;
            }
            // During daytime, we only get light and button measurements when Green Light is on
            if (SEMAGREEN_GetVal() && !isButton) {
                // Changing period to Night will only take effect if Pedestrian traffic is not currently enabled
                if (!isLight) {
                    cDark = 0;
                    period = 1;
                    setPedGreen();
                    setSemaYellow();
                    break;
                }
                // ----------------NEED TO CHECK HERE FOR PIN/VARIABLE_NAME DESTINATED TO BUTTON
                if (BUTTON_GetVal() == 1) {
                    isButton = 1;
                }
            }
            if (isButton) {
                if (cSema < 10){
                    cSema++;
                } else if (cSema < 20) {
                    if (cSema == 10) {
                        setSemaYellow();
                    }
                    cSema++;
                } else if (cSema < 30) {
                    if (cSema == 20) {
                        setSemaRed();
                        // liga led verde
                        setPedRed();
                    }
                    cSema++;
                } else if (cSema < 40) {
                    if (cSema == 30) {
                    	// liga led vermelho
                        setPedGreen();
                    } else {
                    	// pisca led vermelho
                        PEDRED_NegVal();
                    }
                    cSema++;
                } else {
                    setSemaGreen();
                    // pisca led vermelho
                    setPedGreen();
                    cSema=0;
                    isButton = 0;
                }
            }
            break;
        // NIGHT
        case 1:
            // If the current value is Light
            if (LIGHT_GetVal() == 0) {
                cLight++;
                if (cLight > 10) {
                    cLight = 0;
                    period = 0;
                    // liga vermelho
                    setPedGreen();
                    setSemaGreen();
                    isLight = 1;
                    break;
                }
            } else {
                cDark = 0;
            } 
            // liga o led vermelho
            PEDRED_NegVal();
            SEMAYELLOW_NegVal();
            break;
    }

}
void setSemaGreen() {
    SEMAYELLOW_ClrVal();
    SEMARED_ClrVal();
    SEMAGREEN_SetVal();
}
void setSemaYellow() {
    SEMAGREEN_ClrVal();
    SEMARED_ClrVal();
    SEMAYELLOW_SetVal();
}
void setSemaRed() {
    SEMAYELLOW_ClrVal();
    SEMAGREEN_ClrVal();
    SEMARED_SetVal();
}
void setPedGreen() {
    PEDRED_ClrVal();
    PEDGREEN_SetVal();
}
void setPedRed() {
    PEDGREEN_ClrVal();
    PEDRED_SetVal();
}
/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
