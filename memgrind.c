#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include "mymalloc.h"

double test_performance1() {
    /*
    malloc() and immediately free() a 1-byte chunk, 120 times. 
    */
    struct timeval start_time, end_time;
    // Get the start time
    gettimeofday(&start_time, NULL);
    for (int i=0; i < 120; i++) {
        void *test = malloc(1);
        free(test);
    }
    // Get the end time
    gettimeofday(&end_time, NULL);

    // Calculate the elapsed time in microseconds
    long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 +
                        (end_time.tv_usec - start_time.tv_usec);
    
    // Convert elapsed time to seconds, if desired
    double elapsed_time_sec = (double) elapsed_time / 1000000.0;
    
    // Print the elapsed time
    printf("Elapsed time: %ld microseconds (%f seconds)\n", elapsed_time, elapsed_time_sec);
    return elapsed_time_sec;
}

double test_performance2() {
    /*
    Use malloc() to get 120 1-byte chunks, storing the pointers in an array,
    then use free() to deallocate the chuncks. 
    */
    struct timeval start_time, end_time;
    // Get the start time
    gettimeofday(&start_time, NULL);

    void* arr[120];

    for (int i=0; i < 120; i++) {
        void *test = malloc(1);
        arr[i] = test;
    }

    for (int i=0; i < 120; i++) {
        free(arr[i]);
    }
    // Get the end time
    gettimeofday(&end_time, NULL);

    // Calculate the elapsed time in microseconds
    long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 +
                        (end_time.tv_usec - start_time.tv_usec);
    
    // Convert elapsed time to seconds, if desired
    double elapsed_time_sec = (double) elapsed_time / 1000000.0;
    
    // Print the elapsed time
    printf("Elapsed time: %ld microseconds (%f seconds)\n", elapsed_time, elapsed_time_sec);
    return elapsed_time_sec;
}

void allocate_1byte_chunck_in_arr(void **arr, int index) {
    /*
    Helper function for test_performance3
    Allocating a 1-byte chunk and storing the pointer in an array 
    */
    void *test = malloc(1);
    arr[index] = test;
    return;
}

void deallocate_chunck_in_arr(void **arr, int index) {
    /*
    Helper function for test_performance3
    Deallocating one of the chuncks in the array (if any) 
    */
    free(arr[index]);
    return;
}

double test_performance3() {
    /*
    Randomly choose between
        * Allocating a 1-byte chunck and storing the pointer in an array
        * Deallocating one of the chunks in the array (if any)
    Repeat until you have called malloc() 120 times, the free all remaining 
    allocated chuncks.
    */
    struct timeval start_time, end_time;
    // Get the start time
    gettimeofday(&start_time, NULL);

   int malloc_called_times = 0;
   void* arr[120];
   int arr_c_idx = 0;

    while (1) {
        // printf("%s\n", "while looping..");
        // printf("malloc called times %d\n", malloc_called_times);
        if (malloc_called_times == 120) {
            break;
        }

        bool randbool = rand() & 1; // get LSB of randomly generated number
        // printf("rand bool: %d\n", randbool);

        if (arr_c_idx == -1) {
            arr_c_idx += 1;
            allocate_1byte_chunck_in_arr(arr, arr_c_idx);
            
            malloc_called_times += 1;
        }
        else if (randbool == true) {
            arr_c_idx += 1;
            allocate_1byte_chunck_in_arr(arr, arr_c_idx);
            malloc_called_times += 1;
        } else {
            if (arr_c_idx >= 0) {
                deallocate_chunck_in_arr(arr, arr_c_idx);
                arr_c_idx -= 1;
            }
        }
    }
    
    // Get the end time
    gettimeofday(&end_time, NULL);

    // Calculate the elapsed time in microseconds
    long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 +
                        (end_time.tv_usec - start_time.tv_usec);

    // Convert elapsed time to seconds, if desired
    double elapsed_time_sec = (double) elapsed_time / 1000000.0;

    // Print the elapsed time
    printf("Elapsed time: %ld microseconds (%f seconds)\n", elapsed_time, elapsed_time_sec);

    // freeing all remaining allocated chuncks
    for (int i = 0; i < arr_c_idx; i++) {
        free(arr[i]);
    }
    return elapsed_time_sec;
}

double test_performance4() {
    /*
    malloc() and immediately free() a 1000-byte chunk, 120 times. 
    */
    struct timeval start_time, end_time;
    // Get the start time
    gettimeofday(&start_time, NULL);

    // testcase here
    for (int i=0; i < 120; i++) {
        void *test = malloc(1000);
        free(test);
    }

    // Get the end time
    gettimeofday(&end_time, NULL);

    // Calculate the elapsed time in microseconds
    long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 +
                        (end_time.tv_usec - start_time.tv_usec);

    // Convert elapsed time to seconds, if desired
    double elapsed_time_sec = (double) elapsed_time / 1000000.0;

    // Print the elapsed time
    printf("Elapsed time: %ld microseconds (%f seconds)\n", elapsed_time, elapsed_time_sec);


    return elapsed_time_sec;
}

double test_performance5() {
    /*
    Use malloc() to get 8 512-byte chunks (this will reach the full memory capacity 8*512=4096), 
    storing the pointers in an array,
    then use free() to deallocate the chuncks. 
    */
    struct timeval start_time, end_time;
    // Get the start time
    gettimeofday(&start_time, NULL);

    // testcase here

    void* arr[8];

    for (int i=0; i < 8; i++) {
        void *test = malloc(512);
        arr[i] = test;
    }

    for (int i=0; i < 8; i++) {
        free(arr[i]);
    }

    
    // Get the end time
    gettimeofday(&end_time, NULL);

    // Calculate the elapsed time in microseconds
    long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 +
                        (end_time.tv_usec - start_time.tv_usec);

    // Convert elapsed time to seconds, if desired
    double elapsed_time_sec = (double) elapsed_time / 1000000.0;

    // Print the elapsed time
    printf("Elapsed time: %ld microseconds (%f seconds)\n", elapsed_time, elapsed_time_sec);

    return elapsed_time_sec;
}

void test_object_overlap() {
    // Condition
    // "When successful, malloc() returns a pointer to an object that does not
    // overlap with any other allocated object."
    // Looping through the metadata linked list, chec
}

void execute_performance_tests() {
    double elapsed_time;
    double total_elapsed_time = 0;

    printf("%s","testing test_performance1...");

    for (int i = 0; i < 50; i++) {
        elapsed_time = test_performance1();
        total_elapsed_time += elapsed_time;
    }
    printf("average elapsed time for test_performance1: %f\n", total_elapsed_time / 50);

    total_elapsed_time = 0;

    printf("%s","testing test_performance2...\n");

    for (int i = 0; i < 50; i++) {
        elapsed_time = test_performance2();
        total_elapsed_time += elapsed_time;
    }
    printf("average elapsed time for test_performance2: %f\n", total_elapsed_time / 50);

    total_elapsed_time = 0;
    printf("%s","testing test_performance3...\n");

    for (int i = 0; i < 50; i++) {
        elapsed_time = test_performance3();
        total_elapsed_time += elapsed_time;
    }
    printf("average elapsed time for test_performance3: %f\n", total_elapsed_time / 50);

    total_elapsed_time = 0;
    printf("%s","testing test_performance4...\n");

    for (int i = 0; i < 50; i++) {
        elapsed_time = test_performance4();
        total_elapsed_time += elapsed_time;
    }
    printf("average elapsed time for test_performance4: %f\n", total_elapsed_time / 50);


    total_elapsed_time = 0;
    printf("%s","testing test_performance5...\n");

    for (int i = 0; i < 50; i++) {
        elapsed_time = test_performance5();
        total_elapsed_time += elapsed_time;
    }
    printf("average elapsed time for test_performance5: %f\n", total_elapsed_time / 50);
}

void main() {
    execute_performance_tests();
}   