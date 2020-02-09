#include <pthread.h> // pthread_create and pthread_join
#include <stdio.h>  // printf

int x = 0;

void* thread_function(void* arg) {
    for (int c = 0; c < 1000000; c++) {
        int i = x;
        i = i + 1;
        x = i;
    }
}

int main(void) {
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_function, NULL)) {
        printf("Error in creating thread \n");
    }
    for (int c=  0; c < 1000000; c++) {
        x = x + 1;
    }
    if(pthread_join(thread, NULL)) {
        printf("Error in joining thread\n");
    }
    printf("Final value of x is %d", x);
    return 0;
}
