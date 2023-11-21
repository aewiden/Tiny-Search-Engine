#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h"
#include "../libcs50/set.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/hash.h"

typedef struct index index_t;

index_t* index_new(int numslots);

void* index_find(index_t* index, const char* key);

void index_print(void* arg, const char* key, void* item);

bool index_insert(index_t* index, const char* key, void* item);

void index_load(char* filename);

void counterFunc(void* arg, const int key, int count);

void index_save(index_t* index, char* filename);

void index_delete(index_t* index);

void deleteFunc(void* item);