/* 
 * tiny search engine - indexer
 *
 * see indexer.h for more information.
 *
 * Avery Widen, Winter 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "../common/word.h"
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../libcs50/set.h"
#include "../libcs50/counters.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/hash.h"    
#include "../common/pagedir.h"
#include "../libcs50/file.h"

void indexBuild(char* filename);
void indexPage(index_t* index, webpage_t* webpage, const int docID);

int main(const int argc, char* argv[]) {
    // checks arguments
    if (argc != 3) {
        fprintf(stderr, "Invalid parameters.\n");
        return 1;
    }

    FILE* fp;
    char* pageDir = argv[2];
    char* filename = argv[3];

    // checks if pagedirectory is able to be initialized
    if(!pagedir_init(pageDir)) {
        fprintf(stderr, "Cannot make page directory.\n");
        return 1;
    }

    if((fp = fopen(argv[2], "w") == NULL)) {
        fprintf(stderr, "File cannot be written.\n");
        return 1;
    }
    else {
        fclose(fp);
    }

    // calls build index
    indexBuild(argv[2]);
    index_save(argv[2], fp);
    return 0;
}

void indexBuild(char* filename) {
    // size of ht
    index_t* index = index_new(200);
    FILE* fp;
    // makes directory name
    char* pageDir = malloc((strlen(filename) + 3) * sizeof(char*));
    strcpy(pageDir, filename);
    strcat(pageDir, "/");
    webpage_t* webpage;
    int docID = 1;
    char loop[100];
    sprintf(loop, "%s/%d", filename, docID);

    // while page directory is readable, build the index
    while((fp = fopen(pageDir, "r")) != NULL ){
        int pos = 0;
        char* word;
        char* url = file_readLine(fp);
        char* temp = file_readLine(fp);
        int depth = atoi(temp);
        free(temp);
        // create a new webpage from the file
        webpage = webpage_new(url, depth, file_readFile(fp));
        indexPage(index, webpage, docID);
        docID++;
        webpage_delete(webpage);
        fclose(fp);
    }

    // reset values
    free(pageDir);
    pageDir = malloc((strlen(filename) + 3) * sizeof(char*));
    sprintf(pageDir, "%s/%d", filename, docID);
    return;

}

void indexPage(index_t* index, webpage_t* webpage, const int docID) {

    int pos = 0;
    char* result; 
    while ((result = webpage_getNextWord(webpage, &pos)) != NULL) {
        // normalizes the word
        char* normWord = normalizeWord(result);
        // checks the word length
        if(strlen(normWord) >= 3) {
           if(index_find(index, normWord) != NULL) {
            // increments the counter if word exists
                counters_t* counter = index_find(index, normWord);
                counters_add(counter, docID);
           }
           else {
            // adds a counter if word is not found
                counters_t* counter = counters_new();
                counters_add(counter, docID);
                index_insert(index, normWord, counter);
           }
        free(normWord);
        free(result);
        }
    }
}
