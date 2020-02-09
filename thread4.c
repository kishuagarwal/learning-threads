#include <pthread.h>
#include <stdio.h> 

int x = 0;
pthread_mutex_t x_mutex;

void* thread_function(void* arg) {
    for (int c = 0; c < 1000000; c++) {
        pthread_mutex_lock(&x_mutex);
        int i = x;
        i = i + 1;
        x = i;
        pthread_mutex_unlock(&x_mutex);
    }
}

int main(void) {
    pthread_t thread;

    pthread_mutex_init(&x_mutex, NULL);

    if (pthread_create(&thread, NULL, thread_function, NULL)) {
        printf("Error in creating thread \n");
    }
    for (int c=  0; c < 1000000; c++) {
        pthread_mutex_lock(&x_mutex);
        x = x + 1;
        pthread_mutex_unlock(&x_mutex);
    }
    if(pthread_join(thread, NULL)) {
        printf("Error in joining thread\n");
    }
    pthread_mutex_destroy(&x_mutex);
    printf("Final value of x is %d", x);
    return 0;
}
