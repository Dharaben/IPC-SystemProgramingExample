
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define DharaNidhi "/tmp/DharaNidhi"

union semun {
   int val;
   struct semid_ds *buf;
   unsigned short *array;
};

struct sembuf acquire = { 0, -1, SEM_UNDO};
struct sembuf release = { 0, +1, SEM_UNDO};

int main(int argc,char *argv[])
{
        int  semID;
        char input[256];
        FILE *fptr;
        union semun arg;
        key_t key;
        key = ftok("/tmp/DharaNidhi1", 14);

        if ((semID = semget(key, 1, IPC_CREAT | 0666)) == -1) {
                perror("Sem Creation:");
                exit(1);
        }
        while(1)
        {
                printf("Waiting for Producer...\n");
                if (semop(semID, &acquire, 1) == -1) {
                        perror("Error acquiring lock:");
                        exit(3);
                }
                printf("Producer acquired!\n");
                if ((fptr = fopen(DharaNidhi, "a")) == NULL) {
                        perror(DharaNidhi);
                        exit(4);
                }
                printf("Enter String: ");
                scanf("%s", input);
                if(strcmp(input, "exit") == 0)
                {
                        fprintf(fptr, "Nidhi\n");
                        if(semop(semID, &release, 1) == -1) {
                                perror("Error releasing lock");
                                exit(5);
                        }
                        printf("Consumer released.\n");
                        break;
                }

                fprintf(fptr, "%s\n", input);
                fclose(fptr);
               if(semop(semID, &release, 1) == -1) {
                       perror("Error releasing lock");
                       exit(5);
               }
               printf("Consumer released.\n");
       }
       return 0;
}
