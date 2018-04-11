#include <stdio.h>
#include <string.h>

char CMD[50];
int endOfCMD = 0;
int counterBT = 0;
int CMDbuffPointer = 0;


void cleanCMDbuffer ()

// counterBT does not count * as part of it
void processCMD () {

    if (BTcharBUFF[counterBT] != "*"){
        endOfCMD = 0;
        counterBT = 0;
        CMDbuffPointer = 0;
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
            endOfCMD = 0;
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

void main (){

}