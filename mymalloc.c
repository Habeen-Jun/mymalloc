#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 4096
static char memory[MEMORY_SIZE];

typedef struct header {
    int size;
    int is_free;
    struct header *next;
} header;


void mymalloc(int size) {
    
    head = (header*) memory; 

    header *curr = head;

    while (curr) {
        if (curr->size == NULL) {
            // first call 
            curr->size = MEMORY_SIZE - sizeof(header) - size;
            curr->is_free = 0;

            header *new_chunk = (header*) (curr + sizeof(header) + size);
            new_chunk->size = MEMORY_SIZE - curr->size;
            new_chunk->is_free = 1;

            curr->next = new_chunk;
            
        }
        else if (curr->size >= size + sizeof(header) && curr->is_free == 1) {
            // reqeuested bytes are available to use
            header *new_chunk = (header*) (curr + sizeof(header) + size);

            curr->next = new_chunk;
            curr->size = size + sizeof(header);

            new_chunk->size = MEMORY_SIZE - sizeof(header) - ;
            new_chunk->is_free = 1; 

            curr = new_chunk;

        } else {
            // no available space 
        }

        curr = curr->next;
    }


    
    header *ptr;
    printf("%d", ptr->size);

    

    // header contains
    // 1) the size of the chunck
    // 2) whether the chunk is allocated of free 



}

void myfree(int *pointer) {
    return ;
}

void main() {
    mymalloc(3);
}