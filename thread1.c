#include <pthread.h> // pthread_create and pthread_join
#include <stdio.h>  // printf
#include <unistd.h> // sleep function

int num_threads = 10;
int thread_num[10];

void* thread_function(void* arg) {
    int t= *(int *)(arg);
    printf("Hi from thread %d\n", t);
}

int main(void) {
    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; i++) {
        thread_num[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_num[i])) {
            printf("Error in creating thread %d\n", i);
        }
    }
    for (int i = 0; i < num_threads; i++) {
        if(pthread_join(threads[i], NULL)) {
            printf("Error in joining thread %d\n", i);
        }
        
    }
    return 0;


}
