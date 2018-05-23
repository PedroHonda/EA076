/* ###################################################################
**     Filename    : Events.h
**     Project     : TestEEPROM
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-09-22, 14:59, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "EE241.h"
#include "WAIT1.h"
#include "GI2C1.h"
#include "MCUC1.h"
#include "CI2C1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "KSDK1.h"
#include "LED_PLACA.h"
#include "BitIoLdd1.h"
#include "LM61.h"
#include "AdcLdd1.h"
#include "LINHA1.h"
#include "BitIoLdd2.h"
#include "LINHA2.h"
#include "BitIoLdd3.h"
#include "LINHA3.h"
#include "BitIoLdd4.h"
#include "LINHA4.h"
#include "BitIoLdd5.h"
#include "COLUNA1.h"
#include "ExtIntLdd1.h"
#include "COLUNA2.h"
#include "ExtIntLdd2.h"
#include "COLUNA3.h"
#include "ExtIntLdd3.h"
#include "PTA.h"
#include "PTD.h"
#include "WAIT_TECLADO.h"
#include "PDC1.h"
#include "RESpin1.h"
#include "SCEpin1.h"
#include "D_Cpin1.h"
#include "SM1.h"

#ifdef __cplusplus
extern "C" {
#endif 

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
void Cpu_OnNMIINT(void);


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
void TI1_OnInterrupt(void);

void LM61_OnEnd(void);
/*
** ===================================================================
**     Event       :  LM61_OnEnd (module Events)
**
**     Component   :  LM61 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LM61_OnCalibrationEnd(void);
/*
** ===================================================================
**     Event       :  LM61_OnCalibrationEnd (module Events)
**
**     Component   :  LM61 [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void COLUNA3_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  COLUNA3_OnInterrupt (module Events)
**
**     Component   :  COLUNA3 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void COLUNA2_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  COLUNA2_OnInterrupt (module Events)
**
**     Component   :  COLUNA2 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void COLUNA1_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  COLUNA1_OnInterrupt (module Events)
**
**     Component   :  COLUNA1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  SM1_OnBlockSent (module Events)
**
**     Component   :  SM1 [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. This event is
**         available only if the SendBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SM1_OnBlockSent(LDD_TUserData *UserDataPtr);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
