/* ###################################################################
**     Filename    : Events.c
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
  /* Write your code here ... */
	static int counter = 0;
	extern int lin;
	counter++;
	if (counter == 1) {
		LINHA2_SetVal();
		LINHA3_SetVal();
		LINHA4_SetVal();
		LINHA1_ClrVal();
		lin = 1;
	} else if (counter == 2) {
		LINHA1_SetVal();
		LINHA3_SetVal();
		LINHA4_SetVal();
		LINHA2_ClrVal();
		lin = 2;
	} else if (counter == 3) {
		LINHA2_SetVal();
		LINHA1_SetVal();
		LINHA4_SetVal();
		LINHA3_ClrVal();
		lin = 3;
	} else if (counter == 4) {
		LINHA2_SetVal();
		LINHA3_SetVal();
		LINHA1_SetVal();
		LINHA4_ClrVal();
		lin = 4;
		counter = 0;
	}
	
	//printf("oi");
}

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
void LM61_OnEnd(void)
{
  /* Write your code here ... */
}

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
void LM61_OnCalibrationEnd(void)
{
  /* Write your code here ... */
}

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
void COLUNA3_OnInterrupt(void)
{
  /* Write your code here ... */
	extern int col;
	col = 3;
}

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
void COLUNA2_OnInterrupt(void)
{
  /* Write your code here ... */
	extern int col;
	col = 2;
}

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
void COLUNA1_OnInterrupt(void)
{
  /* Write your code here ... */
	extern int col;
	col = 1;
}

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
void SM1_OnBlockSent(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  COLLECT_TEMP_OnInterrupt (module Events)
**
**     Component   :  COLLECT_TEMP [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void COLLECT_TEMP_OnInterrupt(void)
{
	uint16_t Temper;
	extern int Tc;
	extern int Tmvolt;
	//extern int newDataRead;
	LM61_Measure(TRUE);
	LM61_GetValue16(&Temper);
	// T[mV] = 3.3*Temper*1000/65535 
	Tmvolt = Temper * 3300;
	Tmvolt /= 65535;
	Tc = Tmvolt - 600;
	//newDataRead = 1;
}

/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnRxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnTxChar(void)
{
  /* Write your code here ... */
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
