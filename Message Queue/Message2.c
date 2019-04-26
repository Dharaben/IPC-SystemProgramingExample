/*-------------------------------Assignment-4-----------------------------------|
---------------------------------Program-2--------------------------------------|
------------------------------Std_ID_# - 1820905--------------------------------|
2. The two students continue to develop another version of the chatting programs
that share a message queue.
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGSZ  128

/*
* Declare the message structure.
*/

typedef struct msgbuf
 {
        long    mtype;
        char    mtext[MSGSZ];
} message_buf;

int  main()
{
        int mid;
        key_t key;
        message_buf sendbuf;
        message_buf recbuf;
        size_t buf_length;
        key = ftok("/tmp/DharaNidhi", 'p');

        printf("\n");
        printf("***********************************************\n");
        printf("*            Nidhi Chat Window                *\n");
        printf("***********************************************\n");

       if((mid = msgget(key,IPC_CREAT | 0666)) < 0)
        {
                perror("MS Queue Creation");
                exit(1);
        }
        while(1)
          {
                sleep(1);
                if(msgrcv(mid, &recbuf, MSGSZ, 1, 0) < 0)
                {
                        perror("message Receive");
                        exit(1);
                }
                  else
                        printf("\nDhara :%s", recbuf.mtext);

                sendbuf.mtype = 2;
                printf("\n Enter 'Bye!' to colse connection :");
                scanf("%s",&sendbuf.mtext);


        sleep(1);
       if(strcmp(sendbuf.mtext,"Bye!")==0)
        {
         strcpy(sendbuf.mtext,"Bye!");
         buf_length = strlen(sendbuf.mtext) + 1 ;
         if (msgsnd(mid, &sendbuf, buf_length, IPC_NOWAIT) < 0)
          {
                               printf ("%d, %d, %s, %d\n", mid, sendbuf.mtype, sendbuf.mtext, buf_length);
                               perror("Message Send");
                               exit(1);
          }
                          // msgctl(mid, IPC_SET, &buf);
                          //msgctl(mid,IPC_STAT,&buf);
                          msgctl(mid, IPC_RMID, NULL);
                       break;
       }
        else
               buf_length = strlen(sendbuf.mtext) + 1 ;
               if (msgsnd(mid, &sendbuf, buf_length, IPC_NOWAIT) < 0)
                {
                       printf ("%d, %d, %s, %d\n", mid, sendbuf.mtype, sendbuf.mtext, buf_length);
                       perror("msgsnd");
                       exit(1);
               }else
                       printf("Nidhi :%s", sendbuf.mtext);
       }
       exit(0);
       return 0;
}
