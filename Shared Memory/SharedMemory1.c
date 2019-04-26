/*-------------------------------Assignment-6-----------------------------------|
------------------------------Std_ID_# - 1820905--------------------------------|
Two students team up. Develop a program that creates a shared memory segment and
reads contents from a file to the shared memory segment. Develop the other
program that reads from the shared memory segment and outputs what it reads.
Note that you prepare a plain text file for testing.h
------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>

#define DharaNidhi "/tmp/DharaNidhi.txt"
#define KEY 1718920
#define shmsize sizeof(2550)

int main() {
        int i;
        int shmid;
        int n,fd;
        FILE *fp;
        char *shm;

        fd= open("/tmp/DharaNidhi.txt", O_RDONLY);
        if(fp == NULL) {
                perror("File cannot open");
                return(1);
        }

        if((shmid = shmget(KEY, shmsize, IPC_CREAT | 0666)) == -1) {
                perror("shmget fail");
                exit(1);
        }

        if((shm = (char *) shmat(shmid, 0, 0)) == (char *) -1) {
                perror("shmat fail");
                exit(2);
        }
        printf("\n");
        n = read(fd, shm, 2550);

        shmdt(shm);
        shmctl(shmid, IPC_RMID, (struct shmid_ds *) 0);
}
