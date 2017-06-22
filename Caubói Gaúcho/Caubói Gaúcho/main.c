//
//  main.c
//  Caubói Gaúcho
//
//  Copyright © 2017 Caubói Gaúcho. All rights reserved.
//


//bibliotecas

#include <stdio.h>
#include <string.h>


//Constantes

#define Tamanho 200
#define MaxTerminais 30

#define Tamanho2 70
#define MaxVariaveis 50

#define NVarRegra 10
#define MaxRegras 60

#define arquivo "gramatica2.txt"

#define Tamanho_Entrada 1000
#define N_Terminais_Entrada 100

#define MaxN 20


//variaveis

int NVariaveis = 0;
int NTerminais = 0;
int NRegras = 0;
int NTerminaisIN = 0;


//estruturas

struct REGRA
{
    int marcador;           // Posição do marcador utilizado pelo parser
    int variavel;           //posição no array variaveis da variavel da esquerda
    int nTermos;           //numero de termos a direita
    int proxVar[NVarRegra][2];  //termos a direita. primeiro [] diz qual termo do array olhar. segundo [] diz se é pra olhar no vetor de variaveis ou terminais
    float peso;
    int ID;                 // Número de identificação para fácil diferenciação entre regras
    int n;                  // Número que indica em qual Dn foi gerado
};






// Lê o do arquivo de texto e guarda os terminais e variáveis em suas respectivas matrizes. Também guarda a variável inicial
void le_gramatica(char terminais[MaxTerminais][Tamanho], char variaveis[MaxVariaveis][Tamanho2], int *inicial, struct REGRA regras[MaxRegras])
{
    FILE* f;

    int i = 0;
    int j = 0;
    int k = 0;
    char var[Tamanho2], var2[Tamanho2];
    char c;

    f = fopen(arquivo, "r");
    if (f == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    else
    {
        printf("\nArquivo carregado com sucesso\n\n");

        if((c = fgetc(f)) != '<')  // Verifica primeira linha
        {
            printf("\nErro de sintaxe! Linha 1\n");
            exit(0);
        }

        while((c = fgetc(f)) != 13) // Vai para a próxima linha
        {
            ;
        }

        // Percorre todos os terminais
        while((c = fgetc(f)) == '[')
        {
            if((c=fgetc(f))!= ' ') // Pula primeiro espaço  -> [ terminal ]
            {
                printf("\nErro de sintaxe! Espaco faltando\n");
                exit(0);
            }

            // Pega a palavra até o próximo ']' (terminal)
            while((c = fgetc(f)) != ']' && c != 127)
            {
                terminais[i][j] = c;
                j++;
                //                printf("%c", c);
            }
            terminais[i][j-1] = '\0';   // Elimina o espaço que foi colocado ao fim do terminal
            NTerminais++;
            j = 0;
            i++;
            while((c = fgetc(f)) != 13) // Vai para a próxima linha
            {
                ;
            }
        }
        j = 0;
        i = 0;

        if(c != 'V')  // Verifica linha Variaveis
        {
            printf("\n%c\nErro de sintaxe! \"Variaveis\" faltando\n",c);
            exit(0);
        }

        while((c = fgetc(f)) != 13) // Vai para a próxima linha
        {
            ;
        }

        //        printf("\n");

        // Percorre todas as variáveis
        while((c = fgetc(f)) == '[')
        {
            if((c=fgetc(f))!= ' ') // Pula primeiro espaço  -> [ terminal ]
            {
                printf("\nErro de sintaxe! Espaco faltando\n");
                exit(0);
            }

            // Pega a palavra até o próximo ']' (variável)
            while((c = fgetc(f)) != ']' && c != 127)
            {
                variaveis[i][j] = c;
                j++;
                //                printf("%c", c);
            }
            variaveis[i][j-1] = '\0';   // Elimina o espaço que foi colocado ao fim da variável
            NVariaveis++;
            j = 0;
            i++;
            while((c = fgetc(f)) != 13) // Vai para a próxima linha
            {
                ;
            }
        }

        if(c != 'I')  // Verifica linha Variaveis
        {
            printf("\n%c\nErro de sintaxe! \"Inicial\" faltando\n",c);
            exit(0);
        }

        while((c = fgetc(f)) != 13) // Vai para a próxima linha
        {
            ;
        }

        // Variável inicial
        if((c = fgetc(f)) != '[')  // Verifica '[' na linha da variável inicial
        {
            printf("\n%c\nErro de sintaxe! \'[\' faltando\n",c);
            exit(0);
        }
        if((c = fgetc(f)) != ' ')  // Verifica ' ' na linha da variável inicial
        {
            printf("\n%c\nErro de sintaxe! \' \' faltando\n",c);
            exit(0);
        }
        i = 0;
        while((c = fgetc(f)) != ']' && c != 127)
        {
            var[i] = c;
            i++;
            //            printf("%c", c);
        }
        if(var[i-1] == ' ')
            var[i-1] = '\0';  // Elimina o espaço que foi colocado ao fim da variável

        //testa se var é igual a uma variavel. se sim, atribui a posição ao simbolo inicial
        int inicialEvariavel = 0;
        for(i=0; i<MaxVariaveis; i++)
        {
            if(!strcmp(var, variaveis[i]))
            {
                *inicial = i;
                inicialEvariavel = 1;
            }
        }
        if(!inicialEvariavel)   // Se a variável inicial não estiver na matriz de variáveis, retorna erro
        {
            printf("\nErro! Variavel inicial nao foi declarada como variavel.\n",c);
            exit(0);
        }

        j=0;

        //Regras(sob construção)

        while((c = fgetc(f)) != 13) // Vai para a próxima linha
        {
            ;
        }
        while((c = fgetc(f)) != 13) // Vai para a próxima linha
        {
            ;
        }
        i = 0;

        strcpy(var2, "");

        while((c = fgetc(f)) == '[')
        {
            if((c=fgetc(f))!= ' ') // Pula primeiro espaço  -> [ variável ]
            {
                printf("\nErro de sintaxe! Espaco faltando\n");
                exit(0);
            }

            // Pega a palavra até o próximo ']' (parte esquerda da regra)
            while((c = fgetc(f)) != ']' && c != 127)
            {
                var2[i] = c;
                i++;
            }
            if(var2[i-1] == ' ')
                var2[i-1] = '\0';   // Elimina o espaço que foi colocado ao fim do terminal

            // Encontra a posição da variável da regra na matriz de variáveis
            int varExiste = 0;
            for(i=0; i<MaxVariaveis; i++)
            {
                //strcpy(var, variaveis[i]);
                if(!strcmp(var2, variaveis[i]))
                {
                    regras[j].variavel = i;
                    varExiste = 1;
                }
            }
            if(!varExiste)    // Se a variável da regra não existe, retorna erro
            {
                printf("\nErro! A variavel \"");
                int k = 0;
                for(;k<strlen(var2);k++)
                {
                    if(var2[k]!='\0')
                        printf("%c",var2[k]);
                }
                printf("\" foi declarada nas regras mas nao nas variaveis.\n");
                exit(0);
            }

            //carrega variaveis
            while((c = fgetc(f)) != ';')
            {
                if(c == '[')    // Parte direita da regra encontrada
                {
                    i=0;
                    if((c=fgetc(f))!= ' ') // Pula primeiro espaço  -> [ ? ]
                    {
                        printf("\nErro de sintaxe! Espaco faltando\n");
                        exit(0);
                    }

                    // Pega a palavra até o próximo ']' (parte direita da regra)
                    while((c = fgetc(f)) != ']' && c != 127)
                    {
                        var2[i] = c;
                        i++;
                    }
                    if(var2[i-1] == ' ')
                        var2[i-1] = '\0';

                    // Procura parte direita na lista de variáveis
                    int varExiste = 0;
                    int terExiste = 0;
                    for(i=0; i<MaxVariaveis; i++)
                    {
                       // strcpy(var, variaveis[i]);
                        if(strcmp(var2, variaveis[i]) == 0)
                        {
                            regras[j].proxVar[k][0] = i;
                            regras[j].proxVar[k][1] = 1;
                            regras[j].nTermos++;
                            varExiste = 1;
                        }
                    }

                    // Procura parte direita na lista de terminais
                    for(i=0; i<MaxTerminais; i++)
                    {
                       // strcpy(var, terminais[i]);
                        if(strcmp(var2, terminais[i]) == 0)
                        {
                            regras[j].proxVar[k][0] = i;
                            regras[j].proxVar[k][1] = 2;
                            regras[j].nTermos++;
                            terExiste = 1;
                        }
                    }

                    if(terExiste && varExiste)  // Se encontrou a var2 na lista de terminais E na de variáveis
                    {
                        printf("\nErro! \"");
                        int k = 0;
                        for(;k<strlen(var2);k++)
                        {
                            if(var2[k]!='\0')
                                printf("%c",var2[k]);
                        }
                        printf("\" declarado como variavel e terminal.\n");
                        exit(0);
                    }
                    else if(!terExiste && !varExiste)   // Se não encontrou var2 na lista de variáveis OU na de terminais
                    {
                        printf("\nErro! \"");
                        int k = 0;
                        for(;k<strlen(var2);k++)
                        {
                            if(var2[k]!='\0')
                                printf("%c",var2[k]);
                        }
                        printf("\" foi declarado somente nas regras.\n");
                        exit(0);
                    }

                    for(i=0;i<Tamanho2;i++)
                    {
                        var2[i] = 0;
                    }
                    i=0;
                    k++;
                }
            }

            //pega peso
            c = fgetc(f);
            if(c == '\t')
                c = fgetc(f);
            regras[j].peso += (c - 48);
            c = fgetc(f);
            if(c == '.')
            {
                c = fgetc(f);
                regras[j].peso += (c - 48)*0.1;
                c = fgetc(f);
                if(c != ' ' && c != '\t' && c != '\r' && c != 10 && c != 13)
                    regras[j].peso += (c - 48)*0.01;
            }

            regras[j].ID = NRegras;

            NRegras ++;



            while((c = fgetc(f)) != 13) // Vai para a próxima linha
            {
                ;
            }
            j++;
            i = 0;
            k=0;
        }


        return;
    }
}

// Imprime todos os terminais na matriz de terminais
void imprime_terminais(char Terminais[MaxTerminais][Tamanho])
{
    int i=0;
    int j=0;
    if(Terminais[i][j] != '\0')
    {
        printf("\n-----------------------------");
        printf("\nTerminais");
        printf("\n-----------------------------\n");
        for(i = 0; i< MaxTerminais; i++)
        {
            for(j = 0; j<Tamanho; j++)
            {
                if(Terminais[i][j] != '\0')
                    printf("%c", Terminais[i][j]);
            }
            if(Terminais[i][j] != '\0')
                printf("\n");
        }
        printf("-----------------------------\n\n");
    }
    else
        printf("\nNao ha terminais.\n");
}

//Imprime todas as variáveis na matriz de variáveis
void imprime_variaveis(char Variaveis[MaxVariaveis][Tamanho2], int inicial)
{
    int i=0;
    int j=0;
    if(Variaveis[i][j] != '\0')
    {
        printf("\n-----------------------------");
        printf("\nVariaveis");
        printf("\n-----------------------------\n");
        printf("Variavel Inicial: \n");
        for(i=0; i<Tamanho2; i++)
        {
            printf("%c", Variaveis[inicial][i]);
        }
        printf("\n\nRestante:\n");
        for(i = 0; i< MaxVariaveis; i++)
        {
            for(j = 0; j<Tamanho2; j++)
            {
                if(Variaveis[i][j] != '\0')
                    printf("%c", Variaveis[i][j]);
            }
            if(Variaveis[i][j] != '\0')
                printf("\n");
        }
        printf("-----------------------------\n\n");
    }
    else
        printf("\nNao ha variaveis.\n");
}

//Imprime todas as regras na matriz de regras
void imprime_regras(char terminais[MaxTerminais][Tamanho], char variaveis[MaxVariaveis][Tamanho2], struct REGRA regras[MaxRegras])
{
    int i=0;
    int j=0;
    if(regras[0].proxVar[0][0] != -1)
    {
        printf("\n-----------------------------");
        printf("\nRegras");
        printf("\n-----------------------------\n");
        for(i = 0; i< NRegras; i++)
        {
            int marcadorColocado = 0;
            if(regras[i].proxVar[0][1] != -1)
            {
                printf("[ ");
                int k = 0;
                // Imprime lado esquerdo da regra
                for(;k<strlen(variaveis[regras[i].variavel]);k++)
                {
                    if(variaveis[regras[i].variavel][k]!='\0')
                        printf("%c",variaveis[regras[i].variavel][k]);
                }
                printf(" ] ->");

                // Imprime lado direito da regra
                for(j=0; j<regras[i].nTermos; j++)
                {
                    int k = 0;
                    if(regras[i].marcador == j)
                    {
                        printf(" *[");
                        marcadorColocado = 1;
                    }
                    else
                        printf(" [ ");
                    //printf("\n\n\n_%c_\n\n\n", );
                    if(regras[i].proxVar[j][1]==1)
                    {
                        for(;k<Tamanho2;k++)
                        {
                            if(variaveis[regras[i].proxVar[j][0]][k]!='\0')
                                printf("%c",variaveis[regras[i].proxVar[j][0]][k]);
                        }
                    }
                    else if(regras[i].proxVar[j][1]==2)
                    {
                        for(;k<Tamanho;k++)
                        {
                            if(terminais[regras[i].proxVar[j][0]][k]!='\0')
                                printf("%c",terminais[regras[i].proxVar[j][0]][k]);
                        }
                    }
                    printf(" ]");
                }

                if(!marcadorColocado)
                    printf(" *");

                // Imprime n
                printf(" /%i", regras[i].n);

                // Imprime peso da regra
                printf(" ;%.2f", regras[i].peso);

                // Imprime ID
                //printf("  ID: %i", regras[i].ID);
                printf("\n");
            }

        }
        printf("-----------------------------\n\n");
    }
    else
        printf("\nNao ha regras.\n");
}

// Inicializa as matrizes de terminais e de variáveis com o caractere '\0'
void inicializa_matrizes(char terminais[MaxTerminais][Tamanho], char variaveis[MaxVariaveis][Tamanho2], struct REGRA regras[MaxRegras], struct REGRA D0[MaxRegras], struct REGRA Dn[MaxN][MaxRegras])
{
    int i, j, k = 0;

    for(i = 0; i< MaxTerminais; i++)
    {
        for(j = 0; j<Tamanho; j++)
        {
            terminais[i][j] = '\0';
        }
    }
    for(i = 0; i< MaxVariaveis; i++)
    {
        for(j = 0; j<Tamanho2; j++)
        {
            variaveis[i][j] = '\0';
        }
    }
    for(i = 0; i< MaxRegras; i++)
    {
        regras[i].marcador = 0;
        regras[i].variavel = -1;
        regras[i].nTermos = 0;
        regras[i].peso = 0;
        regras[i].ID = -1;
        regras[i].n = -1;
        //D0
        D0[i].marcador = 0;
        D0[i].variavel = -1;
        D0[i].nTermos = 0;
        D0[i].peso = 0;
        D0[i].ID = -1;
        D0[i].n = -1;
        for(j=0; j<NVarRegra; j++)
        {
            regras[i].proxVar[j][0] = -1;
            regras[i].proxVar[j][1] = -1;
            //D0
            D0[i].proxVar[j][0] = -1;
            D0[i].proxVar[j][1] = -1;
        }
    }
    //Dn
    for(i=0; i<MaxN; i++)
    {
        for(j=0; j<MaxRegras; j++)
        {
            Dn[i][j].marcador = 0;
            Dn[i][j].variavel = -1;
            Dn[i][j].nTermos = 0;
            Dn[i][j].peso = 0;
            Dn[i][j].ID = -1;
            Dn[i][j].n = -1;
            for(k=0; k<NVarRegra; k++)
            {
                Dn[i][j].proxVar[k][0] = -1;
                Dn[i][j].proxVar[k][1] = -1;
            }
        }
    }

    printf("\nMatrizes inicializadas\n");
}


// Função que gera Dn
int gera_Dn(struct REGRA regras[MaxRegras], int terminais_entrada[], char lista_terminais[MaxTerminais][Tamanho], struct REGRA Dn[MaxN][MaxRegras])
{
    int n=1;
    int i,j,k,l;
    k=0;    // Contadora da posição do vetor Dn[n]

    for(i=0; i<NTerminaisIN; i++)   // Percorre o array terminais_entrada
    {
        printf("\n----------------------------\nIniciando geracao de Dn[%i]", n);
        // Guarda em Dn todas as regras de Dn-1 cujo marcador aponta para a palavra sendo procurada
        for(j=0; j<MaxRegras; j++)  // Percorre todas as regras de Dn-1
        {
            if(terminais_entrada[i] == Dn[n-1][j].proxVar[Dn[n-1][j].marcador][0] && Dn[n-1][j].proxVar[Dn[n-1][j].marcador][1] == 2)    // Se a palavra da entrada estiver apontada pelo marcador de uma regra
            {                                                                                                                            //e for um terminal
               // printf("\nRegra encontrada (terminal)!\n%i == %i",terminais_entrada[i],Dn[n-1][j].proxVar[Dn[n-1][j].marcador][0]);
                int regraJaEmDn = 0;
                // Verifica se a regra já está em Dn
                for(l=0; l<MaxRegras; l++)  // Percorre Dn
                {
                    if(Dn[n-1][j].ID == Dn[n][l].ID)
                        regraJaEmDn = 1;
                }
                if(!regraJaEmDn)    // Se não está, coloca
                {
                   // printf("\nRegra adicionada em Dn[%i][%i]!\n", n, k);
                    Dn[n][k] = Dn[n-1][j];
                    Dn[n][k].marcador++;    // Incrementa marcador
                    k++;                    // Incrementa a posição do vetor de saída
                }
                //else
                  //  printf("\nRegra já está em Dn!\n");
            }
        }
        //printf("saiu do loop\n");

        for(j=0; j<k; j++)  // Percorre as novas regras geradas
        {
            Dn_loop(regras, terminais_entrada, lista_terminais, Dn, k, n, j, 1);
        }

        k=0;
        n++;
    }
    return 0;
}

// Função recursiva que continua Dn
int Dn_loop(struct REGRA regras[MaxRegras], int terminais_entrada[], char lista_terminais[MaxTerminais][Tamanho], struct REGRA Dn[MaxN][MaxRegras], int k, int n, int j, int marcadorAvanca)
{
    int l,m,n_cont;
    int k_buff = k;

    if(Dn[n][j].marcador == Dn[n][j].nTermos)    // Se o marcador está na última posição
    {
        //printf("\nMarcador na ultima posicao.");
        // Guarda em Dn todas as regras de Dn-1 cujo marcador aponta para a variável sendo procurada
        for(n_cont = n; n_cont>0; n_cont--) // Percorre todos os Dns gerados anteriormente
        {
            //printf("\n\nn=%i\n\n", n);
            for(l=0; l<MaxRegras; l++)   // Percorre Dn-1
            {
                if(Dn[n][j].variavel == Dn[n_cont-1][l].proxVar[Dn[n_cont-1][l].marcador][0] && Dn[n_cont-1][l].proxVar[Dn[n_cont-1][l].marcador][1]==1)   // Se a variável estiver apontada pelo marcador de uma regra
                {                                                                                                                      //e for variável
                   // printf("\nRegra encontrada!\n%i == %i",Dn[n][j].variavel, Dn[n_cont-1][l].proxVar[Dn[n_cont-1][l].marcador][0]);
                    int regraJaEmDn = 0;
                    // Verifica se a regra já está em Dn
                    for(m=0; m<MaxRegras; m++)  // Percorre Dn
                    {
                        if(Dn[n_cont-1][l].ID == Dn[n][m].ID)
                            regraJaEmDn = 1;
                    }
                    if(!regraJaEmDn)    // Se não está, coloca
                    {
                       // printf("\nRegra adicionada em Dn[%i][%i]!\n", n, k);
                        Dn[n][k] = Dn[n_cont-1][l];
                        if(marcadorAvanca)
                            Dn[n][k].marcador++;    // Incrementa marcador
                        k++;                    // Incrementa a posição do vetor de saída
                    }
                    //else
                       // printf("\nRegra já está em Dn!\n");
                }
            }
           // printf("saiu do loop\n");

            for(l=k_buff; l<k; l++)  // Percorre as novas regras geradas
            {
                k=Dn_loop(regras, terminais_entrada, lista_terminais, Dn, k, n, l, 1);
            }
        }
    }
    else
    {
        //printf("\nMarcador nao esta na ultima posicao. %i", Dn[n][j].marcador);
        if(Dn[n][j].proxVar[Dn[n][j].marcador][1]==1)   // Se o elemento apontado pelo marcador for uma variável
        {
            //printf("\nE variavel");
            for(l=0; l<NRegras; l++)    // Percorre toda a gramática
            {
                if(Dn[n][j].proxVar[Dn[n][j].marcador][0] == regras[l].variavel)    // Se a variável apontada é igual à variável da esquerda da regra
                {
                    //printf("\n_Regra encontrada!\n%i == %i",Dn[n][j].proxVar[Dn[n][j].marcador][0], regras[l].variavel);
                    int regraJaEmDn = 0;
                    // Verifica se a regra já está em Dn
                    for(m=0; m<MaxRegras; m++)  // Percorre Dn
                    {
                        if(regras[l].ID == Dn[n][m].ID)
                            regraJaEmDn = 1;
                    }
                    if(!regraJaEmDn)    // Se não está, coloca
                    {
                        //printf("\nRegra de valor %i e pos %i adicionada em Dn[%i][%i]!\n", regras[l].variavel, l, n, k);
                        Dn[n][k] = regras[l];
                        Dn[n][k].n = n;         // Informa que foi tirado da gramática por n
                        k++;                    // Incrementa a posição do vetor de saída
                    }
                    //else
                        //printf("\nRegra já está em Dn!\n");
                }
            }
            for(l=k_buff; l<k; l++)  // Percorre as novas regras geradas
            {
                //printf("\nk_loopelse:%i", k);
                k=Dn_loop(regras, terminais_entrada, lista_terminais, Dn, k, n, l, 1);
            }
        }
    }

    return k;
}

//Função que le entrada do usuario

void le_entrada(int terminais_entrada[], char lista_terminais[MaxTerminais][Tamanho])
{
    int palavrasSaoTerminais = 0;
    int i ,j, k = 0;
    char entrada_usuario[Tamanho_Entrada];
    char terminal[N_Terminais_Entrada][Tamanho];

    for(i=0; i<Tamanho_Entrada; i++)
    {
        entrada_usuario[i] = '\0';
    }
    for(i=0; i<N_Terminais_Entrada; i++)
    {
        for(j=0; j<Tamanho; j++)
        {
            terminal[i][j] = '\0';
        }
    }
    j=0;

    printf("Digite aqui a entrada a ser reconhecida\n(Caso o terminal desejado possua espaco, escrever o terminal inteiro entre aspas)\n");

    fgets (entrada_usuario, Tamanho_Entrada, stdin);

    printf("\n");

    for(i=0; i<Tamanho_Entrada; i++)
    {
        if(entrada_usuario[i] == '\n')
            entrada_usuario[i] = '\0';
    }

    for(i = 0; i<Tamanho_Entrada; i++)
    {
        if(entrada_usuario[i] == '"')
        {
            i++;
            while(entrada_usuario[i] != '"')
            {
                terminal[j][k] = entrada_usuario[i];
                //       printf("%c", entrada_usuario[i]);
                i++;
                k++;
            }
            i++;
        }
        else
        {
            while(entrada_usuario[i] != ' ' && entrada_usuario[i] != '\0')
            {
                terminal[j][k] = entrada_usuario[i];
                //         printf("%c", entrada_usuario[i]);
                i++;
                k++;
            }

        }
        j++;
        k=0;
    }

    k=0;

    for(i = 0; i<N_Terminais_Entrada; i++)
    {
        for(j = 0; j<MaxTerminais; j++)
        {
            if(strcmp(terminal[i], lista_terminais[j]) == 0 && lista_terminais[j][0] != '\0')
            {
                terminais_entrada[k] = j;
                NTerminaisIN++;
                palavrasSaoTerminais = 1;
            }
        }
        k++;
    }

    if(!palavrasSaoTerminais)
    {
        printf("\nErro! Palavra fornecida nao e terminal.\n");
        exit(0);
    }

    return;
}


// Função que gera D0
int gera_D0(int var, struct REGRA regras[MaxRegras], struct REGRA regras_out[MaxRegras], int k)
{
    //printf("\n\nIniciando D0 com var=%i e k=%i", var, k);
    int k_buff = k;
    int i,j;
    //----------------------------------------
    // Adiciona as regras da atual inicial ao vetor de saída
    //----------------------------------------
    for(i=0; i<MaxRegras; i++)  // Percorre vetor de regras
    {
        if(regras[i].proxVar[0][0]==-1) // Se a regra não existe, está no fim do vetor
            break;
        if(regras[i].variavel == var)    // Se for regra da variável atual
        {
            //printf("\n\nRegra encontrada!");
            // Verifica se a regra já está no vetor
            int estaNoVetor = 0;
            for(j=0; j<MaxRegras; j++)  // Percorre o vetor de regras
            {
                if(regras[i].ID==regras_out[j].ID)    // Se a regra já está no vetor de saída
                {
                    estaNoVetor = 1;
                    //printf("\nRegra ja esta no vetor!");
                    //printf("\nregras[i].id:%i\nregras_out[j].id: %i", regras[i].ID, regras_out[j].ID);
                }
            }
            if(!estaNoVetor)   // Se a regra não está no vetor, a adciona
            {
                regras_out[k] = regras[i];  // Adiciona a regra ao vetor de saída
                regras_out[k].n = 0;
                k++;
            }
        }
    }
    //----------------------------------------

    for(i=0; i<k; i++)  // Percorre regras_out
    {
        if(regras_out[i].marcador!=-1 && regras_out[i].proxVar[regras_out[i].marcador][1]==1 && k!=k_buff)   // Se a regra existe e o valor indicado pelo marcador é uma regra e foi adicionado algo ao vetor de saída
        {
            //printf("\nMarcador: %i\nproxVar: %i, %i",regras_out[i].marcador, regras_out[i].proxVar[regras_out[i].marcador][0], regras_out[i].proxVar[regras_out[i].marcador][1]);
            gera_D0(regras_out[i].proxVar[regras_out[i].marcador][0], regras, regras_out, k); // Para cada regra que existe, busca a variável apontada pelo marcador
        }
        else
            break;
    }
    return k;
}

//Testa se a entrada foi aceita
entrada_aceita(struct REGRA Dn[MaxN][MaxRegras], int inicial)
{
    int i,j;
    for(i=0; i<MaxRegras; i++)  // Percorre Dn[NTerminaisIN]
    {
        if(Dn[NTerminaisIN][i].variavel == inicial && Dn[NTerminaisIN][i].marcador == Dn[NTerminaisIN][i].nTermos)
            return 1;
    }
    return 0;
}


//main
int main(int argc, const char * argv[])
{
    char Terminais[MaxTerminais][Tamanho];
    char Variaveis[MaxVariaveis][Tamanho2];
    struct REGRA Regras[MaxRegras];
    struct REGRA D0[MaxRegras];
    struct REGRA Dn[MaxN][MaxRegras];
    int terminais_entrada[N_Terminais_Entrada]; //cada elemento do array deve ter a posição do array Terminais que possui o terminal digitado pelo usuario. exemplo: (the dog runs) deve fornecer um array {6, 3, 0} usando o arquivo sample.txt. se tiver um elemento -1, palavra não faz parte da linguagem
    int Inicial = 0;

    // Inicialização
    inicializa_matrizes(Terminais, Variaveis, Regras, D0, Dn);

    // Leitura do arquivo da gramática
    le_gramatica(Terminais, Variaveis, &Inicial, Regras);

    //Le entrada do usuario e completa array terminais_entrada
    le_entrada(terminais_entrada, Terminais);

    // Geração de D0
    gera_D0(Inicial, Regras, D0, 0);

    // Geração de Dn
    int i = 0;
    for(i=0; i<MaxRegras; i++)  // Dn[0] = D0
    {
        Dn[0][i] = D0[i];
    }
    gera_Dn(Regras, terminais_entrada, Terminais, Dn);



    // Imprime
    imprime_regras(Terminais, Variaveis, Regras);
    imprime_terminais(Terminais);
    imprime_variaveis(Variaveis, Inicial);

    for(i=0; i<=NTerminaisIN; i++)
    {
        printf("\n-----------------------------");
        printf("\nD%i", i);
        //puts(terminais_entrada[i]);
        imprime_regras(Terminais, Variaveis, Dn[i]);
    }

    if(entrada_aceita(Dn, Inicial))
        printf("\nENTRADA ACEITA!\n\n");
    else
        printf("\nENTRADA Rejeitada!\n\n");

    printf("NVariaveis: %i\nNTerminais: %i\nNRegras: %i\n\nInsira qualquer caractere para terminar o programa\n", NVariaveis, NTerminais, NRegras);
    getchar();

    return 0;
}
