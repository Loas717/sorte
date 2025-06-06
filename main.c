#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define MAX 10

int jogar_dado();
void jogador1(int readfd, int writefd), jogador2(int readfd, int writefd), capturaTeclado(int id);
void* contador_tempo(void* arg);

int pos_j1=0, pos_j2=0, tabuleiro[MAX];
int segundos = 0;
int minutos = 0;
int tempo_rodando = 1;

int main(){
    srand(time(NULL) + getpid());
    int pipe_j1[2], pipe_j2[2], pipe_j1_s[2], pipe_j2_s[2], descritorj1, descritorj2;
    int quem_comeca = rand() % 2; // 0 = jogador1, 1 = jogador2
    pthread_t thread_tempo;
    if (pthread_create(&thread_tempo, NULL, contador_tempo, NULL) != 0) {
        printf("Erro na chamada thread");
        exit(1);
    }
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
            if(pos_j1>MAX){
                pos_j1=MAX;
            }
            printf("Jogador 1 tirou %d e foi para posição %d\n", dado, pos_j1);
            if(pos_j1>=MAX){
                printf("Jogador 1 venceu!\n");
                break;            
            }

            capturaTeclado(j_2);
            write(pipe_j2_s[1],&j_2,sizeof(int));
            read(pipe_j2[0], &dado,sizeof(int));
            pos_j2+=dado;
            if(pos_j2>MAX){
                pos_j2=MAX;
            }
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
            if(pos_j2>MAX){
                pos_j2=MAX;
            }            
            printf("Jogador 2 tirou %d e foi para posição %d\n", dado, pos_j2);
            if(pos_j2>=MAX){
                printf("Jogador 2 venceu!\n");
                break;               
            }

            capturaTeclado(j_1);
            write(pipe_j1_s[1],&j_1,sizeof(int));
            read(pipe_j1[0], &dado,sizeof(int));
            pos_j1+=dado;
            if(pos_j1>MAX){
                pos_j1=MAX;
            }
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
    tempo_rodando = 0;
    pthread_join(thread_tempo, NULL);
    printf("\nTempo total de execução: %d minutos e %d segundos\n", segundos / 60, segundos % 60);
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
    char input;
    if(id==0){
        printf("Jogador 1, digite 'Y' para jogar o dado: ");
        do {
            scanf("%c",&input);
        } while (input != 'Y' && input != 'y');
    }else{
        printf("Jogador 2, digite 'Y' para jogar o dado: ");
        do {
            scanf("%c",&input);
        } while (input != 'Y' && input != 'y');
    }
}

void* contador_tempo(void* arg) {
    while (tempo_rodando) {
        sleep(1);
        segundos++;
    }
    pthread_exit(NULL);
}
