#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/word.h"
#include "../common/index.h"
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../libcs50/set.h"
#include "../libcs50/counters.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/hash.h"    
#include "../common/pagedir.h"
#include "../libcs50/file.h"

typedef struct twocounters twocounters_t;

typedef struct idCount idCount_t;

counters_t* parseQuery(index_t* index, char** query);

bool read_input(char* dir, char* index);

void processQuery(index_t* index, char* pagedir);

int normalizeQuery(char* line, char** words);

void merge(counters_t* andSequence, counters_t* orSequence);

void unionMerge(counters_t* orSequence, counters_t* otherSequence);

void unionFunction(void* arg, const int key, const int count);

void intersect(counters_t* orSequence, counters_t* otherSequence);

void intersectFunction(void* arg, const int key, const int count);
