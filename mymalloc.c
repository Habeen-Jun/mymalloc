#include <stdio.h>

static char memory[4096];


void mymalloc(int size) {

    // header contains
    // 1) the size of the chunck
    // 2) whether the chunk is allocated of free (use the last bit)
    // instead of using two bytes 

    char byte = memory[0];
    byte = size;
    int i;
    int last_bit = byte & 1;

    for(i = 7; 0 <= i; i --)
        printf("%d\n", (byte >> i) & 0x01);
    printf("%d\n", byte & 1);
    // last_bit = 1;

    

    // printf("%d\n", byte);
    // printf("%d\n", byte & 1);
    //return pointer;
}

void myfree(int *pointer) {
    return ;
}

void main() {
    mymalloc(3);
}