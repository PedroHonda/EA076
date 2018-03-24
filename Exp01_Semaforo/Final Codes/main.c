/* ###################################################################
**     Filename    : main.c
**     Project     : Semaforo
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-03-07, 21:12, # CodeGen: 0
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
#include "PEDRED.h"
#include "BitIoLdd1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "PEDGREEN.h"
#include "BitIoLdd2.h"
#include "SEMARED.h"
#include "BitIoLdd3.h"
#include "SEMAYELLOW.h"
#include "BitIoLdd4.h"
#include "SEMAGREEN.h"
#include "BitIoLdd5.h"
#include "BUTTON.h"
#include "BitIoLdd6.h"
#include "LIGHT.h"
#include "BitIoLdd7.h"
#include "LDR.h"
#include "AdcLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */


/* Global variables */
// NOTE: essas duas variaveis sao globais e serao escritas na funcao principal "main" e lidas na interrupcao
/* valueLight: variavel usada para obter o valor (em 16 bits) do conversor AD utilizando o sinal referente
   ao valor de tensao medido no LDR, que por sua vez utiliza de um divisor de tensao simples para tanto
*/
uint16_t valueLight;
/* isButtonPRESS: variavel global utilizada para ficar lendo constantemente o valor do GPIO conectado ao botao
*/
int isButtonPRESS = 0;
    


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;) {
    // esses proximos dois comandos sao utilizados para ler o valor do pino de ADC e armazena-lo na variavel valueLight
	  (void)LDR_Measure(TRUE); 
	  (void)LDR_GetValue16(&valueLight); 
    // le o valor do GPIO. caso isButtonPRESS for 1, quer dizer que o mesmo foi pressionado. Caso contrario, ele sera 0
	  isButtonPRESS = BUTTON_GetVal();
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
