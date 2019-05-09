/*-------------------------------Assignment-5-----------------------------------|
------------------------------Std_ID_# - 1820905--------------------------------|
Descriptions:
Two students team up to develop two programs, one for each. The two programs
share a critical resource, a Printer (Let’s simulate it by using a file.). This
file only allows one process to access it at a time. Therefore a semaphore is
used to control the access to the file. The two programs firstly gain access
to the file through the semaphore. Once gaining the access, the programs open
the file with appending mode and write something that is from command line.
Afterwards write your name to the file. Then release the resource and exit.

Due Date: Demo your program in our class’ lab session on 04/23/2019.
------------------------------------------------------------------------------*/

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
        arg.val = 1;
        if(semctl(semID, 0, SETVAL, arg) == -1) {
                perror("semctl:");
                exit(2);
        }
        while(1)
        {
               printf("Waiting for Consumer...\n");
              if (semop(semID, &acquire, 1) == -1) {
                       perror("Error acquiring lock:");
                       exit(3);
               }
               printf("Consumer acquired!\n");
               if ((fptr = fopen(DharaNidhi, "a")) == NULL) {
                       perror(DharaNidhi);
                       exit(4);
               }
               printf("Enter String: ");
               scanf("%s", input);
               if(strcmp(input, "exit") == 0)
                {
                       fprintf(fptr, "Dhara\n");
                       fclose(fptr);
                       if(semop(semID, &release, 1) == -1) {
                               perror("Error releasing lock");
                               exit(5);
                       }
                       printf("Producer released.\n");
                       break;
               }
               fprintf(fptr, "%s\n", input);
               fclose(fptr);
               if(semop(semID, &release, 1) == -1) {
                       perror("Error releasing lock");
                       exit(5);
               }
               printf("Producer released.\n");
       }
       return 0;
}
