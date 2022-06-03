#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

float get_cpu_clock_speed()
{
     FILE* fp;
     char buffer[1024];
     size_t bytes_read;
     char* match;
     float clock_speed;

     fp = fopen("/proc/cpuinfo" , "r");


     bytes_read = fread(buffer,1 ,sizeof(buffer), fp);
     fclose(fp);
     printf("%ld  %ld\n", sizeof(buffer), bytes_read);

     if(bytes_read ==0 )
          return 0;

     //what is the need for this
     buffer[bytes_read] ='\0';

     match = strstr(buffer, "cpu MHz");
     if(match == NULL )
          return 0;


     sscanf(match ,"cpu MHz : %f" ,&clock_speed );
     return clock_speed;

}


pid_t get_pid_proc_self(){
     char target[32];
     int pid;
     readlink("/proc/self", target, sizeof(target) );
     sscanf(target, "%d", &pid);
     return (pid_t) pid;
}

int main ()
{
     printf("Cpu clock Speed %4.0f\n", get_cpu_clock_speed());
     printf("%d",(int)get_pid_proc_self());
     return 0 ;
}
