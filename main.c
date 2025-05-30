#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX 10

//Processos:
// Processo Servidor: Controla o tabuleiro, gerencia os movimentos, checa quem venceu.
// Processo Jogador 1
// Processo Jogador 2

int printBoard();
void jogador1(), jogador2();

int pos_j1=0, pos_j2=0, tabuleiro[MAX];

int main(){
    int pipe_j1[2], pipe_j2[2], pipe_j1_s[2], pipe_j2_s[2], descritorj1, descritorj2;
    if (pipe(pipe_j1_s) < 0 || pipe(pipe_j1_s) < 0 || pipe(pipe_j2_s) < 0 || pipe(pipe_j2_s) < 0) {
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

void jogador1(){

}

void jogador2(){

}

int printBoard(){

}