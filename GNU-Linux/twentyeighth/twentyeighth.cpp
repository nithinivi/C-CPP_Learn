#include <cstddef>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// a global variable
int Counter = 0;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
void *print_function(void *temp) {
    // guarded area
    pthread_mutex_lock(&m1);
    Counter++;
    pthread_mutex_unlock(&m1);
    int s = *((int *)temp);
    printf("print from worker thread %d \n ", s);
    return 0;
}

int main(int argc, char *argv[]) {
    pthread_t th1;
    pthread_t th2;
    
    int param = 100;
    int re_val = pthread_create(&th1, NULL, print_function, (void *)&param);

    int param2 = 200;
    int re_val2 = pthread_create(&th2, NULL, print_function, (void *)&param2);

    
    pthread_join(th1, NULL);
    pthread_join(th1, NULL);

    printf("Hello from the mail thread %d \n", Counter);
    return 0;
}
