#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//Processos:
// Processo Servidor: Controla o tabuleiro, gerencia os movimentos, checa quem venceu.
// Processo Jogador 1
// Processo Jogador 2

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
    descritorj2 = fork();
    if(descritorj2<0){
        printf("Erro no jogador 2");
        exit(1);
    }
    printf("main.c");
}