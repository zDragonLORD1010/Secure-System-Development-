#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// Returns the index where the key should be stored
int HashIndex(const char* key) {
    int sum = 0;
    for (const char* c = key; *c != '\0'; c++) {
        sum += *c;
    }
    return sum % MAP_MAX;
}

// Allocates memory for the HashMap
HashMap* HashInit() {
    return calloc(1, sizeof(HashMap));
}

// Inserts PairValue into the map, if the value exists, increase ValueCount
void HashAdd(HashMap *map, PairValue *value) {
    if (!map || !value) return;
    int idx = HashIndex(value->KeyName);
    if (map->data[idx] != NULL) {
        value->Next = map->data[idx];
    }
    map->data[idx] = value;
}

// Returns PairValue from the map if a given key is found
PairValue* HashFind(HashMap *map, const char* key) {
    if (!map || !key) return NULL;
    unsigned idx = HashIndex(key);
    for (PairValue* val = map->data[idx]; val != NULL; val = val->Next) {
        if (strcmp(val->KeyName, key) == 0) {
            return val;
        }
    }
    return NULL;
}

// Deletes the entry with the given key from the map
void HashDelete(HashMap *map, const char* key) {
    if (!map || !key) return;
    unsigned idx = HashIndex(key);
    PairValue *val = map->data[idx], *prev = NULL;
    while (val != NULL) {
        if (strcmp(val->KeyName, key) == 0) {
            if (prev)
                prev->Next = val->Next;
            else
                map->data[idx] = val->Next;
            free(val);
            val = NULL;
            return;
        }
        prev = val;
        val = val->Next;
    }
}

// Prints all content of the map
void HashDump(HashMap *map) {
    if (!map) return;
    for (unsigned i = 0; i < MAP_MAX; i++) {
        for (PairValue* val = map->data[i]; val != NULL; val = val->Next) {
            printf("%s\n", val->KeyName);
        }
    }
}


int main() {
    HashMap* map = HashInit();
    if (!map) {
        printf("Failed to initialize HashMap\n");
        return EXIT_FAILURE;
    }
    printf("HashInit() Successful\n");

    PairValue* pv1 = malloc(sizeof(PairValue));
    strcpy(pv1->KeyName, "test_key");
    pv1->ValueCount = 1;
    pv1->Next = NULL;

    PairValue* pv2 = malloc(sizeof(PairValue));
    strcpy(pv2->KeyName, "other_key");
    pv2->ValueCount = 1;
    pv2->Next = NULL;
    
    printf("HashAdd(map, '%s')\n", pv1->KeyName);
    HashAdd(map, pv1);
    
//    printf("HashAdd(map, '%s')\n", pv1->KeyName);
//    HashAdd(map, pv1);

    printf("HashAdd(map, '%s')\n", pv2->KeyName);
    HashAdd(map, pv2);

    printf("HashFind(map, %s) = ", pv1->KeyName);
    PairValue* result = HashFind(map, pv1->KeyName);
    if (result) {
        printf("{'%s': %d}\n", result->KeyName, result->ValueCount);
    } else {
        printf("Not found\n");
    }

    printf("HashDump(map) = \n");
    HashDump(map);

    printf("HashDelete(map, '%s')\n", pv1->KeyName);
    HashDelete(map, pv1->KeyName);
    pv1 = NULL;

    printf("HashFind(map, %s) = ", pv1->KeyName);
    result = HashFind(map, pv1->KeyName);
    if (result) {
        printf("{'%s': %d}\n", result->KeyName, result->ValueCount);
    } else {
        printf("Not found\n");
    }

    printf("HashDump(map) = \n");
    HashDump(map);

    free(pv2);
    free(map);

    return EXIT_SUCCESS;
}
