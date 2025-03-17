#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getString() {
    char* ret = malloc(100 * sizeof(char));
    if (ret == NULL) {
        printf("Allocation failed!\n");
        return NULL;
    }
    strcpy(ret, "Hello World!");
    return ret;
}

void program4() {
    char* str = getString();
    if (str) {
        printf("String: %s\n", str);
        free(str);
    }
}

int main() {
    program4();
}

