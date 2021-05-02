#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Defines para imprimir o menu inicial*/
#define PROGRAM_TITLE "\t\t============ Agenda de Contatos ============\n\n\n\n"
#define MAINMENU_TITLE "\t\t\t       Menu Principal\n"
#define MAINMENU_TITLE_SEPARADOR "\t\t\t============================\n"
#define MAINMENU_OPTION_1 "\t\t\t[1] Criar novo contato\n"
#define MAINMENU_OPTION_2 "\t\t\t[2] Consulta sequencial\n"
#define MAINMENU_OPTION_3 "\t\t\t[3] Lista de contatos\n"
#define MAINMENU_OPTION_4 "\t\t\t[4] Consulta por atributos\n"
#define MAINMENU_OPTION_5 "\t\t\t[5] Modificar contatos\n"
#define MAINMENU_OPTION_6 "\t\t\t[6] Remover contato\n"
#define MAINMENU_OPTION_7 "\t\t\t[7] Apagar lista de contatos\n"
#define MAINMENU_OPTION_8 "\t\t\t[8] Sobre o programa\n"
#define MAINMENU_OPTION_0 "\t\t\t[0] Sair do programa\n"
#define MAINMENU_USER_OPTION "\n\t\t\tDigite a opção que deseja: "

/* Defines para Opção Criar novo contato*/
#define OPTION4_TITLE "\t\t\tConsulta por atributos\n"
#define OPTION4_SEPARADOR "==============================================\n\n"
#define OPTION4_NAME "\t\t\t[1] Nome\n"
#define OPTION4_PHONENUMBER "\t\t\t[2] Número de Telefone\n"
#define OPTION4_ADRESS "\t\t\t[3] Morada\n"
#define OPTION4_CP "\t\t\t[4] Código Postal\n"
#define OPTION4_CITY "\t\t\t[5] Cidade\n"
#define OPTION4_COUNTRY "\t\t\t[6] País\n"
#define OPTION4_CHOOSE "\n\t..::Escolha o atributo pelo qual deseja encontrar o contato: "



void printUnsCharString(int intLength, unsigned char chrString[intLength]);
void printMainMenu();
void printOption4Menu();






