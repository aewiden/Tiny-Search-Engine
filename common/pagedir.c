/* 
 * tiny search engine - pagedir
 *
 * see pagedir.h for more information.
 *
 * Avery Widen, Winter 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"
#include <assert.h>


bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

bool pagedir_init(const char* pageDirectory)
{
    if (pageDirectory == NULL) {
        fprintf(stderr, "Directory is null.\n");
        return false;
    }

    char name[2000];
    strcpy(name, pageDirectory);
    strcat(name, "/.crawler");

    FILE* fp = fopen(name, "w");
    if (fp == NULL) {
        fprintf(stderr, name);
        fprintf(stderr, "Invalid file.\n");
        return false;
    }

    fclose(fp);
    return true;
}


void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID)
{
    // construct file pathname
    char* url = webpage_getURL(page);
    char* path = malloc(sizeof(pageDirectory)+sizeof(page)+1);
    strcpy(path, pageDirectory);
    strcat(path, url);
    FILE* fp = fopen(pageDirectory, "w");

    fprintf(fp, "%s \n %d \n %s \n", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page));
    free(path);
    fclose(fp);
    
}


