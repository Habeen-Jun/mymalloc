#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <sys/time.h>

#define MEMORY_SIZE 4096
static char memory[MEMORY_SIZE];

// typedef struct header {
//     int size;
//     int is_free;
//     struct header *next;
// } header;

void* mymalloc(size_t size, char *file, int line)  {
    header *head = (header*) memory; 
    header *curr = head;
    
    while (curr) {
        if (curr->size == 0) {
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
            // printf("%s", "else if\n");
            printf("curr->size: %d\n", curr->size);
            printf("user requested size:%ld\n", size);
            

            int availabe_memory = curr->size;
            printf("available memory: %d\n", availabe_memory);


            header *new_chunk = (header*) ((void*) curr + sizeof(header) + size);
            curr->size = sizeof(header) + size;
            curr->is_free = 0;

            new_chunk->size = availabe_memory - sizeof(header) - size;
            new_chunk->is_free = 1; 

            curr->next = new_chunk;
            return (void*) curr + sizeof(header);

        } 
        curr = curr->next;
        
    }

    printf("no available space\n line number: %d\n", line);
    return NULL;
}

int detect_error(void *pointer) {
    // first header 
    header *head = (header*) memory; 
    header *ptr = head;
    
    while (ptr) {
        if (pointer == ptr && ptr->is_free == 0) {
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
    
    header *head = (header*) memory;

    // coalecsing
    while (head) {
        if (head->next != NULL) {
                if (head->is_free == 1 && head->next->is_free == 1) {
                    printf("%s\n", "coalescing");

                    // There is a dummy node that shouldn't be in the
                    // metadata linked list for some reasons.. handling this.
                    if (head->size + head->next->size >= 4080) {
                        head->next = NULL;
                        break;

                    }
                    head->size += (head->next->size);
                    
                    // printf("head->size: %d\n", head->size);
                    // printf("head->next->size: %d\n", head->next->size);
                    head->next = head->next->next;
                    return;
                    }
        }
        head = head->next;
    }

    return;
}
