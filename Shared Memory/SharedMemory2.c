#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define DharaNidhi "/tmp/DharaNidhi.txt"
#define KEY 1718920
#define shmsize sizeof(2550)
int main() {

        int shmid, n;
        char *shm;


if ((shmid = shmget(KEY, shmsize, IPC_CREAT | 0666)) == -1 ) {
        perror("shmget fail");
        exit(1);
}

if ((shm = (char *) shmat(shmid, 0, 0)) == (char *) -1) {
        perror("shmat fail");
        exit(2);
}
printf("Nidhi received by Dhara : %s",shm);
shmdt(shm);
}
