#include "contatos.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif


//----->Funções de alocação de memoria

//Enumera o numero de contatos existentes no ficheiro
int contactFileCounting(){
    FILE *fp;
    int intContactCounter = 0;
    contatos lista;

    //Abrir ficheiro
    fp = fopen("leandro.dat","r");

    //Ler ficheiro
    while(fread(&lista,sizeof(contatos),1,fp)==1)
    {
        //Contar contatos existentes no ficheiro
        intContactCounter++;
    }

    //Fechar ficheiro
    fclose(fp);

    return intContactCounter;   //Retorna numero de contatos no ficheiro
}

//Aloca memória num array de structs consoante o que existe no ficheiro
struct contato *allocContact(struct contato *p2array){
    FILE *fp;
    int intCounter = 0;
    contatos lista;

    //Verifica se existe ficheiro
    if((fp = fopen("leandro.dat","r"))!=NULL)
    {
        //printf("Ficheiro existe\n\n");
    }
    else
    {
        //Cria ficheiro caso não exista
        fp = fopen("leandro.dat","w+");
        //printf("Ficheiro não existe!");

    }

    //Enquanto existir ler structs do ficheiro
    while(fread(&lista,sizeof(contatos),1,fp)==1)
    {
        //Realocar memória no array de structs
        p2array = realloc(p2array, (intCounter+1) * sizeof(contatos));

        //Armazenar contatos do ficheiro no array
        p2array[intCounter] = lista;
        intCounter++;
    }


    fclose(fp);
    return p2array;
}

//Escreve os contatos da memória no ficheiro
void writeContactFile(struct contato *p2array, int intContactCounter){
    FILE *fp;

    int intCounter = 0;

    //Abrir ficheiro
    fp = fopen("leandro.dat", "w+");

    //Percorrer o array de contatos
    for(intCounter = 0; intCounter < intContactCounter; intCounter++){
        //Escrever contato no ficheiro
        fwrite(&p2array[intCounter], sizeof(contatos), 1, fp);
    }
    //Fechar ficheiro
    fclose(fp);
}

int contactMemoryCounting(struct contato *p2array, int intContactCounter){
    int intCounter = 0, structsize = 0, arraysize = 0;

    structsize = sizeof(struct contato);
    arraysize = ((size_t*)p2array)[-1];

    intCounter = arraysize / structsize;

    return intCounter;
}

//----->Funçoes de manipulação de contatos



//Cria um novo contato na memória
struct contato *criarContato(struct contato *p2array, int intContactCounter){

    //Limpar terminal
    system(CLEAR);

    fflush(stdin);  //Limpa buffer

    //Realocar memória para o array de structs para mais um contato
    p2array = realloc(p2array, (intContactCounter+1) * sizeof(contatos));

    clsKeyboardBuffer();    //Limpar buffer

    nomeContato(20,p2array[intContactCounter].chrNome);  //Entrada/Validação de dados para Nome
    fflush(stdin);

    numeroTelefone(intContactCounter, p2array,10,p2array[intContactCounter].chrTelefone);   //Entrada/Validação de dados para Telefone
    fflush(stdin);

    moradaContato(intContactCounter, p2array,30,p2array[intContactCounter].chrMorada);  //Entrada/Validação de dados para Morada
    fflush(stdin);

    codPostalContato(intContactCounter, p2array,10,p2array[intContactCounter].chrCodPostal);    //Entrada/Validação de dados para Codigo Postal
    fflush(stdin);

    cidadeContato(intContactCounter, p2array,20,p2array[intContactCounter].chrCidade);  //Entrada/Validação de dados para Cidade
    fflush(stdin);

    paisContato(intContactCounter, p2array,20,p2array[intContactCounter].chrPais);  //Entrada/Validação de dados para Pais
    fflush(stdin);


    printf("\n\n---> Contato criado com sucesso!");
    printf("\n..::Pressione qualquer tecla para continuar");
    getche();

    return p2array;     //Retorna pointer do array com novo contato
}

//Display dos contatos que estão na memória pela ordem do qual foram criados
void consultaSequencial(struct contato *p2array, int intContactCounter){
    int intCounter = 0, intFound = 0;
    unsigned char chrInput = '\0';

    fflush(stdin);
    intFound=0;

    clsKeyboardBuffer();    //Limpar buffer

    //Verificar se o array está vazio
    if(p2array == NULL){
        system(CLEAR);

        printf("\n\t\t================================\n\t\t\tConsulta Sequencial\n\t\t================================");
        printf("\n\n\n===================================================================================================");


        printf("\n\n---> Não existem contatos na sua lista de contatos!");
        printf("\nDICA: Para criar contatos escolha a Opção 1 do Menu Principal");
        printf("\n\n..::Pressione qualquer tecla para continuar");
        fflush(stdin);
        getche();
        return;
    }


    //Ler os contatos da memória
    for(intCounter = 0; intCounter < intContactCounter; )
    {
        system(CLEAR);

        printf("\n\t\t================================\n\t\t\tConsulta Sequencial\n\t\t================================");
        printf("\n\n\n===================================================================================================");



        printf("\n\n\t\tNome: \t\t");
        printUnsCharString(20, p2array[intCounter].chrNome);
        printf("\n\t\tTelefone: \t");
        printUnsCharString(10, p2array[intCounter].chrTelefone);
        printf("\n\t\tMorada: \t");
        printUnsCharString(30, p2array[intCounter].chrMorada);
        printf("\n\t\tCódigo Postal: \t");
        printUnsCharString(10, p2array[intCounter].chrCodPostal);
        printf("\n\t\tCidade: \t");
        printUnsCharString(20, p2array[intCounter].chrCidade);
        printf("\n\t\tPaís: \t\t");
        printUnsCharString(20, p2array[intCounter].chrPais);
        printf("\n");
        printf("\n\n===================================================================================================\n");
        printf("Para avançar para o contato seguinte prima '0'\n");
        printf("Para recuar para o contato seguinte prima '1'\n");
        printf("Para voltar para o menu principal prima 'Enter'\n");


        fflush(stdin);
        chrInput = getche();

        //Premir tecla 0 para avançar contato
        if(chrInput == 48){
            //Se não der para voltar mais para tras volta para o fim
            if(intCounter == intContactCounter - 1 ){
                intCounter = 0;
                intFound++;
            }else{
                intCounter++;
                intFound++;
            }
        //Premir tecla 1 para recuar contato
        }else if(chrInput == 49){
            //Se não der para voltar mais para tras volta para o fim
            if(intCounter == 0){
                intCounter = intContactCounter - 1;
                intFound++;
            }else{
                intCounter--;
                intFound++;
            }
        //Premir Enter para sair da lista
        }else if(chrInput == 10){
            break;
        }else{

        }

    }

}

//Display dos contatos que estão na memória por ordem alfabetica
void listaContatos(struct contato *p2array, int intContactCounter){
    int intCounter = 0, intFound = 0, intLetra = 0;

    clsKeyboardBuffer();    //Limpar buffer

    system(CLEAR);

    printf("\n\t\t================================\n\t\t\tLista de Contatos\n\t\t================================");
    printf("\n\n\n===================================================================================================");

    //Verificar se não exite nenhum contato no array
    if(p2array == NULL){
        fflush(stdin);
        printf("\n\n---> Lista de contatos vazia!");
        printf("\nDICA: Para criar contatos escolha a Opção 1 do Menu Principal");
        printf("\n\n..::Pressione qualquer tecla para continuar");
        getche();
        return;
    }



    //Percorrer o alfabeto
    for(intLetra=97; intLetra<=122; intLetra++)
    {
        intFound = 0;

        //Ler os contatos da memória
        for(intCounter = 0; intCounter < intContactCounter; intCounter++)
        {
            //Verificar se a primeira letra do nome é igual á letra
            if(p2array[intCounter].chrNome[0]==intLetra || p2array[intCounter].chrNome[0]==intLetra-32)
            {
                printf("\n\n\t\tNome: \t\t");
                printUnsCharString(20, p2array[intCounter].chrNome);
                printf("\n\t\tTelefone: \t");
                printUnsCharString(10, p2array[intCounter].chrTelefone);
                printf("\n\t\tMorada: \t");
                printUnsCharString(30, p2array[intCounter].chrMorada);
                printf("\n\t\tCódigo Postal: \t");
                printUnsCharString(10, p2array[intCounter].chrCodPostal);
                printf("\n\t\tCidade: \t");
                printUnsCharString(20, p2array[intCounter].chrCidade);
                printf("\n\t\tPaís: \t\t");
                printUnsCharString(20, p2array[intCounter].chrPais);
                printf("\n");
                intFound++;
            }
        }

        //Separador para indicar quando termina a listagem de uma letra
        if(intFound!=0)
        {
            printf("\n\n============================================================================================ [%c]-(%d)\n\n",intLetra-32,intFound);
        }

    }

    fflush(stdin);
    printf("\n\n---> Lista de Contatos exibida com sucesso!");
    printf("\n..::Pressione qualquer tecla para continuar");
    getche();

}

void consultaAtributos(struct contato *p2array, int intContactCounter){

    int intFound = 0, intLength = 20, intCounter = 0, intChoice = 0;

    system(CLEAR);
    clsKeyboardBuffer();

    if(p2array == NULL){
        printf("Não existem contatos para consultar!!");
        fflush(stdin);
        getche();
        return;
    }


    intFound = 0;
    printOption4Menu();
    fflush(stdin);

    scanf("%d", &intChoice);
    fflush(stdin);

    switch (intChoice) {
        case 1:
            consultaNome(p2array, intContactCounter);
            break;
        case 2:
            consultaTelefone(p2array, intContactCounter);
            break;
        case 3:
            consultaMorada(p2array, intContactCounter);
            break;
        case 4:
            consultaCodPostal(p2array, intContactCounter);
            break;
        case 5:
            consultaCidade(p2array, intContactCounter);
            break;
        case 6:
            consultaPais(p2array, intContactCounter);
            break;
        default:
            printf("\nOpção inválida!");
            printf("\n--->Clique em qq tecla para voltar ao menu");
            clsKeyboardBuffer();
            fflush(stdin);
            getche();
            system(CLEAR);
            break;
    }

}

void modificarContato(struct contato *p2array, int intContactCounter){

    int intCounter = 0, intFound = 0;
    unsigned char chrInput = '\0';

    fflush(stdin);
    intFound=0;

    clsKeyboardBuffer();    //Limpar buffer

    //Verificar se o array está vazio
    if(p2array == NULL){
        system(CLEAR);

        printf("\n\t\t================================\n\t\t\tModificar contatos\n\t\t================================");
        printf("\n\n\n===================================================================================================");


        printf("\n\n---> Não existem contatos na sua lista de contatos!");
        printf("\nDICA: Para criar contatos escolha a Opção 1 do Menu Principal");
        printf("\n\n..::Pressione qualquer tecla para continuar");
        fflush(stdin);
        getche();
        return;
    }


    //Ler os contatos da memória
    for(intCounter = 0; intCounter < intContactCounter; ) {
        system(CLEAR);

        printf("\n\t\t================================\n\t\t\tModificar Contato\n\t\t================================");
        printf("\n\n\n===================================================================================================");


        printf("\n\n\t\tNome: \t\t");
        printUnsCharString(20, p2array[intCounter].chrNome);
        printf("\n\t\tTelefone: \t");
        printUnsCharString(10, p2array[intCounter].chrTelefone);
        printf("\n\t\tMorada: \t");
        printUnsCharString(30, p2array[intCounter].chrMorada);
        printf("\n\t\tCódigo Postal: \t");
        printUnsCharString(10, p2array[intCounter].chrCodPostal);
        printf("\n\t\tCidade: \t");
        printUnsCharString(20, p2array[intCounter].chrCidade);
        printf("\n\t\tPaís: \t\t");
        printUnsCharString(20, p2array[intCounter].chrPais);
        printf("\n");
        printf("\n\n===================================================================================================\n");
        printf("Para avançar para o contato seguinte prima '0'\n");
        printf("Para recuar para o contato anterior prima '1'\n");
        printf("Para editar o contato prima 'Delete'\n");
        printf("Para voltar para o menu principal prima 'Enter'\n");


        fflush(stdin);
        chrInput = getche();

        //Premir tecla delete para editar
        if(chrInput == 127)
        {
            nomeContato(20,p2array[intCounter].chrNome);  //Entrada/Validação de dados para Nome
            fflush(stdin);

            numeroTelefone(intCounter, p2array,10,p2array[intCounter].chrTelefone);   //Entrada/Validação de dados para Telefone
            fflush(stdin);

            moradaContato(intCounter, p2array,30,p2array[intCounter].chrMorada);  //Entrada/Validação de dados para Morada
            fflush(stdin);

            codPostalContato(intCounter, p2array,10,p2array[intCounter].chrCodPostal);    //Entrada/Validação de dados para Codigo Postal
            fflush(stdin);

            cidadeContato(intCounter, p2array,20,p2array[intCounter].chrCidade);  //Entrada/Validação de dados para Cidade
            fflush(stdin);

            paisContato(intCounter, p2array,20,p2array[intCounter].chrPais);  //Entrada/Validação de dados para Pais
            fflush(stdin);


            printf("\n\n---> Contato modificado com sucesso!");
            printf("\n..::Pressione qualquer tecla para continuar");
            getche();



        }
        //Premir tecla 0 para avançar contato
        else if(chrInput == 48){
            //Se não der para voltar mais para tras volta para o fim
            if(intCounter == intContactCounter - 1 ){
                intCounter = 0;
                intFound++;
            }else{
                intCounter++;
                intFound++;
            }
            //Premir tecla 1 para recuar contato
        }else if(chrInput == 49){
            //Se não der para voltar mais para tras volta para o fim
            if(intCounter == 0){
                intCounter = intContactCounter - 1;
                intFound++;
            }else{
                intCounter--;
                intFound++;
            }
            //Premir Enter para sair da lista
        }else if(chrInput == 10){
            break;
        }else{

        }

    }

}

struct contato *removerContato(struct contato *p2array, int intContactCounter){

    int intCounter = 0, intFound = 0;
    unsigned char chrInput = '\0';

    fflush(stdin);
    intFound=0;

    clsKeyboardBuffer();    //Limpar buffer

    //Verificar se o array está vazio
    if(p2array == NULL){
        system(CLEAR);

        printf("\n\t\t================================\n\t\t\tApagar contatos\n\t\t================================");
        printf("\n\n\n===================================================================================================");


        printf("\n\n---> Não existem contatos na sua lista de contatos!");
        printf("\nDICA: Para criar contatos escolha a Opção 1 do Menu Principal");
        printf("\n\n..::Pressione qualquer tecla para continuar");
        fflush(stdin);
        getche();
        return p2array;
    }


    //Ler os contatos da memória
    for(intCounter = 0; intCounter < intContactCounter; ) {
        system(CLEAR);

        printf("\n\t\t================================\n\t\t\tApagar Contatos\n\t\t================================");
        printf("\n\n\n===================================================================================================");


        printf("\n\n\t\tNome: \t\t");
        printUnsCharString(20, p2array[intCounter].chrNome);
        printf("\n\t\tTelefone: \t");
        printUnsCharString(10, p2array[intCounter].chrTelefone);
        printf("\n\t\tMorada: \t");
        printUnsCharString(30, p2array[intCounter].chrMorada);
        printf("\n\t\tCódigo Postal: \t");
        printUnsCharString(10, p2array[intCounter].chrCodPostal);
        printf("\n\t\tCidade: \t");
        printUnsCharString(20, p2array[intCounter].chrCidade);
        printf("\n\t\tPaís: \t\t");
        printUnsCharString(20, p2array[intCounter].chrPais);
        printf("\n");
        printf("\n\n===================================================================================================\n");
        printf("Para avançar para o contato seguinte prima '0'\n");
        printf("Para recuar para o contato anterior prima '1'\n");
        printf("Para apagar o contato prima 'Delete'\n");
        printf("Para voltar para o menu principal prima 'Enter'\n");


        fflush(stdin);
        chrInput = getche();

        //Premir tecla delete para apagar
        if(chrInput == 127) {
            printf("\n\nTêm a certeza que deseja apagar o contato?");
            printf("\n\t\t[1] Sim\n");
            printf("\t\t[2] Não\n\n");
            printf("Digite a opção que deseja selecionar: ");
            scanf("%c", &chrInput);


            //Confirmar apagar contato
            if (chrInput == 49) {
                for (intCounter; intCounter < intContactCounter; intCounter++) {

                    if (intCounter == intContactCounter - 1) {
                        p2array = realloc(p2array, (intCounter) * sizeof(contatos));
                        printf("\n\n---> Contato apagado com sucesso!");
                        printf("\n..::Pressione qualquer tecla para continuar");
                        clsKeyboardBuffer();
                        fflush(stdin);
                        getche();
                        return p2array;
                    } else {
                        p2array[intCounter] = p2array[intCounter + 1];
                    }

                }
            //Nao alterar nada
            }else if (chrInput == 50){
                printf("\n\n---> Contato mantém-se intacto!");
                printf("\n..::Pressione qualquer tecla para continuar");
                clsKeyboardBuffer();
                fflush(stdin);
                getche();
            }else{
            }

        }
            //Premir tecla 0 para avançar contato
        else if(chrInput == 48){
            //Se não der para ir mais para frente volta para o inicio
            if(intCounter == intContactCounter - 1 ){
                intCounter = 0;
                intFound++;
            }else{
                intCounter++;
                intFound++;
            }
            //Premir tecla 1 para recuar contato
        }else if(chrInput == 49){
            //Se não der para voltar mais para tras volta para o fim
            if(intCounter == 0){
                intCounter = intContactCounter - 1;
                intFound++;
            }else{
                intCounter--;
                intFound++;
            }
            //Premir Enter para sair da lista
        }else if(chrInput == 10){
            break;
        }else{

        }

        }


    return p2array;
}

//Apaga ficheiro de contatos e contatos da memória (retorna NULL)
struct contato *apagarFileContatos(struct contato *p2array){
    char chrChoice = '\0';
    FILE *fp;


    system(CLEAR);
    printf("AVISO! Ao eliminar o ficheiro que contém os contatos, perderá permanentemente os seus contatos!\n");
    printf("================================================================================================================\n\n");
    printf("Deseja eliminar o ficheiro de contatos?\n");
    printf("\t\t[1] Sim\n");
    printf("\t\t[2] Não\n\n");
    printf("Digite a opção que deseja selecionar: ");
    scanf(" %c", &chrChoice);
    fflush(stdin);

    //Verificar opção do user
    if(chrChoice != 49){
        printf("\n\nFicheiro de contatos mantém-se intacto!");
        printf("\n..::Pressione qualquer tecla para continuar");
        clsKeyboardBuffer();    //Limpar buffer
        getche();
    }else{
        system(CLEAR);
        printf("AVISO! Ao eliminar o ficheiro que contém os contatos, perderá permanentemente os seus contatos!\n");
        printf("================================================================================================================\n\n");
        printf("Tem a certeza que deseja eliminar o ficheiro de contatos?\n");
        printf("\t\t[1] Não\n");
        printf("\t\t[2] Sim\n\n");
        printf("Digite a opção que deseja selecionar: ");
        scanf(" %c", &chrChoice);
        fflush(stdin);

        //Verificar se o user deseja eliminar contatos
        if(chrChoice == 50){
            //Verificar se existe ficheiro
            if((fp = fopen("leandro.dat","r"))!=NULL)
            {
                //Caso exista ficheiro
                fclose(fp);
                remove("leandro.dat");  //Eliminar ficheiro de contatos
                free(p2array);      //Libertar memória do array
                p2array = NULL;     //Apagar contatos da memória
                printf("\n\nFicheiro de contatos eliminado com sucesso!");
                printf("\n..::Pressione qualquer tecla para continuar");
                clsKeyboardBuffer();
                getche();
            }
            else
            {
                //Se não existir ficheiro
                free(p2array);
                p2array = NULL;     //Apagar contatos da memória
                printf("\n\nFicheiro de contatos eliminado com sucesso!");
                printf("\n..::Pressione qualquer tecla para continuar");
                clsKeyboardBuffer();
                getche();
            }

        }else{
            printf("\n\nFicheiro de contatos mantém-se intacto!");
            printf("\n..::Pressione qualquer tecla para continuar");
            clsKeyboardBuffer();
            getche();
        }
    }
    return p2array;
}

//Display de algumas informações do programa
void sobrePrograma(){
    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tSobre o Programa\n\t\t================================");
    printf("\n\n\n===================================================================================================");
    printf("\n\t  Este programa foi desenvolvido por Leandro Fonseca na disciplina de Programação Imperativa do curso de Engenharia Informática do Ismat pelo docente Francisco José de Melo Pereira.");
    printf("\n\n\t  O intuito do programa é ser um gestor de contatos na qual os contatos ficam guardados no ficheiro \"leandro.dat\".");
    printf("\n\t  Ao iniciar o programa lê todos os contatos que se encontram no ficheiro e copia-los para a memória, na qual onde vão ser trabalhados \n\tnum array de structs com memória alocada dinâmica até ao fim da execução do programa, ou seja, as alterações dos contatos só seram gravadas se o programa terminar de forma regular.");
    printf("\n\n..::Pressione qualquer tecla para continuar");

    clsKeyboardBuffer();
    getche();
}





//----->Funções de validação de dados

//Percorre um array e poe o valores de todos os valores a 0
void clearArray(int intStringLength, unsigned char chrArray[intStringLength]){
    int i = 0;
    for (i = 0; i <intStringLength; ++i) {
        chrArray[i] = '\0';
    }
}

//Transforma os caracteres multibyte para codigo UTF-8 e retorna
unsigned char linuxPTchar(){
    //Caracteres Portugueses Linux
    //Linux - Se utilizar unsigned char e subtrair ao ultimo numero da tabela extendida ascii (255)
    //o 195 que é a keycode das teclas especiais no layout portugues, e somar
    //o segundo keycode do caracter e somar 4 obtem-se o codigo ascii da extended table utf-8
    //printf("%lc %d\n", 255-195+((int)chr)+4,255-195+((int)chr)+4);
    unsigned char intKeycode = 0, intUTF8 = 0;
    intKeycode = getche();
    intUTF8 = 255 - 195 + (int)intKeycode + 4;
    return intUTF8;
}

//Limpa o buffer do teclado
void clsKeyboardBuffer(void){
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF){
        return;
    }
}

//Validação de entrada de dados para campo Nome
void nomeContato(int intStringLength, unsigned char chrData[intStringLength]){
    //Letras minúsculas + espaço +  letras maiusculas

    int intStringPosition = 0;
    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrData;

    clearArray(intStringLength,chrData);    //Limpa o array

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
    printf("Nome: ");
    printUnsCharString(20,chrData);


    do {
        chrUserInput = getche();
        //Letras Minúsculas + espaço +  Letras Maiusculas
        if ((chrUserInput > 96 && chrUserInput < 123) || (chrUserInput == 32) ||(chrUserInput > 64 && chrUserInput < 91)) {
            chrUserData[intStringPosition] = chrUserInput;
            chrUserData[intStringPosition+1] = 0;
            intStringPosition++;
        }
            //Letras portuguesas minusculas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();
            if((chrUserInput > 223 && chrUserInput < 255) || (chrUserInput > 191 && chrUserInput < 222)){
                chrUserData[intStringPosition] = chrUserInput;
                chrUserData[intStringPosition+1] = '\0';
                intStringPosition++;
            }else{
                chrUserData[intStringPosition] = '\0';
                system(CLEAR);
                printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
                printf("Nome: ");
                printUnsCharString(20,chrData);
            }

        }
            //Tecla de Enter
        else if(chrUserInput == 10){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            chrUserData[intStringPosition] = '\0';
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,chrData);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,chrData);
        }
    } while (intStringPosition < intStringLength);

}

//Validação de entrada de dados para campo Numero de Telefone
void numeroTelefone(int intContactCounter,struct contato *p2array,int intStringLength, unsigned char chrData[intStringLength]){
    //Numeros Inteiros

    int intStringPosition = 0;
    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrData;

    clearArray(intStringLength,chrData);    //Limpa o array

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
    printf("Nome: ");
    printUnsCharString(20,p2array[intContactCounter].chrNome);
    printf("\nNumero de telemovel: ");
    printUnsCharString(10,chrData);


    do {
        chrUserInput = getche();

        //Numeros Inteiros
        if (chrUserInput > 47 && chrUserInput < 58) {
            chrUserData[intStringPosition] = chrUserInput;
            intStringPosition++;
        }
            //Letras portuguesas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();

            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,chrData);

        }
            //Tecla de Enter
        else if(chrUserInput == 10 || chrUserInput == 13){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,chrData);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,chrData);
        }
    }while (intStringPosition < intStringLength);

}

//Validação de entrada de dados para campo Morada
void moradaContato(int intContactCounter,struct contato *p2array,int intStringLength, unsigned char chrData[intStringLength]){
    //Todos caracteres

    int intStringPosition = 0;
    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrData;

    clearArray(intStringLength,chrData);

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
    printf("Nome: ");
    printUnsCharString(20,p2array[intContactCounter].chrNome);
    printf("\nNumero de telemovel: ");
    printUnsCharString(10,p2array[intContactCounter].chrTelefone);
    printf("\nMorada: ");
    printUnsCharString(30,chrData);


    do {
        chrUserInput = getche();
        //Todos os caracteres
        if ((chrUserInput > 32 && chrUserInput < 127) || (chrUserInput == 32) ) {
            chrUserData[intStringPosition] = chrUserInput;
            chrUserData[intStringPosition+1] = '\0';
            intStringPosition++;
        }
            //Letras portuguesas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();
            if(chrUserInput > 191 && chrUserInput < 255){
                chrUserData[intStringPosition] = chrUserInput;
                chrUserData[intStringPosition+1] = '\0';
                intStringPosition++;
            }else{
                chrUserData[intStringPosition] = '\0';
                system(CLEAR);
                printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
                printf("Nome: ");
                printUnsCharString(20,p2array[intContactCounter].chrNome);
                printf("\nNumero de telemovel: ");
                printUnsCharString(10,p2array[intContactCounter].chrTelefone);
                printf("\nMorada: ");
                printUnsCharString(30,chrData);
            }

        }
            //Tecla de Enter
        else if(chrUserInput == 10){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,p2array[intContactCounter].chrTelefone);
            printf("\nMorada: ");
            printUnsCharString(30,chrData);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,p2array[intContactCounter].chrTelefone);
            printf("\nMorada: ");
            printUnsCharString(30,chrData);
        }
    } while (intStringPosition < intStringLength);

}

//Validação de entrada de dados para campo Código Postal
void codPostalContato(int intContactCounter,struct contato *p2array,int intStringLength, unsigned char chrData[intStringLength]) {
    //Numeros Inteiros + travessao

    int intStringPosition = 0;
    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrData;

    clearArray(intStringLength,chrData);    //Limpa o array

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
    printf("Nome: ");
    printUnsCharString(20,p2array[intContactCounter].chrNome);
    printf("\nNumero de telemovel: ");
    printUnsCharString(10,p2array[intContactCounter].chrTelefone);
    printf("\nMorada: ");
    printUnsCharString(30,p2array[intContactCounter].chrMorada);
    printf("\nCódigo Postal: ");
    printUnsCharString(10,chrData);


    do {
        chrUserInput = getche();

        //Numeros Inteiros
        if ((chrUserInput > 47 && chrUserInput < 58) || (chrUserInput == 45)) {
            chrUserData[intStringPosition] = chrUserInput;
            intStringPosition++;
        }
        //Letras portuguesas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();

            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,p2array[intContactCounter].chrTelefone);
            printf("\nMorada: ");
            printUnsCharString(30,p2array[intContactCounter].chrMorada);
            printf("\nCódigo Postal: ");
            printUnsCharString(10,chrData);

        }
            //Tecla de Enter
        else if(chrUserInput == 10 || chrUserInput == 13){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,p2array[intContactCounter].chrTelefone);
            printf("\nMorada: ");
            printUnsCharString(30,p2array[intContactCounter].chrMorada);
            printf("\nCódigo Postal: ");
            printUnsCharString(10,chrData);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,p2array[intContactCounter].chrTelefone);
            printf("\nMorada: ");
            printUnsCharString(30,p2array[intContactCounter].chrMorada);
            printf("\nCódigo Postal: ");
            printUnsCharString(10,chrData);
        }
    }while (intStringPosition < intStringLength);

}

//Validação de entrada de dados para campo Cidade
void cidadeContato(int intContactCounter,struct contato *p2array,int intStringLength, unsigned char chrData[intStringLength]){
    //Letras minúsculas + letras maiusculas + espaço

    int intStringPosition = 0;
    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrData;

    clearArray(intStringLength,chrData);    //Limpa o array

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
    printf("Nome: ");
    printUnsCharString(20,p2array[intContactCounter].chrNome);
    printf("\nNumero de telemovel: ");
    printUnsCharString(10,p2array[intContactCounter].chrTelefone);
    printf("\nMorada: ");
    printUnsCharString(30,p2array[intContactCounter].chrMorada);
    printf("\nCódigo Postal: ");
    printUnsCharString(10,p2array[intContactCounter].chrCodPostal);
    printf("\nCidade: ");
    printUnsCharString(20,chrData);


    do {
        chrUserInput = getche();
        //Letras Minúsculas + espaço +  Letras Maiusculas
        if ((chrUserInput > 96 && chrUserInput < 123) ||(chrUserInput > 64 && chrUserInput < 91) || (chrUserInput == 32)) {
            chrUserData[intStringPosition] = chrUserInput;
            chrUserData[intStringPosition+1] = 0;
            intStringPosition++;
        }
            //Letras portuguesas minusculas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();
            if((chrUserInput > 223 && chrUserInput < 255) || (chrUserInput > 191 && chrUserInput < 222)){
                chrUserData[intStringPosition] = chrUserInput;
                chrUserData[intStringPosition+1] = '\0';
                intStringPosition++;
            }else{
                chrUserData[intStringPosition] = '\0';
                system(CLEAR);
                printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
                printf("Nome: ");
                printUnsCharString(20,p2array[intContactCounter].chrNome);
                printf("\nNumero de telemovel: ");
                printUnsCharString(10,p2array[intContactCounter].chrTelefone);
                printf("\nMorada: ");
                printUnsCharString(30,p2array[intContactCounter].chrMorada);
                printf("\nCódigo Postal: ");
                printUnsCharString(10,p2array[intContactCounter].chrCodPostal);
                printf("\nCidade: ");
                printUnsCharString(20,chrData);
            }

        }
            //Tecla de Enter
        else if(chrUserInput == 10){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            chrUserData[intStringPosition] = '\0';
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,p2array[intContactCounter].chrTelefone);
            printf("\nMorada: ");
            printUnsCharString(30,p2array[intContactCounter].chrMorada);
            printf("\nCódigo Postal: ");
            printUnsCharString(10,p2array[intContactCounter].chrCodPostal);
            printf("\nCidade: ");
            printUnsCharString(20,chrData);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,p2array[intContactCounter].chrTelefone);
            printf("\nMorada: ");
            printUnsCharString(30,p2array[intContactCounter].chrMorada);
            printf("\nCódigo Postal: ");
            printUnsCharString(10,p2array[intContactCounter].chrCodPostal);
            printf("\nCidade: ");
            printUnsCharString(20,chrData);
        }
    } while (intStringPosition < intStringLength);

}

//Validação de entrada de dados para campo País
void paisContato(int intContactCounter,struct contato *p2array,int intStringLength, unsigned char chrData[intStringLength]){
    //Letras minúsculas + letras maiusculas + espaço

    int intStringPosition = 0;
    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrData;

    clearArray(intStringLength,chrData);    //Limpa o array

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
    printf("Nome: ");
    printUnsCharString(20,p2array[intContactCounter].chrNome);
    printf("\nNumero de telemovel: ");
    printUnsCharString(10,p2array[intContactCounter].chrTelefone);
    printf("\nMorada: ");
    printUnsCharString(30,p2array[intContactCounter].chrMorada);
    printf("\nCódigo Postal: ");
    printUnsCharString(10,p2array[intContactCounter].chrCodPostal);
    printf("\nCidade: ");
    printUnsCharString(20,p2array[intContactCounter].chrCidade);
    printf("\nPaís: ");
    printUnsCharString(20,chrData);


    do {
        chrUserInput = getche();
        //Letras Minúsculas + espaço +  Letras Maiusculas
        if ((chrUserInput > 96 && chrUserInput < 123) ||(chrUserInput > 64 && chrUserInput < 91) || (chrUserInput == 32)) {
            chrUserData[intStringPosition] = chrUserInput;
            chrUserData[intStringPosition+1] = 0;
            intStringPosition++;
        }
            //Letras portuguesas minusculas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();
            if((chrUserInput > 223 && chrUserInput < 255) || (chrUserInput > 191 && chrUserInput < 222)){
                chrUserData[intStringPosition] = chrUserInput;
                chrUserData[intStringPosition+1] = '\0';
                intStringPosition++;
            }else{
                chrUserData[intStringPosition] = '\0';
                system(CLEAR);
                printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
                printf("Nome: ");
                printUnsCharString(20,p2array[intContactCounter].chrNome);
                printf("\nNumero de telemovel: ");
                printUnsCharString(10,p2array[intContactCounter].chrTelefone);
                printf("\nMorada: ");
                printUnsCharString(30,p2array[intContactCounter].chrMorada);
                printf("\nCódigo Postal: ");
                printUnsCharString(10,p2array[intContactCounter].chrCodPostal);
                printf("\nCidade: ");
                printUnsCharString(20,p2array[intContactCounter].chrCidade);
                printf("\nPaís: ");
                printUnsCharString(20,chrData);
            }

        }
            //Tecla de Enter
        else if(chrUserInput == 10){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            chrUserData[intStringPosition] = '\0';
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,p2array[intContactCounter].chrTelefone);
            printf("\nMorada: ");
            printUnsCharString(30,p2array[intContactCounter].chrMorada);
            printf("\nCódigo Postal: ");
            printUnsCharString(10,p2array[intContactCounter].chrCodPostal);
            printf("\nCidade: ");
            printUnsCharString(20,p2array[intContactCounter].chrCidade);
            printf("\nPaís: ");
            printUnsCharString(20,chrData);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tContato\n\t\t================================\n\n");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,p2array[intContactCounter].chrTelefone);
            printf("\nMorada: ");
            printUnsCharString(30,p2array[intContactCounter].chrMorada);
            printf("\nCódigo Postal: ");
            printUnsCharString(10,p2array[intContactCounter].chrCodPostal);
            printf("\nCidade: ");
            printUnsCharString(20,p2array[intContactCounter].chrCidade);
            printf("\nPaís: ");
            printUnsCharString(20,chrData);
        }
    } while (intStringPosition < intStringLength);

}




//----->Funções de consulta por atributos


void consultaNome(struct contato *p2array, int intContactCounter){
    int intFound = 0, intStringLength = 20, intStringPosition = 0,intCounter = 0;

    unsigned char chrSearched[20];

    fflush(stdin);

    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrSearched;

    clearArray(intStringLength,chrSearched);    //Limpa o array

    clsKeyboardBuffer();

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tPesquisa Nome\n\t\t================================\n\n");
    printf("Nome: ");
    printUnsCharString(20,chrSearched);

    //Entrada de dados
    do {
        chrUserInput = getche();
        //Letras Minúsculas + espaço +  Letras Maiusculas
        if ((chrUserInput > 96 && chrUserInput < 123) || (chrUserInput == 32) ||(chrUserInput > 64 && chrUserInput < 91)) {
            chrUserData[intStringPosition] = chrUserInput;
            chrUserData[intStringPosition+1] = 0;
            intStringPosition++;
        }
            //Letras portuguesas minusculas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();
            if((chrUserInput > 223 && chrUserInput < 255) || (chrUserInput > 191 && chrUserInput < 222)){
                chrUserData[intStringPosition] = chrUserInput;
                chrUserData[intStringPosition+1] = '\0';
                intStringPosition++;
            }else{
                chrUserData[intStringPosition] = '\0';
                system(CLEAR);
                printf("\n\t\t================================\n\t\t\tPesquisa Nome\n\t\t================================\n\n");
                printf("Nome: ");
                printUnsCharString(20,chrSearched);
            }

        }
            //Tecla de Enter
        else if(chrUserInput == 10){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            chrUserData[intStringPosition] = '\0';
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("Nome: ");
            printUnsCharString(20,chrSearched);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("Nome: ");
            printUnsCharString(20,chrSearched);
        }
    } while (intStringPosition < intStringLength);

    printf("\n\nDeseja pesquisar pelo nome: ");
    printUnsCharString(20,chrSearched);
    fflush(stdin);
    getche();

    system(CLEAR);

    printf("\n\n..::Resultado da pesquisa de: ");
    printUnsCharString(20,chrSearched);
    printf("\n===================================================\n");



    //Percorrer contatos na memória
    for(intCounter = 0; intCounter < intContactCounter; intCounter++){

        //Comparar se a pesquisa é igual
        if(memcmp(chrSearched, p2array[intCounter].chrNome, 20) == 0){

            printf("\n\n\t\tNome: \t\t");
            printUnsCharString(20, p2array[intCounter].chrNome);
            printf("\n\t\tTelefone: \t");
            printUnsCharString(10, p2array[intCounter].chrTelefone);
            printf("\n\t\tMorada: \t");
            printUnsCharString(30, p2array[intCounter].chrMorada);
            printf("\n\t\tCódigo Postal: \t");
            printUnsCharString(10, p2array[intCounter].chrCodPostal);
            printf("\n\t\tCidade: \t");
            printUnsCharString(20, p2array[intCounter].chrCidade);
            printf("\n\t\tPaís: \t\t");
            printUnsCharString(20, p2array[intCounter].chrPais);
            printf("\n");
            printf("\n===================================================\n");
            intFound++;


        }
    }

    if (intFound == 0){
        printf("\n..::Nenhuma correspondencia encontrada!");
    }

    else{
        printf("\n..::%d correspondencia(s) encontrada(s)!", intFound);

        if(intFound >= 2){
            printf("\n\n..::ATENÇÃO: Existem %d contatos com o mesmo nome!!", intFound);
            printf("\n..::Não deve criar contatos com exatamente os mesmos paramêtros");
        }

    }

    fflush(stdin);
    printf("\n\n Pressiona qq tecla para sair: ");
    getche();
}

void consultaTelefone(struct contato *p2array, int intContactCounter){
    int intFound = 0, intStringLength = 10, intStringPosition = 0,intCounter = 0;

    unsigned char chrSearched[10];

    fflush(stdin);

    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrSearched;

    clearArray(intStringLength,chrSearched);    //Limpa o array

    clsKeyboardBuffer();

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tPesquisa Telefone\n\t\t================================\n\n");
    printf("Telefone: ");
    printUnsCharString(10,chrSearched);

    //Entrada de dados
    do {
        chrUserInput = getche();

        //Numeros Inteiros
        if (chrUserInput > 47 && chrUserInput < 58) {
            chrUserData[intStringPosition] = chrUserInput;
            intStringPosition++;
        }
            //Letras portuguesas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();

            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa Telefone\n\t\t================================\n\n");
            printf("\nTelefone: ");
            printUnsCharString(10,chrSearched);

        }
            //Tecla de Enter
        else if(chrUserInput == 10 || chrUserInput == 13){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa Telefone\n\t\t================================\n\n");
            printf("\nTelefone: ");
            printUnsCharString(10,chrSearched);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa Telefone\n\t\t================================\n\n");
            printf("\nTelefone: ");
            printUnsCharString(10,chrSearched);
        }
    }while (intStringPosition < intStringLength);

    printf("\n\nDeseja pesquisar pelo Telefone: ");
    printUnsCharString(10,chrSearched);
    fflush(stdin);
    getche();

    system(CLEAR);

    printf("\n\n..::Resultado da pesquisa de: ");
    printUnsCharString(10,chrSearched);
    printf("\n===================================================\n");



    //Percorrer contatos na memória
    for(intCounter = 0; intCounter < intContactCounter; intCounter++){

        //Comparar se a pesquisa é igual
        if(memcmp(chrSearched, p2array[intCounter].chrTelefone, 10) == 0){

            printf("\n\n\t\tNome: \t\t");
            printUnsCharString(20, p2array[intCounter].chrNome);
            printf("\n\t\tTelefone: \t");
            printUnsCharString(10, p2array[intCounter].chrTelefone);
            printf("\n\t\tMorada: \t");
            printUnsCharString(30, p2array[intCounter].chrMorada);
            printf("\n\t\tCódigo Postal: \t");
            printUnsCharString(10, p2array[intCounter].chrCodPostal);
            printf("\n\t\tCidade: \t");
            printUnsCharString(20, p2array[intCounter].chrCidade);
            printf("\n\t\tPaís: \t\t");
            printUnsCharString(20, p2array[intCounter].chrPais);
            printf("\n");
            printf("\n===================================================\n");
            intFound++;


        }
    }

    if (intFound == 0){
        printf("\n..::Nenhuma correspondencia encontrada!");
    }

    else{
        printf("\n..::%d correspondencia(s) encontrada(s)!", intFound);

        if(intFound >= 2){
            printf("\n\n..::ATENÇÃO: Existem %d contatos com o mesmo Telefone!!", intFound);
            printf("\n..::Não deve criar contatos com exatamente os mesmos paramêtros");
        }

    }

    fflush(stdin);
    printf("\n\n Pressiona qq tecla para sair: ");
    getche();
}

void consultaMorada(struct contato *p2array, int intContactCounter){
    int intFound = 0, intStringLength = 30, intStringPosition = 0,intCounter = 0;

    unsigned char chrSearched[30];

    fflush(stdin);

    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrSearched;

    clearArray(intStringLength,chrSearched);    //Limpa o array

    clsKeyboardBuffer();

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tPesquisa Morada\n\t\t================================\n\n");
    printf("Morada: ");
    printUnsCharString(30,chrSearched);

    //Entrada de dados
    do {
        chrUserInput = getche();
        //Todos os caracteres
        if ((chrUserInput > 32 && chrUserInput < 127) || (chrUserInput == 32) ) {
            chrUserData[intStringPosition] = chrUserInput;
            chrUserData[intStringPosition+1] = '\0';
            intStringPosition++;
        }
            //Letras portuguesas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();
            if(chrUserInput > 191 && chrUserInput < 255){
                chrUserData[intStringPosition] = chrUserInput;
                chrUserData[intStringPosition+1] = '\0';
                intStringPosition++;
            }else{
                chrUserData[intStringPosition] = '\0';
                system(CLEAR);
                printf("\n\t\t================================\n\t\t\tPesquisa Morada\n\t\t================================\n\n");
                printf("\nMorada: ");
                printUnsCharString(30,chrSearched);
            }

        }
            //Tecla de Enter
        else if(chrUserInput == 10){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa Morada\n\t\t================================\n\n");
            printf("\nMorada: ");
            printUnsCharString(30,chrSearched);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa Morada\n\t\t================================\n\n");
            printf("\nMorada: ");
            printUnsCharString(30,chrSearched);
        }
    } while (intStringPosition < intStringLength);

    printf("\n\nDeseja pesquisar pela Morada: ");
    printUnsCharString(30,chrSearched);
    fflush(stdin);
    getche();

    system(CLEAR);

    printf("\n\n..::Resultado da pesquisa de: ");
    printUnsCharString(30,chrSearched);
    printf("\n===================================================\n");



    //Percorrer contatos na memória
    for(intCounter = 0; intCounter < intContactCounter; intCounter++){

        //Comparar se a pesquisa é igual
        if(memcmp(chrSearched, p2array[intCounter].chrMorada, 30) == 0){

            printf("\n\n\t\tNome: \t\t");
            printUnsCharString(20, p2array[intCounter].chrNome);
            printf("\n\t\tTelefone: \t");
            printUnsCharString(10, p2array[intCounter].chrTelefone);
            printf("\n\t\tMorada: \t");
            printUnsCharString(30, p2array[intCounter].chrMorada);
            printf("\n\t\tCódigo Postal: \t");
            printUnsCharString(10, p2array[intCounter].chrCodPostal);
            printf("\n\t\tCidade: \t");
            printUnsCharString(20, p2array[intCounter].chrCidade);
            printf("\n\t\tPaís: \t\t");
            printUnsCharString(20, p2array[intCounter].chrPais);
            printf("\n");
            printf("\n===================================================\n");
            intFound++;


        }
    }

    if (intFound == 0){
        printf("\n..::Nenhuma correspondencia encontrada!");
    }

    else{
        printf("\n..::%d correspondencia(s) encontrada(s)!", intFound);

    }

    fflush(stdin);
    printf("\n\n Pressiona qq tecla para sair: ");
    getche();
}

void consultaCodPostal(struct contato *p2array, int intContactCounter){
    int intFound = 0, intStringLength = 10, intStringPosition = 0,intCounter = 0;

    unsigned char chrSearched[10];

    fflush(stdin);

    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrSearched;

    clearArray(intStringLength,chrSearched);    //Limpa o array

    clsKeyboardBuffer();

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tPesquisa Código Postal\n\t\t================================\n\n");
    printf("Código Postal: ");
    printUnsCharString(10,chrSearched);

    //Entrada de dados
    do {
        chrUserInput = getche();

        //Numeros Inteiros
        if ((chrUserInput > 47 && chrUserInput < 58) || (chrUserInput == 45)) {
            chrUserData[intStringPosition] = chrUserInput;
            intStringPosition++;
        }
            //Letras portuguesas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();

            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa Código Postal\n\t\t================================\n\n");
            printf("\nCódigo Postal: ");
            printUnsCharString(10,chrSearched);

        }
            //Tecla de Enter
        else if(chrUserInput == 10 || chrUserInput == 13){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa Código Postal\n\t\t================================\n\n");
            printf("\nCódigo Postal: ");
            printUnsCharString(10,chrSearched);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa Código Postal\n\t\t================================\n\n");
            printf("\nCódigo Postal: ");
            printUnsCharString(10,chrSearched);
        }
    }while (intStringPosition < intStringLength);

    printf("\n\nDeseja pesquisar pelo Código Postal: ");
    printUnsCharString(10,chrSearched);
    fflush(stdin);
    getche();

    system(CLEAR);

    printf("\n\n..::Resultado da pesquisa de: ");
    printUnsCharString(10,chrSearched);
    printf("\n===================================================\n");



    //Percorrer contatos na memória
    for(intCounter = 0; intCounter < intContactCounter; intCounter++){

        //Comparar se a pesquisa é igual
        if(memcmp(chrSearched, p2array[intCounter].chrCodPostal, 10) == 0){

            printf("\n\n\t\tNome: \t\t");
            printUnsCharString(20, p2array[intCounter].chrNome);
            printf("\n\t\tTelefone: \t");
            printUnsCharString(10, p2array[intCounter].chrTelefone);
            printf("\n\t\tMorada: \t");
            printUnsCharString(30, p2array[intCounter].chrMorada);
            printf("\n\t\tCódigo Postal: \t");
            printUnsCharString(10, p2array[intCounter].chrCodPostal);
            printf("\n\t\tCidade: \t");
            printUnsCharString(20, p2array[intCounter].chrCidade);
            printf("\n\t\tPaís: \t\t");
            printUnsCharString(20, p2array[intCounter].chrPais);
            printf("\n");
            printf("\n===================================================\n");
            intFound++;


        }
    }

    if (intFound == 0){
        printf("\n..::Nenhuma correspondencia encontrada!");
    }

    else{
        printf("\n..::%d correspondencia(s) encontrada(s)!", intFound);

    }

    fflush(stdin);
    printf("\n\n Pressiona qq tecla para sair: ");
    getche();
}

void consultaCidade(struct contato *p2array, int intContactCounter){
    int intFound = 0, intStringLength = 20, intStringPosition = 0,intCounter = 0;

    unsigned char chrSearched[20];

    fflush(stdin);

    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrSearched;

    clearArray(intStringLength,chrSearched);    //Limpa o array

    clsKeyboardBuffer();

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tPesquisa Cidade\n\t\t================================\n\n");
    printf("Cidade: ");
    printUnsCharString(20,chrSearched);

    //Entrada de dados
    do {
        chrUserInput = getche();
        //Letras Minúsculas + espaço +  Letras Maiusculas
        if ((chrUserInput > 96 && chrUserInput < 123) || (chrUserInput == 32) ||(chrUserInput > 64 && chrUserInput < 91)) {
            chrUserData[intStringPosition] = chrUserInput;
            chrUserData[intStringPosition+1] = 0;
            intStringPosition++;
        }
            //Letras portuguesas minusculas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();
            if((chrUserInput > 223 && chrUserInput < 255) || (chrUserInput > 191 && chrUserInput < 222)){
                chrUserData[intStringPosition] = chrUserInput;
                chrUserData[intStringPosition+1] = '\0';
                intStringPosition++;
            }else{
                chrUserData[intStringPosition] = '\0';
                system(CLEAR);
                printf("\n\t\t================================\n\t\t\tPesquisa Cidade\n\t\t================================\n\n");
                printf("Cidade: ");
                printUnsCharString(20,chrSearched);
            }

        }
            //Tecla de Enter
        else if(chrUserInput == 10){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            chrUserData[intStringPosition] = '\0';
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa Cidade\n\t\t================================\n\n");
            printf("Cidade: ");
            printUnsCharString(20,chrSearched);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa Cidade\n\t\t================================\n\n");
            printf("Cidade: ");
            printUnsCharString(20,chrSearched);
        }
    } while (intStringPosition < intStringLength);

    printf("\n\nDeseja pesquisar pela Cidade: ");
    printUnsCharString(20,chrSearched);
    fflush(stdin);
    getche();

    system(CLEAR);

    printf("\n\n..::Resultado da pesquisa de: ");
    printUnsCharString(20,chrSearched);
    printf("\n===================================================\n");



    //Percorrer contatos na memória
    for(intCounter = 0; intCounter < intContactCounter; intCounter++){

        //Comparar se a pesquisa é igual
        if(memcmp(chrSearched, p2array[intCounter].chrCidade, 20) == 0){

            printf("\n\n\t\tNome: \t\t");
            printUnsCharString(20, p2array[intCounter].chrNome);
            printf("\n\t\tTelefone: \t");
            printUnsCharString(10, p2array[intCounter].chrTelefone);
            printf("\n\t\tMorada: \t");
            printUnsCharString(30, p2array[intCounter].chrMorada);
            printf("\n\t\tCódigo Postal: \t");
            printUnsCharString(10, p2array[intCounter].chrCodPostal);
            printf("\n\t\tCidade: \t");
            printUnsCharString(20, p2array[intCounter].chrCidade);
            printf("\n\t\tPaís: \t\t");
            printUnsCharString(20, p2array[intCounter].chrPais);
            printf("\n");
            printf("\n===================================================\n");
            intFound++;


        }
    }

    if (intFound == 0){
        printf("\n..::Nenhuma correspondencia encontrada!");
    }

    else{
        printf("\n..::%d correspondencia(s) encontrada(s)!", intFound);

    }

    fflush(stdin);
    printf("\n\n Pressiona qq tecla para sair: ");
    getche();
}

void consultaPais(struct contato *p2array, int intContactCounter){
    int intFound = 0, intStringLength = 20, intStringPosition = 0,intCounter = 0;

    unsigned char chrSearched[20];

    fflush(stdin);

    unsigned char chrUserInput = 0;
    unsigned char *chrUserData = chrSearched;

    clearArray(intStringLength,chrSearched);    //Limpa o array

    clsKeyboardBuffer();

    system(CLEAR);
    printf("\n\t\t================================\n\t\t\tPesquisa País\n\t\t================================\n\n");
    printf("País: ");
    printUnsCharString(20,chrSearched);

    //Entrada de dados
    do {
        chrUserInput = getche();
        //Letras Minúsculas + espaço +  Letras Maiusculas
        if ((chrUserInput > 96 && chrUserInput < 123) || (chrUserInput == 32) ||(chrUserInput > 64 && chrUserInput < 91)) {
            chrUserData[intStringPosition] = chrUserInput;
            chrUserData[intStringPosition+1] = 0;
            intStringPosition++;
        }
            //Letras portuguesas minusculas linux
        else if(chrUserInput == 195){
            chrUserInput = linuxPTchar();
            if((chrUserInput > 223 && chrUserInput < 255) || (chrUserInput > 191 && chrUserInput < 222)){
                chrUserData[intStringPosition] = chrUserInput;
                chrUserData[intStringPosition+1] = '\0';
                intStringPosition++;
            }else{
                chrUserData[intStringPosition] = '\0';
                system(CLEAR);
                printf("\n\t\t================================\n\t\t\tPesquisa País\n\t\t================================\n\n");
                printf("País: ");
                printUnsCharString(20,chrSearched);
            }

        }
            //Tecla de Enter
        else if(chrUserInput == 10){
            intStringPosition = intStringLength+1;
        }
            //Tecla de BackSpace
        else if(chrUserInput == 127){
            chrUserData[intStringPosition] = '\0';
            intStringPosition--;
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa País\n\t\t================================\n\n");
            printf("País: ");
            printUnsCharString(20,chrSearched);
        }else{
            chrUserData[intStringPosition] = '\0';
            system(CLEAR);
            printf("\n\t\t================================\n\t\t\tPesquisa País\n\t\t================================\n\n");
            printf("País: ");
            printUnsCharString(20,chrSearched);
        }
    } while (intStringPosition < intStringLength);

    printf("\n\nDeseja pesquisar pelo País: ");
    printUnsCharString(20,chrSearched);
    fflush(stdin);
    getche();

    system(CLEAR);

    printf("\n\n..::Resultado da pesquisa de: ");
    printUnsCharString(20,chrSearched);
    printf("\n===================================================\n");



    //Percorrer contatos na memória
    for(intCounter = 0; intCounter < intContactCounter; intCounter++){

        //Comparar se a pesquisa é igual
        if(memcmp(chrSearched, p2array[intCounter].chrPais, 20) == 0){

            printf("\n\n\t\tNome: \t\t");
            printUnsCharString(20, p2array[intCounter].chrNome);
            printf("\n\t\tTelefone: \t");
            printUnsCharString(10, p2array[intCounter].chrTelefone);
            printf("\n\t\tMorada: \t");
            printUnsCharString(30, p2array[intCounter].chrMorada);
            printf("\n\t\tCódigo Postal: \t");
            printUnsCharString(10, p2array[intCounter].chrCodPostal);
            printf("\n\t\tCidade: \t");
            printUnsCharString(20, p2array[intCounter].chrCidade);
            printf("\n\t\tPaís: \t\t");
            printUnsCharString(20, p2array[intCounter].chrPais);
            printf("\n");
            printf("\n===================================================\n");
            intFound++;


        }
    }

    if (intFound == 0){
        printf("\n..::Nenhuma correspondencia encontrada!");
    }

    else{
        printf("\n..::%d correspondencia(s) encontrada(s)!", intFound);

    }

    fflush(stdin);
    printf("\n\n Pressiona qq tecla para sair: ");
    getche();
}


