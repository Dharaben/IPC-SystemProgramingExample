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
int main()
{
     int i;
     printf("\n\n");
     printf("***********************************************\n");
     printf("*                                             *\n");
     printf("*                 Assignment-3                *\n");
     printf("*            SIGINT and SIGQUIT KILL          *\n");
     printf("*                   Program 1                 *\n");
     printf("*               Std_ID_# - 1820905            *\n");
     printf("*                                             *\n");
     printf("***********************************************\n\n\n");
     printf("\n-----------------------------------------------\n");

void signal_catcher(int);

   if (signal(SIGINT, signal_catcher) ==SIG_ERR)
   {
        perror("SIGINT");
        exit(1);
   }
if (signal(SIGQUIT, signal_catcher) ==SIG_ERR)
   {
        perror("SIGQUIT");
        exit(2);
   }
   for (i=0; ; ++i)
   {
        printf(" %i \n", i);
        sleep(1);
   }
}
void signal_catcher(int the_sig)
{
    signal(the_sig, signal_catcher); /*reset*/
    printf("\nSignal %d received.\n", the_sig);
    if (the_sig == SIGQUIT)
        exit(3);
}
/*--------------------------------------------------------------------------*/
