#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "coniolinux.h"
#include "textlib.h"

typedef struct contato{
    unsigned char chrNome[20],chrTelefone[10],chrMorada[30],chrCodPostal[10],chrCidade[20],chrPais[20];
} contatos;



/*Protótipos das funçoes de alocação de memoria*/
int contactFileCounting();
struct contato *allocContact(struct contato *p2array);
void writeContactFile(struct contato *p2array, int intContactCounter);



/*Protótipos das funçoes de validação de dados*/
void clearArray(int intStringLength, unsigned char chrArray[intStringLength]);
void clsKeyboardBuffer(void);
unsigned char linuxPTchar();
void nomeContato(int intStringLength, unsigned char chrData[intStringLength]);
void numeroTelefone(int intContactCounter,struct contato *p2array,int intStringLength, unsigned char chrData[intStringLength]);
void moradaContato(int intContactCounter,struct contato *p2array,int intStringLength, unsigned char chrData[intStringLength]);
void codPostalContato(int intContactCounter,struct contato *p2array,int intStringLength, unsigned char chrData[intStringLength]);
void cidadeContato(int intContactCounter,struct contato *p2array,int intStringLength, unsigned char chrData[intStringLength]);
void paisContato(int intContactCounter,struct contato *p2array,int intStringLength, unsigned char chrData[intStringLength]);

/*Protótipos das funções principais*/
struct contato *criarContato(struct contato *p2array, int intContactCounter);
void consultaSequencial(struct contato *p2array, int intContactCounter);
void listaContatos(struct contato *p2array, int intContactCounter);
void consultaAtributos();
void modificarContato();
void removerContato();
struct contato *apagarFileContatos(struct contato *p2array);
void sobrePrograma();
void consultaNome();

