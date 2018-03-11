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
void TI1_OnInterrupt(void)
{
    static int contador_pedestre = 0;
    static int contador_semaforo = 0;
    static int isButton = 1;
    SEMAYELLOW_NegVal();
    //if (PUSHBUTTON_GetRawVal())
        //isButton = 1;
    SEMAGREEN_NegVal();
    /*if (isButton){
        if (contador_semaforo < 10){
            //PEDGREEN_SetVal();
            //PEDRED_ClrVal();
            SEMAGREEN_SetVal();
            contador_semaforo++;
        }
        else if (contador_semaforo < 20) {
            // Turns yellow
            //PEDGREEN_SetVal();
            //PEDRED_SetVal();
            SEMAGREEN_ClrVal();
            SEMAYELLOW_SetVal();
            contador_semaforo++;
        } else if (contador_semaforo < 30) {
            // Turns red
            //PEDGREEN_ClrVal();
            //PEDRED_SetVal();
            SEMAYELLOW_ClrVal();
            contador_semaforo++;
        } else if (contador_semaforo > 50){
            // Turns green
            //PEDGREEN_SetVal();
            //PEDRED_ClrVal();
            SEMAGREEN_SetVal();
            contador_semaforo=0;
        }
    }*/
    /*
    if (contador_pedestre){
        PEDRED_NegVal();
        contador_pedestre = 0;
    } else {
        PEDGREEN_NegVal();
        contador_pedestre = 1;
    }*/
    
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