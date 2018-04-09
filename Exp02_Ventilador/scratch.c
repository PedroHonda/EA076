#include <stdio.h>
#include <string.h>

char CMD[50];
int readingCMD = 0;
int CMDlength = 0;
int CMDbuffPointer = 0;


void cleanCMDbuffer ()

// CMDlength does not count * as part of it
void processCMD () {

    if (CMD[CMDlength] != "*"){
        readingCMD = 0;
        CMDlength = 0;
        CMDbuffPointer = 0;
    }
    else {
        char par[10];
        int parINT;
        // strncmp returns 0 if the comparison matches
        if (!strncmp(CMD, "VEL", 3)){
            strncpy(par, CMD + 4, 3);
            parINT = atoi(par);
            //printf("%d\n\n", parINT);
        }
        else if (!strncmp(CMD, "VENT", 4)){
            readingCMD = 0;
        }
        else if (!strncmp(CMD, "EXAUST", 6)){
            readingCMD = 0;
        }
        else if (!strncmp(CMD, "PARA", 4)){
            readingCMD = 0;
        }
        else if (!strncmp(CMD, "ANO", 3)){
            readingCMD = 0;
        }
        else if (!strncmp(CMD, "MÊS", 3)){
            readingCMD = 0;
        }
        else if (!strncmp(CMD, "DIA", 3)){
            readingCMD = 0;
        }
        else if (!strncmp(CMD, "SEM", 3)){
            readingCMD = 0;
        }
        else if (!strncmp(CMD, "HORA", 4)){
            readingCMD = 0;
        }
        else if (!strncmp(CMD, "MIN", 3)){
            readingCMD = 0;
        }
        else if (!strncmp(CMD, "SEG", 3)){
            readingCMD = 0;
        } else {
            readingCMD = 0;
        }

        
    }
    readingCMD = 0;
}

void main (){

}