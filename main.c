/*
Ismat - Engenheria Informática 1º Ano
Programação Imperativa - Prof. Francisco Pereira
Leandro Fonseca
19/04/2021 - 17:47
Resumo: Programa de gerenciamento de contatos com alocaçao de memoria dinamica
Inputs:
Outputs:
 */


//ATENÇÃO O PROGRAMA FOI FEITO EM LINUX E NÃO FOI TESTADO NO WINDOWS
//PODE HAVER ALGUMA DIFERENÇA EM TERMOS DE KEYINPUTS
//SE TIVER PROBLEMAS RETIRAR coniolinux


#include <locale.h>
#include "contatos.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif


int main()

{
    setlocale(LC_ALL, "en_US.UTF-8");
    setlocale(LC_CTYPE, "en_US.UTF-8");

    struct contato *p2array = NULL;

    int intExit = 0, intContactCounter = 0;
    char chrMenuOption = '\0';

    p2array = allocContact(p2array);
    intContactCounter = contactFileCounting();



    while(intExit != 1){

        printMainMenu();
        scanf(" %c",&chrMenuOption);


        switch(chrMenuOption){

            case '0':
                intExit = 1;
                writeContactFile(p2array,intContactCounter);
                break;

            case '1':
                p2array = criarContato(p2array, intContactCounter);
                intContactCounter++;
                break;

            case '2':
                consultaSequencial(p2array, intContactCounter);
                break;

            case '3':
                listaContatos(p2array, intContactCounter);
                break;

            case '4':
                consultaAtributos(p2array,intContactCounter);
                break;

            case '5':
                modificarContato(p2array, intContactCounter);
                break;

            case '6':
                p2array = removerContato(p2array, intContactCounter);
                (p2array == NULL) ? intContactCounter = 0: intContactCounter == contactMemoryCounting(p2array, intContactCounter);
                break;

            case '7':
                p2array = apagarFileContatos(p2array);
                (p2array == NULL) ? intContactCounter = 0: intContactCounter;
                break;

            case '8':
                writeContactFile(p2array,intContactCounter);
                break;

            case '9':
                sobrePrograma();
                break;

            default:
                clsKeyboardBuffer();
                fflush(stdin);
                system(CLEAR);
                break;

        }
    }

    free(p2array);

    return 0;

}