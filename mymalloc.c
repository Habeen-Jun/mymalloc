#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <sys/time.h>

#define MEMORY_SIZE 4096
static char memory[MEMORY_SIZE];

typedef struct header {
    int size;
    int is_free;
    struct header *next;
} header;

void* mymalloc(size_t size, char *file, int line)  {
    header *head = (header*) memory; 
    header *curr = head;
    
    printf("malloc called! requested size: %ld\n", size);
    printf("line number: %d", __LINE__);
    while (curr) {
        printf("current size: %d is_free: %d\n", curr->size, curr->is_free);
        if (curr->size == 0) {
            printf("%s", "if\n");
            // first call 
            printf("%s", "firstcall\n");
            curr->size = size + sizeof(header);
            curr->is_free = 0;
            header *new_chunk = (header*) ((void*) curr + sizeof(header) + size); // curr (first memory address of curr) + sizeof(header) + size (requested size) 
            new_chunk->size = MEMORY_SIZE - sizeof(header) - size;
            printf("new chunk memory size: %d\n", new_chunk->size);
        
            new_chunk->is_free = 1;
            curr->next = new_chunk;

            return (void*) curr + sizeof(header);
        }
        else if (curr->size >= size + sizeof(header) && curr->is_free == 1) {
            printf("%s", "else if\n");
            // reqeuested bytes are available to use
            // printf("%s", "not firstcall\n");
            int availabe_memory = curr->size;
            printf("available memory: %d\n", availabe_memory);

            header *new_chunk = (header*) ((void*) curr + sizeof(header) + size);
            printf("address of new chunk: %p\n", new_chunk);
            curr->size = sizeof(header) + size;
            curr->is_free = 0;
            printf("curr->next: %p\n", curr->next);

            printf("new chunck size should be: %ld\n", availabe_memory - sizeof(header) - size);
            printf("new chunck -> is_free %d\n", new_chunk->is_free);
            new_chunk->size = availabe_memory - sizeof(header) - size;
            printf("new chunk memory size: %d\n", new_chunk->size);

            new_chunk->is_free = 1; 
            new_chunk->next = curr->next; // new chunk points to NULL
            
            curr->next = new_chunk;

            return (void*) curr + sizeof(header);

        } 
        curr = curr->next;
    }

    printf("no available space\n line number: %d\n", line);
}

int detect_error(void *pointer) {
    // first header 
    header *head = (header*) memory; 
    header *ptr = head;
    
    while (ptr) {
        if (pointer == ptr && ptr->is_free == 0) {
            printf("address of user_pointer: %p\n", pointer);
            printf("address of current_pointer: %p\n", ptr);
            return 1;
        }

        ptr = ptr->next;
    }
    
    return -1;
}

void myfree(void *pointer, char *file, int line) {
    // getting the chunk header from data pointer.
    header *curr = (header*) ((void*) pointer - sizeof(header));
    int result = detect_error(curr);
    if (result == -1) {
        printf("error while freeing pointer\n line number: %d\n", line);
        return;
    }

    curr->is_free = 1;

    // coalecsing
    while (curr) {
        if (curr->next != 0) {
                if (curr->is_free == 1 && curr->next->is_free == 1) {
                    curr->size += (sizeof(header) + (curr->next->size));
                    curr->next = curr->next->next;
                    }
        }
        
        curr = curr->next;
    }

    return;
}

void main() {
    // void *test = malloc(1);
    // free(test);
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
    

    // void *test = malloc(10); // 1
    // void *test1 = malloc(10); // 2
    // void *test2 = malloc(10);
    // void *test3 = malloc(400);
    // void *test4 = malloc(400);
    // void *test5 = malloc(2000);

    // int x;
    // free(test5);
}