#include <stdio.h>
#include "textlib.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

void printMainMenu(){
    system(CLEAR);
    printf(PROGRAM_TITLE);
    printf(MAINMENU_TITLE);
    printf(MAINMENU_TITLE_SEPARADOR);
    printf(MAINMENU_OPTION_1);
    printf(MAINMENU_OPTION_2);
    printf(MAINMENU_OPTION_3);
    printf(MAINMENU_OPTION_4);
    printf(MAINMENU_OPTION_5);
    printf(MAINMENU_OPTION_6);
    printf(MAINMENU_OPTION_7);
    printf(MAINMENU_OPTION_8);
    printf(MAINMENU_OPTION_9);
    printf(MAINMENU_OPTION_0);
    printf(MAINMENU_TITLE_SEPARADOR);
    printf(MAINMENU_USER_OPTION);
}
void printUnsCharString(int intLength, unsigned char chrString[intLength]){
    int intCounter = 0;

    for (intCounter = 0; intCounter < intLength; intCounter++){

        if(chrString[intCounter] != '\0'){
            printf("%lc", chrString[intCounter]);
        }else{
            intCounter = intLength + 1;
        }
    }
}
void printOption4Menu(){
    system(CLEAR);
    printf(OPTION4_TITLE);
    printf(OPTION4_SEPARADOR);
    printf(OPTION4_NAME);
    printf(OPTION4_PHONENUMBER);
    printf(OPTION4_ADRESS);
    printf(OPTION4_CP);
    printf(OPTION4_CITY);
    printf(OPTION4_COUNTRY);
    printf(OPTION4_SEPARADOR);
    printf(OPTION4_CHOOSE);
}