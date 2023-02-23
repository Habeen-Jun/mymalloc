#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <string.h>

#define MEMORY_SIZE 4096


// 1. specify the requirements your library must satisfy

// 2. describe how you could determine whether the requirements have been violated

// 3. write program to check those conditions

void *testcase1(int num_object, int size) {
// malloc() reserves unallocated memory

    // num_object = number of object that we want to test
    // size = size of the each object (size that we need for malloc())

    // creating new object
    void *object[num_object];

    // allocating the several objects
    for(int i = 0; i < num_object; i++) {
        object[i] = malloc(size);

        if(object[i] == NULL) {
            printf("The allocation failed! \n");
            return NULL;
        }
    }

    // fills each object with a distinct byte pattern
    for(int i = 0; i < num_object; i++) { // looping each object

        memset(object[i], i + 1, size);
        // writes i + 1 (first object will be 1, second = 2 etc ...) to all bytes of an object[i]
    }

    // check if the object still contains the written pattern
    for(int i = 0; i< num_object; i++){
        int* object_ptr = (int*)(object[i]);
        for(int j = 0; j < size; j++) {
            // if object does not have byte pattern print fail
            if(object_ptr[i][j] != i + 1) {
                printf("Object does not have correct byte pattern\n");
                return NULL;
            }
        }
    }


    // it frees the onject
    for(int i = 0; i < num_object; i++) {
        free(object[i]);
    }
    
    printf("Successfully done");
}

void *testcase2(void *pointer) {
    // free() deallocates memory
    
}


void main() {
    testcase1(3, 10);

}
