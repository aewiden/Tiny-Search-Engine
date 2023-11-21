/* 
 * tiny search engine - querier
 *
 * see indexer.h for more information.
 *
 * Avery Widen, Winter 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
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

typedef struct twocounters {
    counters_t* counter1;
    counters_t* counter2;
} twocounters_t;

typedef struct idCount {
    int* id;
    int* count;
} idCount_t;

int normalizeQuery(char* line, char** words);
void processQuery(index_t* index, char* pagedir);
counters_t* parseQuery(index_t* index, char** query);
bool read_input(char* dir, char* index);
void merge(counters_t* andSequence, counters_t* orSequence);
void unionMerge(counters_t* orSequence, counters_t* otherSequence);
void unionFunction(void* arg, const int key, const int count);
void intersect(counters_t* orSequence, counters_t* otherSequence);
void intersectFunction(void* arg, const int key, const int count);
int fileno(FILE *stream);

int main(const int argc, char* argv[]) {
    // check args
    if (argc != 3) {
        return 1;
    }
    // check validity of input
    if(!read_input(argv[1], argv[2])) {
        exit(1);
    }
    // load file into index
    else {
        FILE* fp = fopen(argv[2], "r");
        int lines = file_numLines(fp);
        fclose(fp);

        index_t* index = index_new(lines);
        char** words;
        index_load(argv[2]);

        fp = stdin;
        words = file_readFile(fp);
        processQuery(index, words);

        free(words);
        index_delete(index);
        fclose(fp);
    }

    return 0;
}

static void prompt(void) {
  // print a prompt iff stdin is a tty (terminal)
  if (isatty(fileno(stdin))) {
    printf("Query? ");
  }
}

counters_t* parseQuery(index_t* index, char** query) {
    // create and and or sequence
    counters_t* andSequence;
    counters_t* orSequence;
    bool shortCircuit = false;

    // loop through query
    for(int i = 0; i < strlen(query); i++) { //fix
        if(strcmp(query[i], "or") == 0) {
            merge(andSequence, orSequence);
            shortCircuit = false;
            continue;
        }
        if(shortCircuit) {
            continue;
        }
        if(strcmp(query[i], "and") == 0) {
            continue;
        }
        // look for match
        else {
            void* match = index_find(index, query[i]);
            if(match == NULL) {
                shortCircuit = true;
                if(andSequence != NULL) {
                    free(andSequence);
                    andSequence = NULL;
                }
            }
            // add to counter
            else {
                if(andSequence == NULL) {
                    andSequence = counters_new();
                    unionMerge(andSequence, match);
                }
                else {
                    intersect(andSequence, match);
                }
            }
        }
    }
    merge(andSequence, orSequence);
    return orSequence;
}

bool read_input(char* dir, char* index) {
    // check pagedir
    char* pagedir = (malloc(strlen(dir) + 10));
    strcpy(pagedir, dir);
    strcat(pagedir, ".crawler");
    FILE* fp = fopen(pagedir, "r");
    if(fp == NULL) {
        fprintf(stderr, "Invalid directory.\n");
        free(pagedir);
        free(dir);
        return false;
    }
    free(pagedir);
    fclose(fp);
    // check index
    fp = fopen(index, "r");
    if(fp == NULL) {
        fprintf(stderr, "Invalid index.\n");
        return false;
    }
    fclose(fp);
    return true;
}

void processQuery(index_t* index, char* pagedir) {
    char* line = NULL;
    int len = 0;

    // go through each line of file
    while((line = file_readLine(stdin)) != NULL) {
        char** words = calloc(sizeof(char*), strlen(line) + 1);
        len = normalizeQuery(line, words);
        printf("Query? ");
        for(int i = 0; i < len; i++) {
            printf(" %s", words[i]);
        }
        printf("\n");

        // check for valid query
        char* neighbor = NULL;
        char* curr = NULL;
        bool queryCheck = true; 
        if(len == 0) {
            fprintf(stderr, "Empty query.\n");
            queryCheck = false;
        }
        // check and/or combinations
        if((strcmp(words[0], "and") == 0 || strcmp(words[0], "or") == 0)) {
            fprintf(stderr, "And/or cannot be first in query.\n");
            queryCheck = false;
        }

        if((strcmp(words[len - 1], "and") == 0 || strcmp(words[len -1 ], "or") == 0)) {
            fprintf(stderr, "And/or cannot be last in query.\n");
            queryCheck = false;
        }

        for(int i = 0; i < len; i++) {
            curr = words[i];
            if(neighbor != NULL) {
                if((strcmp(curr, "and") == 0) || (strcmp(curr, "or") == 0)) {
                    fprintf(stderr, "And/or cannot be adjacent.\n");
                    queryCheck = false;
                }
                else {
                    neighbor = NULL;
                }
            }
            else {
                if((strcmp(curr, "and") == 0) || (strcmp(curr, "or") == 0)) {
                    neighbor = curr;
                }
            }
            for(int j = 0; i < strlen(curr); j++) {
                if(isalpha(curr[j]) == 0) {
                    fprintf(stderr, "Bad character in query.\n");
                    queryCheck = false;
                }
            }
        }
        if(!queryCheck) {
            free(words);
            free(line);
            exit(1);
        }

        // call query
        printf("Input query: \n");
        free(words);
        free(line);
    }

}

int normalizeQuery(char* line, char** words) {
    char delim[] = " ";
    char* word = strtok(line, delim);
    int i = 1;
    if(word == NULL) {
        return 0;
    }
    // normalize query to all lowercase
    while((word = strtok(NULL, delim)) != NULL) {
        normalizeWord(word);
        words[i] = word;
        i++;
    }
    return i;
}

void merge(counters_t* andSequence, counters_t* orSequence) {
   // push temporary result andSequence to final result orSequence
    // also reset andSequence
   if(andSequence != NULL) {
        if(orSequence == NULL) {
            orSequence = counters_new();
            unionMerge(orSequence, andSequence);
            free(andSequence);
            andSequence = NULL;
        }
    }
}

void unionMerge(counters_t* orSequence, counters_t* otherSequence) {
    // union orSequence and otherSequence by adding counts for matching keys
    // store results in orSequence
    counters_iterate(otherSequence, orSequence, unionFunction);
}

void unionFunction(void* arg, const int key, const int count) {
    int wordCount = counters_get(arg, key);
    counters_set(arg, key, count + wordCount);
}

void intersect(counters_t* orSequence, counters_t* otherSequence) {
    twocounters_t* args= {orSequence, otherSequence};
    counters_iterate(orSequence, args, intersectFunction);
}

void intersectFunction(void* arg, const int key, const int count) {
    //return counters_set(arg->counter1, key, min(count, counters_get(arg->counter2, key)));
}
