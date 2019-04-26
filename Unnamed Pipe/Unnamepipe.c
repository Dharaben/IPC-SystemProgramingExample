/*-------------------------------Assignment-3-----------------------------------|
---------------------------------Program-2--------------------------------------|
------------------------------Std_ID_# - 1820905--------------------------------|
2. Modify Program 5.2 in Lecture 5 so that three commands, last, sort, and more
can be passed to the program from command line.  Each command passed to the
 program should be connected to the next command via a pipe. When use this new
program a three-command sequence such as:

%last | sort | more would be indicated as:
% ./a.out    last    sort    more
when running your program.
------------------------------------------------------------------------------*/

/*
*A last | sort command pipeline
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{

     printf("\n\n");
     printf("***********************************************\n");
     printf("*                                             *\n");
     printf("*                 Assignment-3                *\n");
     printf("*            Modify program 5.2               *\n");
     printf("*                   Program 2                 *\n");
     printf("*               Std_ID_# - 1820905            *\n");
     printf("*                                             *\n");
     printf("***********************************************\n\n\n");
     printf("\n------------------------------------------------------------------------\n");

if(argc!=4)
{
  fprintf(stderr, "Usage: %s  *Three command are required [last sort more] !!* \n",argv[0]);
  printf("----------------------------------------------------------------------\n");
  exit(1);

}

int f_des[2];
int f_Des[2];

if (pipe(f_des) == -1)
{
    perror("Pipe");
    exit(2);
}

if (pipe(f_Des) == -1)
{
    perror("Pipe");
    exit(3);
}


switch (fork())
{
    case -1:
             perror("Fork");
             exit(4);
    case 0:                                          /*In the 1st child process */
            dup2(f_des[1], fileno(stdout));         //copy f_des[1] into stdout
            close(f_des[0]);                        // close f_des[0] read end of Pipe
            close(f_des[1]);                       //close f_des[1]  write end of Pipe
            close(f_Des[0]);                       // close f_des[0] read end of Pipe
            close(f_Des[1]);
             execlp(argv[1],argv[1],(char *) 0); // execl command "last"
            exit(5);
     default:

switch(fork())
{
    case -1:
            perror("Fork");
            exit(6);
    case 0:                                         /*In the 2st child process */
            dup2(f_des[0], fileno(stdin));         //copy f_des[0] into stdin
            close(f_des[0]);                       // close f_des[0] read end of Pipe
            close(f_des[1]);                       //close f_des[1]  write end of Pipe
            dup2(f_Des[1],fileno(stdout));
            close(f_Des[0]);
            close(f_Des[1]);
            execlp(argv[2],argv[2], (char *) 0);   // execl command  "sort"
            exit(7);
   default:
             dup2(f_Des[0], fileno(stdin));
            close(f_des[0]);                      // close f_des[0] read end of Pipe
            close(f_des[1]);                      //close f_des[1]  write end of Pipe
            close(f_Des[0]);
            close(f_Des[1]);
            execlp(argv[3],argv[3], (char *) 0);   // execl command "more"
            exit(8);
       }
   }
   return 0;
 }

/*-----------------------------------------------------------------------------*/
