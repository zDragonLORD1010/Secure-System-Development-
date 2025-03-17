#include <stdio.h>
#include <stdlib.h>

void* program3(unsigned N) {
    void *arr = malloc(N * sizeof(char));
    if ((N < 1) || (arr == NULL)) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    printf("Memory allocation success!\n");
    return arr;
}

int main() {
    void* arr = program3(4);
    if (arr) {
        free(arr);
    }
}

