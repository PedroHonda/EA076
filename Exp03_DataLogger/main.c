/* ###################################################################
**     Filename    : main.c
**     Project     : TestEEPROM
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-09-22, 14:59, # CodeGen: 0
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
#include "COLLECT_TEMP.h"
#include "TimerIntLdd2.h"
#include "TU2.h"
#include "AS1.h"
#include "ASerialLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/* User includes (#include below this line is not maintained by Processor Expert) */
uint16_t Temper = 0;
int Tmvolt = 0;
int Tc = 0;
union {
	  int celsiusInt;
	  uint8_t celsiusByte[2];
} T;
int CMD = 0;
// Union auxiliar para converter facilmente valores de hexa pra int
union {
	  int integer;
	  uint8_t bytes2[2];
} unionAUX;
int newDataRead = 0;
char reset[2] = {0x00, 0x00};
char registrosExistentes[2] = {0x00, 0x00};
char writeData[2];
int regExist;
/* COLUNAS e LINHAs - Flags */
int col = 0;
int lin = 0;
/* Estado da coleta periodica - iniciar ou finalizar */
int perCollect = 0; // inicia sem coletar
/* Functions */
void processKeyboard();
int intToStr(char *c, int integer);
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
    int writePOS = 0;
	char test1[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
	char test2[16] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
	char rcv[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  //EE241_WriteBlock(0x00, test1, 16);
  //EE241_WriteBlock(0x10, test2, 16);
  //EE241_ReadBlock(0x00, rcv, 32);
  
	//EE241_WriteBlock(0x3FE, reset, 2);	
  // Após este ponto, o programa entra no loop FOR infinito abaixo, basta dar um pause e ver as variáveis, especialmente o vetor "rcv"
  for(;;){
	if (perCollect && newDataRead) {
		if (Tc > 0) {
			// T.celsiusByte[1] = Mais significativo
			// T.celsiusByte[0] = Menos significativo
			T.celsiusInt = Tc;
		} else {
			// Realiza complemento de 2 caso Tc for negativo
			T.celsiusInt = 65536 + Tc;
		}
		EE241_ReadBlock(0x3FE, registrosExistentes, 2);
		unionAUX.bytes2[0] = registrosExistentes[1];
		unionAUX.bytes2[1] = registrosExistentes[0];
		regExist = unionAUX.integer;
		writePOS = regExist*2;
		writeData[0] = T.celsiusByte[1];
		writeData[1] = T.celsiusByte[0];
		EE241_WriteBlock(writePOS, writeData, 2);
		regExist++;
		unionAUX.integer = regExist;
		registrosExistentes[1] = unionAUX.bytes2[0];
		registrosExistentes[0] = unionAUX.bytes2[1];
		EE241_WriteBlock(0x3FE, registrosExistentes, 2);
		newDataRead = 0;
	}
	  
	  if (col) {
		  perCollect = 0;
		  col = 0;
		  processKeyboard();
		  COLUNA1_Disable();
		  COLUNA2_Disable();
		  COLUNA3_Disable();
		  WAIT_TECLADO_Waitms(150);
		  COLUNA1_Enable();
		  COLUNA2_Enable();
		  COLUNA3_Enable();
	  }
	  
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
// Return length
int intToStr (char *c, int integer){
	
	int len = 0;
	int digit;
	int auxInt = 0;
	auxInt = integer;
	while(auxInt>0) {
		auxInt /= 10;
		len++;
	}
	auxInt = integer;
	for(int i=1 ; i<=len ; i++){
		digit = auxInt%10;
		c[len-i] = digit+48;
		auxInt /= 10;
	}
	return len;
}
void processKeyboard() {
	int aux = 0;
	LED_PLACA_NegVal();
	AS1_SendChar('A');
	if (lin == 1) {
		// 1
		if (col == 1) {
			PDC1_WriteLineStr(1, "RESET     ");
			PDC1_WriteLineStr(2, "          ");
			PDC1_WriteLineStr(3, "          ");
			CMD = 1;
		}
		// 2
		else if (col == 2) {
			PDC1_WriteLineStr(1, "ID        ");
			PDC1_WriteLineStr(2, "          ");
			PDC1_WriteLineStr(3, "          ");
		}
		// 3
		else if (col == 3) {
			PDC1_WriteLineStr(1, "MEASURE   ");
			PDC1_WriteLineStr(2, "          ");
			PDC1_WriteLineStr(3, "          ");
			CMD = 3;
		}
	}
	else if (lin == 2) {
		// 4
		if (col == 1) {
			PDC1_WriteLineStr(1, "STATUS    ");
			PDC1_WriteLineStr(2, "          ");
			PDC1_WriteLineStr(3, "          ");
			CMD = 4;
		}
		// 5
		else if (col == 2) {
			PDC1_WriteLineStr(1, "INIT      ");
			PDC1_WriteLineStr(2, "          ");
			PDC1_WriteLineStr(3, "          ");
			CMD = 5;
		}
		// 6
		else if (col == 3) {
			PDC1_WriteLineStr(1, "FIN       ");
			PDC1_WriteLineStr(2, "          ");
			PDC1_WriteLineStr(3, "          ");
			CMD = 6;
		}
	}
	else if (lin == 3) {
		// 7
		if (col == 1) {
			PDC1_WriteLineStr(1, "DUMP      ");
			PDC1_WriteLineStr(2, "          ");
			PDC1_WriteLineStr(3, "          ");
			CMD = 7;
		}
	}
	else if (lin == 4) {
		// #
		if (col == 1) {
			switch(CMD) {
				case 1:
					// Insere 0x00 nas duas ultimas posicoes (1022 e 1023) da EEPROM
					EE241_WriteBlock(0x3FE, reset, 2);
					PDC1_WriteLineStr(1, "MEMORIA   ");
					PDC1_WriteLineStr(2, "APAGADA   ");
					PDC1_WriteLineStr(3, "          ");
					break;
				case 2:
					PDC1_WriteLineStr(1, "ID        ");
					PDC1_WriteLineStr(2, "          ");
					PDC1_WriteLineStr(3, "          ");
					break;
				case 3:
					int len;
					int inteiro;
					int decimais;
					char printINT[5];
					char printTemp[10];
					inteiro = Tc/10;
					decimais = Tc%10;
					len = intToStr(printINT, inteiro);
					strncpy(printTemp, printINT, len);
					len = intToStr(printINT, decimais);
					strncpy(printTemp+len, ",", 1);
					strncpy(printTemp+len+1, printINT, 1);
					strncpy(printTemp+len+2, "°C", 2);
					PDC1_WriteLineStr(1, "MEASURE   ");
					PDC1_WriteLineStr(2, printTemp);
					PDC1_WriteLineStr(3, "          ");
					break;
				case 4:
					char regExistSTR[4];
					char regDispSTR[4];
					char printExist[10];
					char printDisp[10];
					int regDisp;
					int len;
					EE241_ReadBlock(0x3FE, registrosExistentes, 2);
					unionAUX.bytes2[1] = registrosExistentes[0];
					unionAUX.bytes2[0] = registrosExistentes[1];
					regExist = unionAUX.integer;
					regDisp = 512 - regExist;
					len = intToStr(regExistSTR, regExist);
					strncpy(printExist, "EXIS:", 5);
					strncpy(printExist+5, regExistSTR, len);
					len = intToStr(regDispSTR, regDisp);
					strncpy(printDisp, "DISP:", 5);
					strncpy(printDisp+5, regDispSTR, len);
					PDC1_WriteLineStr(1, "STATUS    ");
					PDC1_WriteLineStr(2, printExist);
					PDC1_WriteLineStr(3, printDisp);
					break;
				case 5:
					perCollect = 1;
					PDC1_WriteLineStr(1, "INICIANDO ");
					PDC1_WriteLineStr(2, "COLETA    ");
					PDC1_WriteLineStr(3, "          ");
					break;
				case 6:
					perCollect = 0;
					PDC1_WriteLineStr(1, "FINALIZA  ");
					PDC1_WriteLineStr(2, "COLETA    ");
					PDC1_WriteLineStr(3, "          ");
					break;
				case 7:
					char data[2];
					int len;
					int inteiro;
					int decimais;
					char printINT[5];
					int i;
					int j;
					PDC1_WriteLineStr(1, "DUMPING   ");
					PDC1_WriteLineStr(2, "          ");
					PDC1_WriteLineStr(3, "          ");
					EE241_ReadBlock(0x3FE, registrosExistentes, 2);
					unionAUX.bytes2[1] = registrosExistentes[0];
					unionAUX.bytes2[0] = registrosExistentes[1];
					regExist = unionAUX.integer;
					for (i = 0 ; i <= regExist ; i++){
						// coleta 2 bytes de leitura da ROM
						aux = i*2;
						EE241_ReadBlock(aux, data, 2);
						// converte 2 bytes em um inteiro
						unionAUX.bytes2[1] = data[0];
						unionAUX.bytes2[0] = data[1];
						// separa digitos em inteiros e decimais
						inteiro = unionAUX.integer/10;
						decimais = unionAUX.integer%10;
						// converte inteiro para string
						len = intToStr(printINT, inteiro);
						for (j = 0 ; j < len ; j++) { 
							AS1_SendChar(printINT[j]);
						}
						AS1_SendChar(',');
						len = intToStr(printINT, decimais);
						for (j = 0 ; j < len ; j++) { 
							AS1_SendChar(printINT[j]);
						}
						AS1_SendChar('°');
						AS1_SendChar('C');
						AS1_SendChar('\r');
						AS1_SendChar('\n');
					}
					break;
				default:
					PDC1_WriteLineStr(1, "NO COMMAND");
					PDC1_WriteLineStr(2, "          ");
					PDC1_WriteLineStr(3, "          ");
			}
		}
		// *
		else if (col == 3) {
			PDC1_WriteLineStr(1, "CLEAR CMD ");
			PDC1_WriteLineStr(2, "          ");
			PDC1_WriteLineStr(3, "          ");
			CMD = 0;
		}
	}
}

