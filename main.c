#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX 10


int printBoard(), jogar_dado();
void jogador1(), jogador2();

int pos_j1=0, pos_j2=0, tabuleiro[MAX];

int main(){
    int pipe_j1[2], pipe_j2[2], pipe_j1_s[2], pipe_j2_s[2], descritorj1, descritorj2;
    if (pipe(pipe_j1) < 0 || pipe(pipe_j1_s) < 0 || pipe(pipe_j2) < 0 || pipe(pipe_j2_s) < 0) {
        printf("Erro na chamada PIPE");
        exit(1);
    }
    descritorj1 = fork();
    if(descritorj1<0){
        printf("Erro no jogador 1");
        exit(1);
    }
    if(descritorj1>0){
        descritorj2 = fork();
        if(descritorj2<0){
            printf("Erro no jogador 2");
            exit(1);
        }
        if(descritorj2==0){
            jogador2();
        }
    }else{
        jogador1();
    }
    
    //printf("main.c");
}

int jogar_dado() {
    srand(time(NULL) + getpid());  
    int resultado = (rand() % 6) + 1;
    printf("Dado jogado! Valor obtido: %d\n", resultado);
    return resultado;
}

void jogador1(){
    int dado = jogar_dado();
    pos_j1 += dado;
    printf("Jogador 1 está na posição %d\n", pos_j1);
}

void jogador2(){
    int dado = jogar_dado();
    pos_j2 += dado;
    printf("Jogador 2 está na posição %d\n", pos_j2);
}

int printBoard(){

}