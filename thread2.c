#include <pthread.h>
#include <stdio.h>

typedef struct bound {
    int low;
    int high;
} bound;

int a[] = {5,6,1,2,3,7,4,8,9,0,11,10};
int size = 12;

void* merge_sort(void* arg) {
    bound limits = *((bound *)arg);
    int low = limits.low;
    int high = limits.high;

    // If the size is one, don't do anything
    if (low == high) {
        return;
    }
    // If the size of the array is 2 or more
    // Then break the range into two parts

    int mid = (low + high) / 2;

    // Create two threads to assign the task of 
    // sorting the two halfs of the array

    bound left = {.low=low, .high=mid};
    bound right = {.low=mid+1, .high=high};

    pthread_t left_thread, right_thread;
    
    if (pthread_create(&left_thread, NULL, merge_sort, &left)) {
        printf("Error in creating the thread at point %d %d\n", low, mid);
    }
    if (pthread_create(&right_thread, NULL, merge_sort, &right)) {
        printf("Error in creating the thread at point %d %d\n", mid+1, high);
    }
    
    // Wait for both the threads to complete
    pthread_join(left_thread, NULL);
    pthread_join(right_thread, NULL);

    // Now combine the two sorted sub-halfs into sorted array
    // Note: This can be done inplace also.
    
    //Create a temporary array to hold the sorted array
    int temp_size = high - low + 1;
    int temp[temp_size];

    int left_index = low;
    int right_index= mid+1;
    for (int i = 0; i < temp_size; i++) {
        if (left_index <= mid && right_index <= high) {
            if (a[left_index] < a[right_index]) {
                temp[i] = a[left_index];
                left_index++;
            } else {
                temp[i] = a[right_index];
                right_index++;
            }
        } else {
            if (left_index <= mid) {
                temp[i] = a[left_index++];
            } else {
                temp[i] = a[right_index++];
            }
        }
    }

    // Copy the temp array to the original array
    for (int i = 0; i < temp_size; i++) {
        a[low+i] = temp[i];
    } 
}

int main(void) {
    pthread_t mythread;
    bound initial = {.low=0, .high=size-1};

    // Call merge sort on the entire array
    merge_sort(&initial);

    // Print the sorted array
    for (int i = 0 ; i < size; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}
