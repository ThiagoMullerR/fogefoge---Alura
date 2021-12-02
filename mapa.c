#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

void copiamapa(MAPA* destino, MAPA* origem){
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;
    alocamapa(destino);
    for(int i = 0; i < origem->linhas; i++){
        strcpy(destino->matriz[i], origem->matriz[i]);
    }
}

void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino){
    char personagem = m->matriz[xorigem][yorigem];
    m->matriz[xdestino][ydestino] = personagem;
    m->matriz[xorigem][yorigem] = VAZIO;
}

// já está na ultima casa (para nao sair do mapa)
int ehvalida(MAPA* m, int x, int y){
    if(x >= m->linhas)
        return 0;
    if(y >= m->colunas)
        return 0;
    
    return 1;
}

// só anda uma posição se tiver pontinho
int ehvazia(MAPA* m, int x, int y){
    return m->matriz[x][y] == VAZIO;
}

void encontramapa(MAPA* m, POSICAO* p, char c){
    // acha a posiçao do foge foge
    for(int i = 0; i < m->linhas; i++){
        for(int j = 0; j < m->colunas; j++){
            if(m->matriz[i] [j] == c){
                p->x = i;
                p->y = j;
                break;
            }
        }
    }
}

void liberamapa(MAPA* m){
    for (int i = 0; i < m->linhas; i++){
        free(m->matriz[i]); // free(*m.matriz[i]); é a mesma coisa que free(m->matriz[i]);
    }
    free(m->matriz);
}
void alocamapa(MAPA* m){
    ////////////////
    // Recebe o mapa
    m->matriz = malloc(sizeof(char*) * m->linhas);
    for (int i = 0; i < m->linhas; i++){
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));
    }
    ////////////////
}

void lemapa(MAPA* m){
    // Abertura do arquivo
    FILE* f;
    f = fopen("mapa.txt", "r");
    if(f == 0){
        printf("Erro na leitura do mapa!\n");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->linhas), &(m->colunas));

    ////////////////
    //  
    //  ALOCAÇÃO DINÂMICA DE MEMÓRIA - EXEMPLO SIMPLIES
    //
    // int* v = malloc(sizeof(int) * 50); //int* v = malloc(4); // 4 é o valor de bits de um inteiro (int)
    // É usado o sizeof(int) para descobrir o tamanho dos bits da arquitetura que o código está rodando, pois ela pode variar
    // Para declarar um array, é só multiplicar pelo numero de posições do array e depois inserir os valores
    // v[0] = 10;
    // v[1] = 20;
    // printf("inteiro alocado %d %d\n", v[0], v[1]);
    //free(v); //toda vez que usamos o maloc (mexemos com alocação dinâmica de memoria) devemos livrar o espaço após usá-lo.
    ////////////////

    ////////////////
    //  
    //  ALOCAÇÃO DINÂMICA DE MEMÓRIA - EXEMPLO COMPLEXO (matriz)
    //
    //int** v = malloc(sizeof(int*) * 5);
    //for(int i = 0; i < 5; i++){
    //    v[i] = malloc(sizeof(int) * 10);
    //}
    //
    //v [0] [0] = 10;
    //v [1] [2] = 12;
    //printf("inteiro alocado %d %d\n", v[0] [0], v[1] [2]);
    //for(int i = 0; i < 5; i++){
    //   free(v[i]);
    //}
    //free(v);
    ////////////////

    alocamapa(m);
    


    // ~lendo e gravando as linhas da matriz~
    // Neste caso, estamos passando as linhas da matriz. 
    // Se fosse utilizar "mapa[i] [j]" no loop, estaríamos passando uma posição da matriz.
    // Passando a primeira dimensão, estamos passando apenas a linha.
    for(int i = 0; i < 5; i++){
        fscanf(f, "%s", m->matriz[i]);
    }
    
    fclose(f);

    // Não usamos assim porque estaríamos imprimindo posição por posiçao.
    //for(int i = 0; i < 5; i++){
    //    for(int j = 0; j < 10; j++){
    //        printf("%c", mapa[i] [j]);
    //    }
    //    printf("\n");
    //}

}
void imprimemapa(MAPA* m){
    // Então Economizamos imprimindo o mapa apenas linha por linha.
    for(int i = 0; i < 5; i++){
        printf("%s\n", m->matriz[i]);
    }
}