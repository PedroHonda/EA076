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
/* As funcoes a seguir serao definidas posteriormente e basicamente garantem que apenas um determinado
LED esteja ativo enquanto o restante fique apagado, sendo que o semaforo se comportara de maneira
independente dos LEDs de pedestre.
Em outras palavras, a funcao setSemaGreen acendera o LED Verde de pedestre e apagara os LEDs verdes e amarelo */
void setSemaGreen();
void setSemaYellow();
void setSemaRed();
void setPedGreen();
void setPedRed();
/*
	Condicao inicial configurada nos componentes do PE
		Semaforo:	GREEN 	- 	ligado
					YELLOW	-	desligado
					RED		-	desligado
		
		Pedestre:	GREEN	-	desligado
					RED		-	ligado
*/
void TI1_OnInterrupt(void)
{
    /* Os contadores abaixo tem o unico proposito de utilizar o tempo da interrupcao para marcar o tempo em que
    determinado estado esta ativo*/
    static int cSema = 0; // apos o pedestre acionar o botao, esse contador controlara todos os estados de ambos os semaforos
    static int cLight = 0; // contador usado para evitar sombras momentaneas (uma pomba passando, por exemplo)
    static int cDark = 0; // contador usado para evitar clareamento momentaneo (farol, por exemplo)
    /* As variaveis a seguir serao utilizadas como flags, ou seja, tendo valores entre 0 e 1 apenas */
    static int isButton = 0; // flag utilizada para armazenar a acao do pedestre de apertar o botao.
                             // importante, pois o valor global isButtonPRESS sera atualizado sempre
    static int isLight = 1; // flag criada unicamente para evitar que a mudanca de estado para noite ocorra quando o processo
                            // de semaforo do pedestre esta acontecendo. Mais detalhes no programa a seguir
    static int period = 0; // period = 0: day, period = 1: night
    /* Variaveis globais importadas do programa principal */
    extern uint16_t valueLight;
    extern int isButtonPRESS;
    
    /* Primeira condicao a ser analisada sera a a flag que determina se esta de noite ou dia */
    switch (period) {
        // DAY
        case 0: 
            // Empiricamente, observou-se que o quando o valor lido for maior que 30000, indica que esta escuro
            if (valueLight > 30000) {
                // o timer para evitar mudancas momentaneas sera incrementado, e o estado mudara para noite apenas
                // quando se passar 10*250ms = 2.5 segundos, sendo 250ms o tempo de interrupcao configurado
                cDark++;
                if (cDark > 10)
                    isLight = 0;
            } else {
                // caso nao tenha se passado 2.5 segundos, e a situacao de luz volte, o contador sera zerado
                // isso evita a situacao em que um passaro passe pelo sensor LDR
                cDark = 0;
            }
            // So realizara medicoes de luz e de leitura de botao das variaveis globais quando a flag de botao
            // nao estiver ativada e o estado atual for semaforo de carros verde ativo
            if (SEMAGREEN_GetVal() && !isButton) {
                // Caso esteja neste estado, e a leitura acima indique que esteja num estado escuro por mais de 2.5 s
                // muda o estado para noite 
                if (!isLight) {
                    cDark = 0;
                    period = 1;
                    // a condicao inicial de noite sera o semaforo de pedestre em vermelho e o de carro em amarelo
                    setPedRed();
                    setSemaYellow();
                    break;
                }
                // Caso o pedestre pressione o botao, a flag isButton sera ativa
                // Note que a "condicao pai" "if (SEMAGREEN_GetVal() && !isButton)" nao entrara novamente ate que o processo
                // de semaforo acabe, o que impede que o estado mude para noite no meio desse processo, evitando acidentes
                if (isButtonPRESS == 1) {
                    isButton = 1;
                }
            }
            // Caso o botao venha a ser pressionado, inicia-se entao o processo de mudanca de estado dos semaforos
            if (isButton) {
                // Nos primeiros 2.5 segundos, o semaforo de carro permanecera verde
                if (cSema < 10)
                    cSema++;
                // Dos 2.5 seg ate 5 segundos, o semaforo de carro passa a ficar amarelo
                else if (cSema < 20) {
                    // ao mudar de estado, liga o semaforo de carro amarelo
                    if (cSema == 10) {
                        setSemaYellow();
                    }
                    cSema++;
                } 
                // Dos 5 segundos ate 7.5 segundos o semaforo de carro vai para vermelho e o de pedestre pra verde
                else if (cSema < 30) {
                    // ao mudar de estado, liga o semaforo de carro vermelho e pedestre verde
                    if (cSema == 20) {
                        setSemaRed();
                        setPedGreen();
                    }
                    cSema++;
                } 
                // Dos 7.5 segundos ate 10 segundos o semaforo de pedestre comeca a piscar vermelho
                else if (cSema < 40) {
                    // primeiro, liga apenas o semaforo vermelho
                    if (cSema == 30)
                        setPedRed();
                    // depois, comuta o valor do LED a cada 250 ms, proporcionando o efeito de pisca-pisca
                    else 
                        PEDRED_NegVal();
                    cSema++;
                } 
                // Por fim, passados 10 segundos, volta ao estado inicial de semaforo de carros em verde,
                // de pedestre em vermelho, e zera o contador de semaforo e a flag do botao
                else {
                    setSemaGreen();
                    setPedRed();
                    cSema=0;
                    isButton = 0;
                }
            }
            break;
        // NIGHT
        case 1:
            // Empiricamente, observou-se que o quando o valor lido for menor que 30000, indica que esta claro
            if (valueLight < 30000) {
                cLight++;
                // o timer para evitar mudancas momentaneas sera incrementado, e o estado mudara para dia apenas
                // quando se passar 10*250ms = 2.5 segundos, sendo 250ms o tempo de interrupcao configurado
                if (cLight > 10) {
                    cLight = 0;
                    period = 0;
                    // Condicao inicial de dia: Semaforo de carros em verde e de pedestre em vermelho
                    setPedRed();
                    setSemaGreen();
                    isLight = 1;
                    break;
                }
            } else {
                cDark = 0;
            } 
            // comuta os valores de semaforo pedestre vermelho e carro amarelo, produzindo pisca-pisca
            PEDRED_NegVal();
            SEMAYELLOW_NegVal();
            break;
    }

}
/* As funcoes a seguir serao definidas posteriormente e basicamente garantem que apenas um determinado
LED esteja ativo enquanto o restante fique apagado, sendo que o semaforo se comportara de maneira
independente dos LEDs de pedestre.
Em outras palavras, a funcao setSemaGreen acendera o LED Verde de pedestre e apagara os LEDs verdes e amarelo */
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
    PEDRED_SetVal();
    PEDGREEN_ClrVal();
}
void setPedRed() {
    PEDGREEN_SetVal();
    PEDRED_ClrVal();
}
/*
** ===================================================================
**     Event       :  LDR_OnEnd (module Events)
**
**     Component   :  LDR [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LDR_OnEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  LDR_OnCalibrationEnd (module Events)
**
**     Component   :  LDR [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LDR_OnCalibrationEnd(void)
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
