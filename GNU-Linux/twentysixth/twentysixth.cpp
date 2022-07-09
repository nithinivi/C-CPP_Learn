#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *print_function(void *temp) {
    printf("hello from worker thread\n");
    return 0;
}

int main(int argc, char const *argv[]) {
    pthread_t pth;

    //  create a thread and start the execution
    int re_val = pthread_create(&pth, NULL, print_function, 0);
    printf("hello from the main thread \n");

    pthread_join(pth, NULL);
    return 0;
}
