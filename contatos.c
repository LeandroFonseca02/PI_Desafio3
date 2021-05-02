#include "contatos.h"


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







//----->Funçoes de manipulação de contatos



//Cria um novo contato na memória
struct contato *criarContato(struct contato *p2array, int intContactCounter){

    //Limpar terminal
    system("clear");

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
        system("clear");

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
        system("clear");

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

    system("clear");

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

//void consultaAtributos(){
//
//    int intFound = 0, intLength = 20, intCounter = 0, intChoice = 0;
//    FILE *fp;
//
//    unsigned char chrSearched[20], chrFinded[20];
//
////    system("clear");
//    clearArray(20,chrSearched);
//    clearArray(20, chrFinded);
//
//    intFound = 0;
//
//    printOption4Menu();
//    fflush(stdin);
//
//    scanf("%d", &intChoice);
//    fflush(stdin);
//
//    switch (intChoice) {
//        case 1:
//            consultaNome();
//            break;
//        case 2:
//            break;
//        case 3:
//            break;
//        case 4:
//            break;
//        case 5:
//            break;
//        case 6:
//            break;
//        default:
//            break;
//    }
//
//    fp = fopen("leandro.dat", "r");
//
//    system("clear");
//
//    printf("\n\n..::Resultado da pesquisa de: ");
//    printUnsCharString(20,chrSearched);
//    printf("\n===================================================\n");
//
//    while (fread(&lista, sizeof(lista), 1, fp) == 1) {
//
//        clearArray(20, chrFinded);
//
//        for (intCounter = 0; intCounter <= intLength; intCounter++){
//            if(chrSearched[intCounter] != '\0'){
//                chrFinded[intCounter] = lista.chrNome[intCounter];
//            }else{
//                intCounter = intLength + 1;
//            }
//        }
//
//        chrFinded[intLength] = '\0';
//
//        if (memcmp(chrSearched, chrFinded, 20) == 0) {
//
//            printf("\n\nNome\t: ");
//            printUnsCharString(20,lista.chrNome);
//            printf("\nNumero de Telefone\t: ");
//            printUnsCharString(10,lista.chrTelefone);
//            printf("\nMorada\t: ");
//            printUnsCharString(30,lista.chrMorada);
//            printf("\nCodigo Postal\t: ");
//            printUnsCharString(10,lista.chrCodPostal);
//            printf("\nCidade\t: ");
//            printUnsCharString(20,lista.chrCidade);
//            printf("\nPaís\t: ");
//            printUnsCharString(20,lista.chrPais);
//            printf("\n");
//            intFound++;
//        }
//
//    }
//
//    if (intFound == 0){
//        printf("\n..::Nenhuma correspondencia encontrada!");
//    }
//
//    else{
//        printf("\n..::%d correspondencia(s) encontrada(s)!", intFound);
//    }
//
//    clsKeyboardBuffer();
//    getche();
//
//    fclose(fp);
//}
//
//void modificarContato(){
//
//    FILE *fp, *ft;
//    unsigned char chrToSearch[30];
//
//    system("clear");
//
//    fp=fopen("leandro.dat","r");
//
//    ft=fopen("temp.dat","w");
//
//    fflush(stdin);
//
//    printf("..::Edit contact\n===============================\n\n\t..::Enter the name of contact to edit:");
//
//    scanf("%s",chrToSearch);
//
//    while(fread(&lista,sizeof(lista),1,fp)==1)
//
//    {
//        if(memcmp(chrToSearch, lista.chrNome, 20) == 0){
//            fwrite(&lista,sizeof(lista),1,ft);
//        }
//    }
//
//    fflush(stdin);
//
//    printf("\n\n..::Editing '%s'\n\n",chrToSearch);
//
//    printf("..::Nome(Use identical):");
//
//    scanf("%s",lista.chrNome);
//
//    fflush(stdin);
//
//    printf("..::Número de telefone:");
//
//    scanf("%s",lista.chrTelefone);
//
//    fflush(stdin);
//
//    printf("..::Morada:");
//
//    scanf("%s",lista.chrMorada);
//
//    fflush(stdin);
//
//    printf("..::Código Postal:");
//
//    scanf("%s",lista.chrCodPostal);
//
//    fflush(stdin);
//
//    printf("..::Cidade:");
//
//    scanf("%s",lista.chrCidade);
//
//    fflush(stdin);
//
//    printf("..::País:");
//
//    scanf("%s",lista.chrPais);
//
//    printf("\n");
//
//    fwrite(&lista,sizeof(lista),1,ft);
//
//    fclose(fp);
//
//    fclose(ft);
//
//    remove("leandro.dat");
//
//    rename("temp.dat","leandro.dat");
//}
//
//void removerContato(){
//
//    FILE *fp, *ft;
//    unsigned char chrToSearch[30];
//
//    system("clear");
//
//    fflush(stdin);
//
//    printf("\n\n\t..::DELETE A CONTACT\n\t==========================\n\t..::Enter the name of contact to delete:");
//
//    scanf("%s",chrToSearch);
//
//    fp=fopen("leandro.dat","r");
//
//    ft=fopen("temp.dat","w");
//
//    while(fread(&lista,sizeof(lista),1,fp)!=0)
//
//        if (strcmp(chrToSearch,lista.chrNome)!=0){
//            fwrite(&lista,sizeof(lista),1,ft);
//        }
//
//
//
//    fclose(fp);
//
//    fclose(ft);
//
//    remove("leandro.dat");
//
//    rename("temp.dat","leandro.dat");
//
//}

//Apaga ficheiro de contatos e contatos da memória (retorna NULL)
struct contato *apagarFileContatos(struct contato *p2array){
    int intChoice = 0;
    FILE *fp;


    system("clear");
    printf("AVISO! Ao eliminar o ficheiro que contém os contatos, perderá permanentemente os seus contatos!\n");
    printf("================================================================================================================\n\n");
    printf("Deseja eliminar o ficheiro de contatos?\n");
    printf("\t\t[1] Sim\n");
    printf("\t\t[2] Não\n\n");
    printf("Digite a opção que deseja selecionar: ");
    scanf("%d", &intChoice);
    fflush(stdin);

    //Verificar opção do user
    if(intChoice != 1){
        printf("\n\nFicheiro de contatos mantém-se intacto!");
        printf("\n..::Pressione qualquer tecla para continuar");
        clsKeyboardBuffer();    //Limpar buffer
        getche();
    }else{
        system("clear");
        printf("AVISO! Ao eliminar o ficheiro que contém os contatos, perderá permanentemente os seus contatos!\n");
        printf("================================================================================================================\n\n");
        printf("Tem a certeza que deseja eliminar o ficheiro de contatos?\n");
        printf("\t\t[1] Não\n");
        printf("\t\t[2] Sim\n\n");
        printf("Digite a opção que deseja selecionar: ");
        scanf("%d", &intChoice);
        fflush(stdin);

        //Verificar se o user deseja eliminar contatos
        if(intChoice == 2){
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
    system("clear");
    printf("teste");
    getche();
}





//Funções de validação de dados

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

    system("clear");
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
                system("clear");
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
            system("clear");
            printf("Nome: ");
            printUnsCharString(20,chrData);
        }else{
            chrUserData[intStringPosition] = '\0';
            system("clear");
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

    system("clear");
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
            system("clear");
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
            system("clear");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,chrData);
        }else{
            chrUserData[intStringPosition] = '\0';
            system("clear");
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

    system("clear");
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
                system("clear");
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
            system("clear");
            printf("Nome: ");
            printUnsCharString(20,p2array[intContactCounter].chrNome);
            printf("\nNumero de telemovel: ");
            printUnsCharString(10,p2array[intContactCounter].chrTelefone);
            printf("\nMorada: ");
            printUnsCharString(30,chrData);
        }else{
            chrUserData[intStringPosition] = '\0';
            system("clear");
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

    system("clear");
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
            system("clear");
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
            system("clear");
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
            system("clear");
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

    system("clear");
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
                system("clear");
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
            system("clear");
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
            system("clear");
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

    system("clear");
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
                system("clear");
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
            system("clear");
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
            system("clear");
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






//Funçoes de manipulação de contatos

//void consultaNome(){
//    int intFound = 0, intLength = 20, intCounter = 0;
//    FILE *fp;
//
//    unsigned char chrSearched[20], chrFinded[20];
//
//    fflush(stdin);
//    nomeContato(intLength,chrSearched);
//
//    fp = fopen("leandro.dat", "r");
//
//    system("clear");
//
//    printf("\n\n..::Resultado da pesquisa de: ");
//    printUnsCharString(20,chrSearched);
//    printf("\n===================================================\n");
//
//    while (fread(&lista, sizeof(lista), 1, fp) == 1) {
//
//        clearArray(20, chrFinded);
//
//        for (intCounter = 0; intCounter <= intLength; intCounter++){
//            if(chrSearched[intCounter] != '\0'){
//                chrFinded[intCounter] = lista.chrNome[intCounter];
//            }else{
//                intCounter = intLength + 1;
//            }
//        }
//
//        chrFinded[intLength] = '\0';
//
//        if (memcmp(chrSearched, chrFinded, 20) == 0) {
//
//            printf("\n\nNome\t: ");
//            printUnsCharString(20,lista.chrNome);
//            printf("\nNumero de Telefone\t: ");
//            printUnsCharString(10,lista.chrTelefone);
//            printf("\nMorada\t: ");
//            printUnsCharString(30,lista.chrMorada);
//            printf("\nCodigo Postal\t: ");
//            printUnsCharString(10,lista.chrCodPostal);
//            printf("\nCidade\t: ");
//            printUnsCharString(20,lista.chrCidade);
//            printf("\nPaís\t: ");
//            printUnsCharString(20,lista.chrPais);
//            printf("\n");
//            intFound++;
//        }
//
//    }
//
//    if (intFound == 0){
//        printf("\n..::Nenhuma correspondencia encontrada!");
//    }
//
//    else{
//        printf("\n..::%d correspondencia(s) encontrada(s)!", intFound);
//    }
//
//    clsKeyboardBuffer();
//    getche();
//
//    fclose(fp);
//}