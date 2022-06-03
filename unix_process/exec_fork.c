#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(char *program, char **args_list)
{
     pid_t child_pid;
     child_pid = fork();

     if (child_pid <0)
          printf("Failure in fork");

     else if (child_pid == 0)
     {
          printf("Spawned child  %d\n" , getpid());

          char *args[] = {"./test", NULL};
          execv(args[0], args);

          fprintf(stderr, "an error occured in execvp \n");
          abort();
     }
     else
          printf("Parent Process \n");

     wait(2);

     return child_pid;
}

int main()
{

     // parent process
     char *args_list[] = {"test", "-l", "/", NULL};

     int pid = spawn("test", args_list);
     printf("end of main %d\n" , getpid());
     return 0;
}
