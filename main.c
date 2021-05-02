#include <locale.h>
#include "contatos.h"

//Opção 1 - Completamente feito
//Opção 2 - Completamente feito
//Opção 3 - Completamente feito
//Opção 4 -
//Opção 5 -
//Opção 6 -
//Opção 7 -
//Opção 8 - Fazer qualquer coisa



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

//            case '4':
//                consultaAtributos();
//                break;
//
//            case '5':
//                modificarContato();
//                break;
//
//            case '6':
//                removerContato();
//                break;
//
            case '7':
                p2array = apagarFileContatos(p2array);
                break;

//            case '8':
//                sobrePrograma();
//                break;
//
            default:
                printf("Invalid choice");
                break;

        }
    }

    free(p2array);

    return 0;

}