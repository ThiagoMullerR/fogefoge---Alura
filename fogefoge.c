#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"

MAPA m;
POSICAO heroi;

int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino){
    int opcoes[4][2] = {
        {xatual, yatual +1},
        {xatual +1, yatual},
        {xatual, yatual -1},
        {xatual -1, yatual}
    };

    srand(time(0));
    for(int i = 0; i < 10; i++){
        int posicao = rand() % 4;

        if(podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])){
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
            return 1;
        }
    }
    return 0;
}

void fantasmas(){
    MAPA copia;
    copiamapa(&copia, &m);

    for(int i = 0; i < m.linhas; i++){
        for(int j = 0; j < m.colunas; j++){

            if(copia.matriz[i][j] == FANTASMA){

                int xdestino;
                int ydestino;

                int encontrou = praondefantasmavai(i, j, &xdestino, &ydestino);

                if(encontrou){
                    andanomapa(&m, i, j, xdestino, ydestino);
                }
                
            }
        }
    }
    liberamapa(&copia);
}


int acabou(){
    POSICAO pos;
    int fogefogenomapa = encontramapa(&m, &pos, HEROI);
    return !fogefogenomapa;
}

int ehdirecao(char direcao){
    return direcao == ESQUERDA ||
        direcao == CIMA ||
        direcao == BAIXO ||
        direcao == DIREITA;
}

void move(char direcao){

    // valida a entrada
    if(!ehdirecao(direcao))
        return;
    
    // Descobrir o que tem na casa que o jogador que que o pacman vá
    // ao final do switch case, o proximox e proximoy vai apontar a case que o jogador quer que ele vá
    int proximox = heroi.x;
    int proximoy = heroi.y;

    switch(direcao){
        case ESQUERDA:
            //esquerda
            proximoy--;
            break;
        case CIMA:
            //cima
            proximox--;
            break;
        case BAIXO:
            //baixo
            proximox++;
            break;
        case DIREITA:
            //direita
            proximoy++;
            break;
    }

    if(!podeandar(&m, HEROI, proximox, proximoy))
        return;
    
    // validação
    // após a validação dos ifs, o pac-man pode andar
    
    //insere o pacman
    //m.matriz[proximox][proximoy] = '@';
    
    // a posiçao antiga recebe um ponto
    //m.matriz[heroi.x][heroi.y] = '.';

    andanomapa(&m, heroi.x, heroi.y, proximox, proximoy);
    // a posição do heroi agora é:
    heroi.x = proximox;
    heroi.y = proximoy;
    
}

int main(){
    
    lemapa(&m);
    encontramapa(&m, &heroi, HEROI);
    
    do{    
        imprimemapa(&m);
        
        char comando;
        scanf(" %c", &comando);
        move(comando);
        fantasmas();
        
    }while(!acabou());

    liberamapa(&m);
}