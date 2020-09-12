#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define THREAD_COUNT 50000

void *thread_loop(void *arg){
    int *is_looping = arg;
    while (*is_looping)
    {
        sleep(1);
    }
    return NULL;
}  

int main(void) {
    int i;
    int thread_count;
    pthread_t thread[THREAD_COUNT];
    int error_no;
    int is_looping = 1;

    for (i = 0; i < THREAD_COUNT; i++ ){
        usleep(1000);

        error_no = pthread_create(&thread[i], NULL, thread_loop, (void *)&is_looping);
        if (error_no != 0) {
            printf("Error: %s\n", strerror(error_no));
            break;
        }
        if ((i % 100) == 0) {
            printf("%d threads created.\n", i);
        }
    }
    thread_count = i;
    is_looping = 0;
    for(i=0; i < thread_count; i++){
        pthread_join(thread[i], NULL);
    }
    printf("Result: %d threads created.\n", thread_count);

    return 0;
}