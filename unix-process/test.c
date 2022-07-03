#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
     printf("spawn from child process with PID %d \n", getpid());
     FILE *fp = fopen("output.txt", "w+");
     return 0;

}
