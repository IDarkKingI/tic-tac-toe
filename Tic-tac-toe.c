//tic-tac-toe


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

#define MAX_CELLS 9

int main(){
    struct sembuf sops;
    pid_t pid;                                                      //pid
    int shmid, semid;
    int x;
    shmid = shmget(IPC_CREAT, 2 * sizeof(int), IPC_CREAT | 0666);   //create shared memory
    semid = semget(IPC_CREAT, 1, IPC_CREAT | 0666);                 //create semaphore (man different?)
    if(shmid == -1){
		perror("shmget");
		return EXIT_FAILURE;
	}
    if(semid == -1){
        perror("semget");
		return EXIT_FAILURE;
    }
    semctl(semid, 0, SETVAL, (int)0);                               //control operation
    int* a = shmat(shmid, NULL, 0);                                 //link with shared memory
    a[0] = 0;
    while(1){                                        //a[0] = cells
        pid = fork();
        if(pid == -1){
            perror("fork");
		    _exit(EXIT_FAILURE);
        }
		if(pid == 0){
            sops.sem_op = 0;
            semop(semid, &sops, 1);
            printf("Enter number(row and collum), gamer - 1:\n");
            scanf("%d", &x);
            a[0]++;
            a[x] = 77;
            if(a[0] == 9){
                puts("Draw\n");
                for(int i = 11; i <= 33; i++){
                    a[i] = 0;
                }
                a[0] = 0;
            }
            if((a[11] == 77 && a[22] == 77 && a[33] == 77) || (a[13] == 77 && a[22] == 77 && a[31] == 77) || (a[11] == 77 && a[12] == 77 && a[13] == 77) || (a[21] == 77 && a[22] == 77 && a[23] == 77) || (a[31] == 77 && a[32] == 77 && a[33] == 77) || (a[11] == 77 && a[21] == 77 && a[31] == 77) || (a[12] == 77 && a[22] == 77 && a[32] == 77) || (a[13] == 77 && a[23] == 77 && a[33] == 77)){
                printf("Player 1 win\n");
                puts("");
                for(int i = 11; i <= 33; i++){
                    a[i] = 0;
                }
                a[0] = 0;
            }
            sops.sem_op = 1;
			semop(semid, &sops, 1);
		}
        pid = fork();
        if(pid == -1){
            perror("fork");
		    _exit(EXIT_FAILURE);
        }
        if(pid == 0){
            sops.sem_op = -1;
            semop(semid, &sops, 1);
            printf("Enter number(row and collum), gamer - 2:\n");
            scanf("%d", &x);
            a[0]++;
            a[x] = 88;
            if(a[0] == 9){
                puts("Draw\n");
                for(int i = 11; i <= 33; i++){
                    a[i] = 0;
                }
                a[0] = 0;
            }
            if((a[11] == 88 && a[22] == 88 && a[33] == 88) || (a[13] == 88 && a[22] == 88 && a[31] == 88) || (a[11] == 88 && a[12] == 88 && a[13] == 88) || (a[21] == 88 && a[22] == 88 && a[23] == 88) || (a[31] == 88 && a[32] == 88 && a[33] == 88) || (a[11] == 88 && a[21] == 88 && a[31] == 88) || (a[12] == 88 && a[22] == 88 && a[32] == 88) || (a[13] == 88 && a[23] == 88 && a[33] == 88)){
                printf("Player 2 win\n");
                puts("");
                for(int i = 11; i <= 33; i++){
                    a[i] = 0;
                }
                a[0] = 0;
            }
            sops.sem_op = 0;
			semop(semid, &sops, 1);
		}
        wait(NULL);
        wait(NULL);
    }
    return 0;
}