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
        for(int j = 0; j < size; j++) {
            // if object does not have byte pattern print fail
            if(*((unsigned char*)object[i]+j) != i + 1) {
                printf("Object does not have correct byte pattern\n");
                return NULL;
            }
        }
    }


    // it frees the onject
    for(int i = 0; i < num_object; i++) {
        free(object[i]);
    }

    printf("Successfully done\n");
}

void *testcase2() {
    // 1) free() deallocates memory
    // 2) After freeing the data chunck, check if the "is_free" attribute of 
    //    header set to 1.
    // 3) Write a program that checks "is_free" header attribute of freed chunk. 
    void* test = malloc(100);
    free(test);

    // getting the chunk header from data pointer.
    header *curr = (header*) ((void*) test - sizeof(header));

    if (curr->is_free == 1) {
        printf("%s\n", "test case 2 passed");
    }
    

}


void main() {
    // testcase1(3, 10);
    testcase2();
}
