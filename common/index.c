/* 
 * tiny search engine - index.c
 *
 * Avery Widen, Winter 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h"
#include "../libcs50/set.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/hash.h"
#include "../libcs50/file.h"

typedef struct index 
{
    hashtable_t* ht;
}
index_t;

void index_delete(index_t* index);
void* deleteFunc(void* item);
void index_print(void* arg, const char* key, void* item);
void* counterFunc(void* arg, const int key, int count);

// index_new, makes a new index from a hashtable
index_t* index_new(int numslots) {
    index_t* index = malloc(sizeof(index_t) + 1);
    index->ht = hashtable_new(numslots);
    return index;
}

// uses hashtable find to look through the index
void* index_find(index_t* index, const char* key) {
    return (index_t*)hashtable_find(index->ht, key);
}

// uses hashtable insert to insert a counter into the index
bool index_insert(index_t* index, const char* key, void* item) {
    if(hashtable_insert(index->ht, key, item)) {
        return true;
    }
    else {
        return false;
    }
}

// index_load, checks if the file is readable
index_t* index_load(char* filename) {  
    index_t* index = index_new(20);
    FILE* fp = fopen(filename, "r");

    // null checks
    if (index == NULL || fp == NULL) {
        fprintf(stderr, "Invalid file/index.\n");
        return NULL;
    }

    char* currLine = NULL;
    char* lineBreak = " ";

    // loops through each line in the file
    while((currLine = file_readLine(fp)) != NULL) {
        // makes a counter, adds each word based on a space delimiter
        counters_t* list = counters_new();
        char* word = strtok(currLine, lineBreak);
        char* docID = NULL;
        char* count = NULL;
        if(list == NULL) {
            fprintf(stderr, "Invalid counter instantiation.\n");
            index_delete(index);
            fclose(fp);
            return NULL;
        }
        // sets the counter to the docID and the proper count
        while(((docID = strtok(NULL, lineBreak)) != NULL) && ((count = strtok(NULL, lineBreak)) != NULL)) {
            counters_set(list, atoi(docID), atoi(count));
        }
        // inserts the counter and the word into the list
        index_insert(index, word, list);
        free(currLine);
    }
    fclose(fp);
    return index;
}

// index_save, works with a writeable file
void index_save(index_t* index, char* filename) {
    FILE* fp = fopen(filename, "w");
    // null checks
    if (index == NULL || filename == NULL) {
        fprintf(stderr, "Invalid input.\n");
        return;
    }
    
    if (fp == NULL) {
        fprintf(stderr, "Invalid file.\n");
        return;
    }

    fclose(fp);

}

void index_print(void* arg, const char* key, void* item) {
    counters_t* counter = item;
    FILE* fp = arg;
    fprintf(fp, "%s", key);
    counters_iterate(counter, fp, counterFunc);
    fprintf(fp, "\n");

}

void* counterFunc(void* arg, const int key, int count) {
    FILE* fp = arg;
    fprintf(fp, "%d, %d", key, count);
}

void index_delete(index_t* index) {
    hashtable_delete(index->ht, deleteFunc);
    free(index);
}

void* deleteFunc(void* item) {
    counters_t* counter = item;
    counters_delete(counter);
}
