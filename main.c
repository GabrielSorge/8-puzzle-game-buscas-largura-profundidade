#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>


typedef struct Estado {
    int matriz[3][3];
    int profundidade;
    struct Estado *Pai;
} Estado;


typedef struct NoFila {
    Estado dado;
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *ini;
    NoFila *fim;
} Fila;


Fila *cria_fila() {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}


int fila_vazia(Fila *f) {
    return (f->ini == NULL);
}


Estado desenfileira(Fila *f) {
    Estado vazio;
    vazio.profundidade = -1;

    if (fila_vazia(f)){
        return vazio;
    }

    NoFila *n = f->ini;
    Estado e = n->dado;

    f->ini = n->prox;
    if (f->ini == NULL) {
        f->fim = NULL;
    }

    free(n);
    return e;
}


void liberar_fila(Fila *f) {
    while (!fila_vazia(f)) {
        desenfileira(f);
    }
    free(f);
}


void copiar_estado(Estado *dest, Estado *orig) {
    *dest = *orig;
}


void copiar_matriz_vetor(int vet[9], int matriz[3][3]) {
    int k = 0;
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            vet[k++] = matriz[i][j];
        }
    }
}


int comparar_vetores(int a[9], int b[9]) {
    for (int i=0;i<9;i++){
        if (a[i] != b[i]){
            return 0;
        }
    }
    return 1;
}


void enfileira(Fila *f, Estado e) {
    NoFila *novo = (NoFila*) malloc(sizeof(NoFila));
    novo->dado = e;
    novo->prox = NULL;

    if (f->fim != NULL) {
        f->fim->prox = novo;
    }
    f->fim = novo;

    if (f->ini == NULL) {
        f->ini = novo;
    }
}



typedef struct No {
    Estado info;
    struct No *prox;
} No;

typedef struct Pilha {
    No *Topo;
} Pilha;


Pilha* CriaPilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->Topo = NULL;
    return p;
}

int vaziaPilha(Pilha *p) {
    return (p->Topo == NULL);
}

void push(Pilha *p, Estado valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->info = valor;
    novo->prox = p->Topo;
    p->Topo = novo;
}

Estado pop(Pilha *p) {
    if (vaziaPilha(p)) {
        Estado vazio;
        vazio.profundidade = -1;
        return vazio;
    }

    No *temp = p->Topo;
    Estado valor = temp->info;
    p->Topo = temp->prox;
    free(temp);
    return valor;
}

void liberaPilha(Pilha *p) {
    while (!vaziaPilha(p)) {
        pop(p);
    }

    free(p);
}



int verifica(int V[]){
    int inversoes=0;
    for(int i=0;i<9;i++){
        for(int j=i+1;j<9;j++){
            if(V[i]>V[j] && V[i]!=0 && V[j]!=0){
                inversoes++;
            }
        }
    }
    return inversoes;
}


void gerar(int m[3][3]){
    int numeros[9];
    int numero_de_inversoes;

    for(int i=0;i<9;i++)
    {
        numeros[i]=i;
    }

    do{
        srand(time(NULL));
        for (int i=0;i<9;i++)
        {
            int r= rand()%9;
            int temp=numeros[i];
            numeros[i]=numeros[r];
            numeros[r]=temp;
        }
        numero_de_inversoes=verifica(numeros);
    }while(numero_de_inversoes%2!=0);


    int k=0;
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            m[i][j]=numeros[k++];
        }
    }
}


void imprimir(int m[3][3]){
    printf("\n\n\n");
    printf("\t\t\t  ===========================\n");
    printf("\t\t\t  ===    JOGO 8-PUZZLE    ===\n");
    printf("\t\t\t  ===========================\n");
    printf("\n\n");
    for (int i=0;i<3;i++){
        printf("\t\t\t\t+---+---+---+\n");
        printf("\t\t\t\t|");
        for (int j=0;j<3;j++){
            if(m[i][j]==0){
                printf("   ");
                printf("|");
            }
            else{
                printf(" %d ", m[i][j]);
                printf("|");

            }
        }
        printf("\n");
    }
    printf("\t\t\t\t+---+---+---+\n");
}



void localizar_vazio(int m[3][3], int *linha, int *coluna){
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            if(m[i][j]==0){
                *linha=i;
                *coluna=j;
                return;
            }
        }
    }
}



void mover(int direcao, int m[3][3], int *mov){
    int i,j;
    localizar_vazio(m, &i, &j);

    int novo_i=i,novo_j=j;


    if((direcao == 5 && i > 0) || (direcao == 2 && i < 2) || (direcao == 1 && j > 0) || (direcao == 3 && j < 2)){
            if (direcao == 5){
                novo_i--;
                (*mov)++;
            }
            if (direcao == 2){
                novo_i++;
                (*mov)++;

            }
            if (direcao == 1){
                novo_j--;
                (*mov)++;
            }
            if (direcao == 3){
                novo_j++;
                (*mov)++;
            }
    }


    int temp=m[i][j];
    m[i][j]=m[novo_i][novo_j];
    m[novo_i][novo_j]=temp;
}



int venceu(int m[3][3]){
    int num = 1;

    for (int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==2 && j==2){
                return (m[i][j] == 0);
            }
            if(m[i][j] != num++){
                return 0;
            }
        }
    }

    return 1;
}


void imprime_certo(){
    int m[3][3];
    int k=1;
    printf("\n\n\n");
    printf("\t\t\t  ===========================\n");
    printf("\t\t\t  ===    JOGO 8-PUZZLE    ===\n");
    printf("\t\t\t  ===========================\n");
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            if(i==2 && j==2){
                m[i][j]=0;
            }
            else{
                m[i][j]=k++;
            }
        }
    }
    printf("\n\n");
    for (int i = 0; i < 3; i++){
        printf("\t\t\t\t+---+---+---+\n");
        printf("\t\t\t\t|");
        for (int j = 0; j < 3; j++){
            if (m[i][j] == 0){
                printf("   ");
                printf("|");
            }
            else{
                printf(" %d ", m[i][j]);
                printf("|");
            }

        }
        printf("\n");
    }
    printf("\t\t\t\t+---+---+---+\n");
}


int mover_estado(int direcao, int m[3][3]){
    int i, j;
    localizar_vazio(m, &i, &j);

    int novo_i = i, novo_j = j;


    if ((direcao == 5 && i > 0) ||  (direcao == 2 && i < 2) ||  (direcao == 1 && j > 0) ||   (direcao == 3 && j < 2)) {

        if (direcao == 5) {
            novo_i--;
        }
        if (direcao == 2) {
            novo_i++;
        }
        if (direcao == 1) {
            novo_j--;
        }
        if (direcao == 3) {
            novo_j++;
        }

        int temp = m[i][j];
        m[i][j] = m[novo_i][novo_j];
        m[novo_i][novo_j] = temp;
        return 1;
    }

    return 0;
}


void copia_matriz(int destino[3][3], int origem[3][3]) {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            destino[i][j] = origem[i][j];
        }
    }
}



void imprimir_solucao(int m[3][3]){

    printf("\n");
    for (int i=0;i<3;i++){
        printf("\t\t\t\t+---+---+---+\n");
        printf("\t\t\t\t|");
        for (int j=0;j<3;j++){
            if(m[i][j]==0){
                printf("   ");
                printf("|");
            }
            else{
                printf(" %d ", m[i][j]);
                printf("|");

            }
        }
        printf("\n");
    }
    printf("\t\t\t\t+---+---+---+\n");
}

void imprime_caminho(Estado *estado_final) {
    Pilha *caminho = CriaPilha();
    Estado *atual = estado_final;
    int passos = 0;

    while (atual != NULL) {
        push(caminho, *atual);
        atual = atual->Pai;
        passos++;
    }

    printf("\n\n\n\t\t=== Caminho da Solu��o (total de %d movimentos) ===\n\n\n", passos - 1);

    int passo = 0;
    while (!vaziaPilha(caminho)) {
        Estado e = pop(caminho);
        printf("\n\t\t\t      ---  Passo %d  ---\n", passo++);
        imprimir_solucao(e.matriz);
        printf("\n\t\t\t       Profundidade: %d\n\n\n", e.profundidade);
        printf("\t----------------------------------------------------------------\n\n");
    }

    liberaPilha(caminho);
}

int compara_matriz(int a[3][3], int b[3][3]) {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (a[i][j] != b[i][j]){
                return 0;
            }
        }
    }
    return 1;
}

int existe(int m[3][3], int num){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(m[i][j] == num)
                return 1;
        }
    }
    return 0;
}


int verifica_m_proprio(int m[3][3]){
    int inversoes=0, k = 0;;
    int V[9];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            V[k]=m[i][j];
            k++;
        }
    }
    int i = 0;
    int j = 0;
    for(i=0;i<9;i++){
        for(j=i+1;j<9;j++){
            if(V[i]>V[j] && V[i]!=0 && V[j]!=0){
                inversoes++;
            }
        }
    }
    return inversoes;
}



void imprimir_m_propria(int m[3][3]){
    printf("\n\n\n");
    printf("\t\t\t  ===========================\n");
    printf("\t\t\t  ===    JOGO 8-PUZZLE    ===\n");
    printf("\t\t\t  ===========================\n\n");
    printf("\t\t\t =  Inserindo matriz pr�pria =\n");
    printf("\n\n");
    for (int i=0;i<3;i++){
        printf("\t\t\t\t+---+---+---+\n");
        printf("\t\t\t\t|");
        for (int j=0;j<3;j++){
            if(m[i][j]==9 || m[i][j]==0){
                printf("   ");
                printf("|");
            }
            else{
                printf(" %d ", m[i][j]);
                printf("|");

            }
        }
        printf("\n");
    }
    printf("\t\t\t\t+---+---+---+\n");
}

void corrige_m(int m[3][3], int i, int j){
    if(m[i][j] == 9){
        m[i][j] = 0;
    }
}


void insere_puzzle(int m[3][3], int i, int j){
    int k;
    do {
        printf("\n\n\t\t\t Preenchendo posi��o %d x %d\n", i+1, j+1);
        printf("\t\t    Digite um n�mero de 1 a 9 (9 = vazio): ");
        scanf("%d", &k);

        if (k < 1 || k > 9) {
            printf("\n\t\t   Valor inv�lido! Use apenas n�meros de 1 a 9.\n");

        }
        else if (existe(m, k)) {
            printf("\n\t\t   O n�mero %d j� foi inserido! Informe outro.\n", k);

        }



    } while (k < 1 || k > 9 || existe(m, k));

    m[i][j] = k;
}


int ja_visitado(Estado vet[], int qtd, int m[3][3]) {
    for (int k = 0; k < qtd; k++) {
        int igual = 1;
        for (int i = 0; i < 3 && igual; i++) {
            for (int j = 0; j < 3; j++) {
                if (vet[k].matriz[i][j] != m[i][j]) {
                    igual = 0;
                    break;
                }
            }
        }
        if (igual){
            return 1;
        }
    }
    return 0;
}



int adiciona_visitado(Estado **vet, int *qtd, Estado e) {
    Estado *novo = realloc(*vet, (*qtd + 1) * sizeof(Estado));
    if (!novo){
        return 0;
    }
    *vet = novo;
    (*vet)[*qtd] = e;
    (*qtd)++;
    return 1;
}

int busca_largura(int inicial_matriz[3][3]) {
    Fila *f = cria_fila();

    Estado inicial;

    copia_matriz(inicial.matriz, inicial_matriz);
    inicial.profundidade = 0;
    inicial.Pai = NULL;

    enfileira(f, inicial);

    Estado *visitados = NULL;
    int qtdVisit = 0;
    adiciona_visitado(&visitados, &qtdVisit, inicial);

    while (!fila_vazia(f)) {
        Estado atual = desenfileira(f);
        if (atual.profundidade == -1) {
            break;
        }
        if (venceu(atual.matriz)) {
                imprime_caminho(&atual);
                free(visitados);
                liberar_fila(f);
                return 1;
        }
        int movs[4] = {5, 2, 1, 3};

        for (int k = 0; k < 4; k++) {
            int aux[3][3];
            copia_matriz(aux, atual.matriz);

            if (!mover_estado(movs[k], aux)){
                    continue;
            }

            if (!ja_visitado(visitados, qtdVisit, aux)) {

                Estado filho;
                copia_matriz(filho.matriz, aux);
                filho.profundidade = atual.profundidade + 1;
                filho.Pai = malloc(sizeof(Estado));
                *filho.Pai = atual;


                Estado filho_visita;
                copia_matriz(filho_visita.matriz, filho.matriz);
                filho_visita.profundidade = filho.profundidade;
                filho_visita.Pai = NULL;

                if (!adiciona_visitado(&visitados, &qtdVisit, filho_visita)) {

                    free(filho.Pai);
                    free(visitados);
                    liberar_fila(f);
                    return 0;
                }

                enfileira(f, filho);
            }
        }
    }

    free(visitados);
    liberar_fila(f);
    return 0;
}



int busca_profundidade_limitada(Pilha *p, int limite){
    int linha, coluna;
    while(!vaziaPilha(p)){
        Estado atual = pop(p);
        if(venceu(atual.matriz)){
                imprime_caminho(&atual);
                return 1;
        }
        else if(atual.profundidade < limite){
              localizar_vazio(atual.matriz, &linha, &coluna);
              if(linha>0){
                  int nova_matriz[3][3];
                  copia_matriz(nova_matriz, atual.matriz);
                  mover_estado(5,nova_matriz);

                  Estado filho;
                  copia_matriz(filho.matriz, nova_matriz);
                  filho.profundidade = atual.profundidade + 1;
                  filho.Pai = malloc(sizeof(Estado));
                  *filho.Pai = atual;


                  int repetido = 0;
                  Estado *temp = filho.Pai;

                  while(temp != NULL){
                    if(compara_matriz(temp->matriz, filho.matriz)){
                        repetido = 1;
                        break;
                    }
                    temp = temp->Pai;
                  }
                  if(!repetido){
                    push(p, filho);
                  }
              }

              if(linha<2){
                  int nova_matriz[3][3];
                  copia_matriz(nova_matriz, atual.matriz);
                  mover_estado(2,nova_matriz);

                  Estado filho;
                  copia_matriz(filho.matriz, nova_matriz);
                  filho.profundidade = atual.profundidade + 1;
                  filho.Pai = malloc(sizeof(Estado));
                  *filho.Pai = atual;

                  int repetido = 0;
                  Estado *temp = filho.Pai;

                  while(temp != NULL){
                    if(compara_matriz(temp->matriz, filho.matriz)){
                        repetido = 1;
                        break;
                    }
                    temp = temp->Pai;
                  }
                  if(!repetido){
                    push(p, filho);
                  }
              }

              if(coluna>0){
                  int nova_matriz[3][3];
                  copia_matriz(nova_matriz, atual.matriz);
                  mover_estado(1,nova_matriz);

                  Estado filho;
                  copia_matriz(filho.matriz, nova_matriz);
                  filho.profundidade = atual.profundidade + 1;
                  filho.Pai = malloc(sizeof(Estado));
                  *filho.Pai = atual;

                  int repetido = 0;
                  Estado *temp = filho.Pai;

                  while(temp != NULL){
                    if(compara_matriz(temp->matriz, filho.matriz)){
                        repetido = 1;
                        break;
                    }
                    temp = temp->Pai;
                  }
                  if(!repetido){
                    push(p, filho);
                  }
              }

              if(coluna<2){
                  int nova_matriz[3][3];
                  copia_matriz(nova_matriz, atual.matriz);
                  mover_estado(3,nova_matriz);

                  Estado filho;
                  copia_matriz(filho.matriz, nova_matriz);
                  filho.profundidade = atual.profundidade + 1;
                  filho.Pai = malloc(sizeof(Estado));
                  *filho.Pai = atual;
                  int repetido = 0;
                  Estado *temp = filho.Pai;

                  while(temp != NULL){
                    if(compara_matriz(temp->matriz, filho.matriz)){
                        repetido = 1;
                        break;
                    }
                    temp = temp->Pai;
                  }
                  if(!repetido){
                    push(p, filho);
                  }
              }
        }
    }
    return 0;
}



int busca_profundidade_iterativa(int m[3][3]){

    system("cls");
    Estado inicial;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            inicial.matriz[i][j]=m[i][j];
        }
    }

    inicial.profundidade = 0;
    inicial.Pai = NULL;

    int lim=0;

    while (1) {
        Pilha *p = CriaPilha();
        push(p, inicial);

            if (busca_profundidade_limitada(p, lim)) {
                printf("\t\t\tSolu��o encontrada com limite %d\n\n\n\n\n", lim);
                liberaPilha(p);
                system("pause");
                return 1;
            }

        liberaPilha(p);
        lim++;
    }

}


int opcao_escolhida(){

    char i;
    int opcao;
    do{
        printf("\n\n\n");
        printf("\t\t\t  ===========================\n");
        printf("\t\t\t  ===    JOGO 8-PUZZLE    ===\n");
        printf("\t\t\t  ===========================\n\n");

        printf("\t\t\t  1 - Jogar\n");
        printf("\t\t\t  2 - Resolver puzzle com IA\n");
        printf("\t\t\t  3 - Encerrar jogo\n\n");
        printf("\t\t\t  Escolha a op��o desejada: ");
        scanf("%c",&i);
        opcao = i - '0';

        system("cls");
    }while(opcao != 1 && opcao != 2 && opcao != 3);
    return opcao;

}




int main(){
    setlocale(LC_ALL,"portuguese");

    char recebe;
    int matriz[3][3]={0,0,0,0,0,0,0,0,0};
    int direcao, ganhou=0, movimentos=0, solucao, tipo_busca=0, qual_puzzle, opcao_m, i, j, inversoes;

    printf("\n\n\n");
    printf("\t\t\t  ===========================\n");
    printf("\t\t\t  ===    JOGO 8-PUZZLE    ===\n");
    printf("\t\t\t  ===========================\n\n\n");

    printf("\t\tO objetivo do 8-puzzle � conseguir organizar os \n");
    printf("\t\tnumeros de 1 a 8 em ordem crescente com o espa�o\n");
    printf("\t\t      vazio por ultimo em uma matriz 3x3.       \n");
    printf("\t\tSua miss�o � conseguir chegar no objetivo com o \n");
    printf("\t\t     menor n�mero de movimentos poss�veis.      \n");

    printf("\n\n\t\t\t\tBOA SORTE !!!!\n\n\n");

    system("pause");
    system("cls");


    qual_puzzle = opcao_escolhida();

    switch(qual_puzzle){

        case 1:

            do{
                system("cls");
                printf("\n\n\n");
                printf("\t\t\t  ===========================\n");
                printf("\t\t\t  ===    JOGO 8-PUZZLE    ===\n");
                printf("\t\t\t  ===========================\n\n");

                printf("\t\t\t  1 - Inserir matriz pr�pria\n");
                printf("\t\t\t  2 - Inserir matriz aleat�ria\n\n");
                printf("\t\t\t  Escolha a op��o desejada: ");
                scanf("%d",&opcao_m);

            }while(opcao_m != 1 && opcao_m !=2);

            if(opcao_m == 1){

                do{
                    system("cls");
                    for(i = 0; i <3; i++){

                        for(j=0; j<3; j++){

                            imprimir_m_propria(matriz);
                            insere_puzzle(matriz, i, j);
                            system("cls");

                        }
                    }
                    i = 0;
                    j = 0;
                    for(i = 0; i <3; i++){

                        for(j=0; j<3; j++){
                            corrige_m(matriz, i, j);
                        }
                    }
                    inversoes = verifica_m_proprio(matriz);
                    if (inversoes %2!=0){
                        imprimir(matriz);
                        printf("\n\n\t\tEsse tabuleiro � impossivel de ser resolvido!\n");
                        printf("\t\t          Por favor insira outro.\n\n\n");
                        i = 0;
                        j = 0;
                        for(i = 0; i <3; i++){

                            for(j=0; j<3; j++){

                                matriz[i][j] = 0;

                            }
                        }
                        system("pause");
                    }
                }while(inversoes %2!=0);


            }


            if(opcao_m == 2){

                system("cls");
                gerar(matriz);
            }

            while (!ganhou){

                imprimir(matriz);

                printf("\n\n\tMovimentos: 5 = Cima | 2 = Baixo | 1 = Esquerda | 3 = Direita\n");
                printf("\tQuantidade de movimentos: %d",movimentos);
                printf("\n\n\t\t\t     Digite o movimento: ");

                do{
                    recebe=getch();
                    direcao = recebe - '0';//converte o char para int
                }while(direcao != 5 && direcao != 1 && direcao != 2 && direcao != 3);

                mover(direcao,matriz,&movimentos);
                ganhou=venceu(matriz);

                system("cls");
            }
            imprime_certo();
            printf("\n\n\t\t\t  PARAB�NS VOC� VENCEU!!!!!!\n");
            printf("\n\t\t\tVoc� precisou de %d movimentos\n\n\n",movimentos);

            break;

        case 2:

            do{
                system("cls");
                printf("\n\n\n");
                printf("\t\t\t  ===========================\n");
                printf("\t\t\t  ===    JOGO 8-PUZZLE    ===\n");
                printf("\t\t\t  ===========================\n\n");

                printf("\t\t\t  1 - Inserir matriz pr�pria\n");
                printf("\t\t\t  2 - Inserir matriz aleat�ria\n\n");
                printf("\t\t\t  Escolha a op��o desejada: ");
                scanf("%d",&opcao_m);

            }while(opcao_m != 1 && opcao_m !=2);

            if(opcao_m == 1){

                do{
                    system("cls");
                    for(i = 0; i <3; i++){

                        for(j=0; j<3; j++){

                            imprimir_m_propria(matriz);
                            insere_puzzle(matriz, i, j);
                            system("cls");

                        }
                    }
                    i = 0;
                    j = 0;
                    for(i = 0; i <3; i++){

                        for(j=0; j<3; j++){
                            corrige_m(matriz, i, j);
                        }
                    }
                    inversoes = verifica_m_proprio(matriz);
                    if (inversoes %2!=0){
                        imprimir(matriz);
                        printf("\n\n\t\tEsse tabuleiro � impossivel de ser resolvido!\n");
                        printf("\t\t          Por favor insira outro.\n\n\n");
                        i = 0;
                        j = 0;
                        for(i = 0; i <3; i++){

                            for(j=0; j<3; j++){

                                matriz[i][j] = 0;

                            }
                        }
                        system("pause");
                    }
                }while(inversoes %2!=0);


            }


            if(opcao_m == 2){

                system("cls");
                gerar(matriz);
            }

            do{
                system("cls");
                imprimir(matriz);
                printf("\n\n\t\t   1 - Para resolver por busca em largura\n");
                printf("\n\t\t   2 - Para resolver por busca em profundidade\n\n");
                printf("\t\t   Insira op��o preferida para solu��o: ");
                scanf("%d",&solucao);
            }while(solucao != 1 && solucao != 2);

            while(tipo_busca == 0){
                if(solucao == 1){

                    system("cls");
                    printf("\n\n\t\tResolvendo por busca em largura...\n");
                    Sleep(2000);
                    busca_largura(matriz);
                    tipo_busca = 1;

                }
                if (solucao == 2) {

                    system("cls");
                    printf("\n\n\t\tResolvendo por busca em profundidade iterativa...\n");
                    Sleep(2000);
                    busca_profundidade_iterativa(matriz);
                    tipo_busca = 1;
                }

            }

            break;

        case 3:

            return 0;

            break;

    }
    return 0;
}
