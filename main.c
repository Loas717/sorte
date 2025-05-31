#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX 10

//para fazer: o jogo fica melhor se for manual msm, o srand produz numeros similares

int printBoard(), jogar_dado();
void jogador1(int readfd, int writefd), jogador2(int readfd, int writefd), capturaTeclado(int id);

int pos_j1=0, pos_j2=0, tabuleiro[MAX];

int main(){
    srand(time(NULL) + getpid());
    int pipe_j1[2], pipe_j2[2], pipe_j1_s[2], pipe_j2_s[2], descritorj1, descritorj2;
    int quem_comeca = rand() % 2; // 0 = jogador1, 1 = jogador2
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
            close(pipe_j2[0]);
            close(pipe_j1_s[1]);
            close(pipe_j1[0]); 
            close(pipe_j1[1]);
            close(pipe_j1_s[0]); 
            close(pipe_j1_s[1]);
            jogador2(pipe_j2_s[0], pipe_j2[1]);
        }
    }else{
        close(pipe_j1[0]);
        close(pipe_j1_s[1]);
        close(pipe_j2[0]); 
        close(pipe_j2[1]);
        close(pipe_j2_s[0]); 
        close(pipe_j2_s[1]);
        jogador1(pipe_j1_s[0], pipe_j1[1]);
    }
    close(pipe_j1[1]);    
    close(pipe_j1_s[0]);   
    close(pipe_j2[1]);    
    close(pipe_j2_s[0]);

    int dado, j_1=0,j_2=1;

    printf("Quem começa? %d\n", quem_comeca);

    while (1)
    {
        if(quem_comeca==0){
            capturaTeclado(j_1);
            write(pipe_j1_s[1],&j_1,sizeof(int));
            read(pipe_j1[0], &dado,sizeof(int));
            pos_j1+=dado;
            printf("Jogador 1 tirou %d e foi para posição %d\n", dado, pos_j1);
            if(pos_j1>=MAX){
                printf("Jogador 1 venceu!\n");
                break;            
            }

            capturaTeclado(j_2);
            write(pipe_j2_s[1],&j_2,sizeof(int));
            read(pipe_j2[0], &dado,sizeof(int));
            pos_j2+=dado;
            printf("Jogador 2 tirou %d e foi para posição %d\n", dado, pos_j2);
            if(pos_j2>=MAX){
                printf("Jogador 2 venceu!\n");
                break;               
            }
        }else{
            capturaTeclado(j_2);
            write(pipe_j2_s[1],&j_2,sizeof(int));
            read(pipe_j2[0], &dado,sizeof(int));
            pos_j2+=dado;
            printf("Jogador 2 tirou %d e foi para posição %d\n", dado, pos_j2);
            if(pos_j2>=MAX){
                printf("Jogador 2 venceu!\n");
                break;               
            }

            capturaTeclado(j_1);
            write(pipe_j1_s[1],&j_1,sizeof(int));
            read(pipe_j1[0], &dado,sizeof(int));
            pos_j1+=dado;
            printf("Jogador 1 tirou %d e foi para posição %d\n", dado, pos_j1);
            if(pos_j1>=MAX){
                printf("Jogador 1 venceu!\n");
                break;               
            }
        }
    }
    

    close(pipe_j1[0]);
    close(pipe_j1_s[1]);
    close(pipe_j2[0]);
    close(pipe_j2_s[1]);
    //printf("main.c");
}

int jogar_dado() {
    //srand(time(NULL) + getpid());  
    int resultado = (rand() % 6) + 1;
    //printf("Dado jogado! Valor obtido: %d\n", resultado);
    return resultado;
}

void jogador1(int readfd, int writefd){
    srand(time(NULL) + getpid()); 
    while (1)
    {
        int comando;
        read(readfd, &comando, sizeof(int));
        if(comando==0){
            int dado = jogar_dado();
            //pos_j1 += dado;
            write(writefd, &dado, sizeof(int));
            //printf("Jogador 1 está na posição %d\n", pos_j1);
        }
    }
}

void jogador2(int readfd, int writefd){
    srand(time(NULL) + getpid()); 
    while (1)
    {
        int comando;
        read(readfd, &comando, sizeof(int));
        if(comando==1){
            int dado = jogar_dado();
            //pos_j2 += dado;
            write(writefd, &dado, sizeof(int));
            //printf("Jogador 2 está na posição %d\n", pos_j2);
        }
        
    }
}

void capturaTeclado(int id){
    char input[10];
    if(id==0){
        do {
            printf("Jogador 1, digite 'Y' para jogar o dado: ");
            fgets(input, sizeof(input), stdin);
        } while (input[0] != 'Y' && input[0] != 'y');
    }else{
        do {
            printf("Jogador 2, digite 'Y' para jogar o dado: ");
            fgets(input, sizeof(input), stdin);
        } while (input[0] != 'Y' && input[0] != 'y');
    }
}

int printBoard(){

}