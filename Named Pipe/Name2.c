#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define DharaNidhi "/tmp/DharaNidhi"
int main()
{
  int i=0, pubFifo, stop = 0, result;
  char intStr1[PIPE_BUF];
  char intStr2[PIPE_BUF];
  printf("\n");
  printf("\n***********************************************\n");
  printf("*              Nidhi Chat Window                *\n");
  printf("\n***********************************************\n");

for(i=1; ; i++)
{
  sleep(1);
  if ((pubFifo=open(DharaNidhi, O_RDWR)) == -1)
  {
    perror("DharaNidhi");
    exit(1);
  }

   read(pubFifo, intStr1, PIPE_BUF);
   close(pubFifo);
   printf("\n Dhara: %s\t", intStr1);
   result = strcmp(intStr1, "Bye!");
   if(result == 0 && stop == 1)
   exit(5);
   stop=0;

   printf("\n Nidhi: ");
   scanf("%s", intStr2);
   result = strcmp(intStr2,"Bye!");
   if(result == 0)
   stop = 1;

   if ((pubFifo=open(DharaNidhi, O_RDWR)) == -1)
   {
        perror("DharaNidhi");
       exit(2);
    }
       write(pubFifo, intStr2, PIPE_BUF);
       close(pubFifo);
 }
   printf("\n");
   return 0;
}
