/*-------------------------------Assignment-4-----------------------------------|
---------------------------------Program-1--------------------------------------|
------------------------------Std_ID_# - 1820905--------------------------------|
1. This is a team assignment. Two students are in one team. Develop two programs
 that share named pipe. Use the program to chat. One user enters “Hello!” Then
 the other can “Hello!” back.  The conversation ends when two users say “Bye!”
 to each other.
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#define DharaNidhi "/tmp/DharaNidhi"
int main()
{
int i=0,pubFifo,result=0, stop = 0;
char intStr1[PIPE_BUF];
char intStr2[PIPE_BUF];
  printf("\n");
  printf("***********************************************\n");
  printf("*            Dhara Chat Window                *\n");
  printf("***********************************************\n");


if(mknod(DharaNidhi, S_IFIFO | 0666, 0) == -1)
{
        perror("Named Pipe Creation Failed");
//      exit(1);
}

if ((pubFifo=open(DharaNidhi, O_RDWR))== -1)
{
      perror("DharaNidhi");
      exit(2);
}

for(i=0; ; i++)
{
  printf("\n Dhara: ");
  scanf("%s", intStr1);
  result =  strcmp(intStr1 , "Bye!");
  if(result == 0)
  stop = 1;

     if ((pubFifo= open(DharaNidhi, O_RDWR)) == -1)
     {
        perror("DharaNidhi");
        exit(2);
     }

     write(pubFifo, intStr1, PIPE_BUF);
     close(pubFifo);
     
     sleep(1);

    if ((pubFifo= open(DharaNidhi, O_RDWR)) == -1)
    {
        perror("DharaNidhi");
        exit(1);
     }
     read(pubFifo, intStr2, PIPE_BUF);
     close(pubFifo);

     printf("\n Nidhi: %s\t", intStr2);
     result = strcmp(intStr2 , "Bye!");
     if(result == 0 && stop == 1)
     exit(4);
     stop = 0;
 }
  printf("\n");
  return 0;
}
