/*-------------------------------Assignment-3-----------------------------------|
---------------------------------Program-1--------------------------------------|
------------------------------Std_ID_# - 1820905--------------------------------|
1. Develop a program that uses system call int kill(pid_t pid, int sig) to
deliver signal SIGINT and signal SIGHQUIT. Provide pid_t pid from command line
to the program. Let the process sleep 3 seconds between delivering signal SIGINT
and signal SIGHQUIT. Then run Program Example 4.4 at the end of Lecture 4 as a
background job. Use your program to deliver signal SIGINT and signal SIGHQUIT
to the process of Program Example 4.4.
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void sigint();
void sigquit();

int main(int argc, char* argv[])
{
        int pid;                           /* get child process */
        pid = atoi(argv[1]);

      //  signal(SIGINT,sigint);              /*function calls */
        //signal(SIGQUIT, sigquit);

        printf("***********************************************\n");
        printf("\n      Parent: sending SIGINT\n\n");
        printf("***********************************************\n");
        kill(pid,SIGINT);
        sleep(3);                         /* pause for 3 secs */

        printf("***********************************************\n");
        printf("\n      Parent: sending SIGQUIT\n\n");
        printf("***********************************************\n");
        kill(pid,SIGQUIT);
        sleep(3);

        return 0;
}
void sigint()
 {
   signal(SIGINT,sigint);                        /* reset signal */
   printf("\n Child: I have received a SIGINT\n");
 }

void sigquit()
 {
    printf("\n Killed Process!!!\n");
    exit(0);
 }
/*----------------------------------------------------------------------------*/
