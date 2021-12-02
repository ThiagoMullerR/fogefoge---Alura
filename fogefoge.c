#include <stdio.h>
#include <stdlib.h>
#include "fogefoge.h"
#include "mapa.h"

MAPA m;
POSICAO heroi;

void fantasmas(){
    MAPA copia;
    copiamapa(&copia, &m);

    for(int i = 0; i < m.linhas; i++){
        for(int j = 0; j < m.colunas; j++){

            if(copia.matriz[i][j] == FANTASMA){
                if(ehvalida(&m, i, j+1) && ehvazia(&m,i, j+1)){
                    andanomapa(&m, i, j, i, j+1);
                }
                
            }
        }
    }
    liberamapa(&copia);
}


int acabou(){
    return 0;
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

    // validação
    if(!ehvalida(&m, proximox, proximoy))
        return;
    
    // após a validação dos ifs, o pac-man pode andar
    if(!ehvazia(&m, proximox, proximoy))
        return;
    
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