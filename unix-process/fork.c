#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
     pid_t child_pid;
     printf("the main process id %d \n", (int) getpid());

     child_pid = fork();

     if(child_pid ==0)
     {
          printf("parent" );
          printf("this is the parent process id %d \n" ,(int) getpid());
          printf("this is the child process id %d \n" ,(int) child_pid);
     }
     else
       printf("This is the child process with id %d \n", (int) getpid());
}


