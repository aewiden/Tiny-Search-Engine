/* 
 * tiny search engine - indextest.c
 *
 * Avery Widen, Winter 2023
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h"
#include "../libcs50/set.h"
#include "../libcs50/hashtable.h"
#include "../common/index.h"
#include "../libcs50/file.h"
#include "../libcs50/counters.h"
#include "../libcs50/hash.h"


int main(int argc, char* argv[]) {

    // create file pointer and check args
    FILE* fp;
    if (argc != 3) {
        fprintf(stderr, "Invalid arguments.\n");
        return 1;
    }

    // check if file is readable
    if((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "File cannot be opened.\n");
        return 1;
    }
    else {
        fclose(fp);
    }

    // check if file is writeable
    if((fp = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "File cannot be opened.\n");
        return 1;
    }
    else {
        fclose(fp);
    }

    // set file pointer and track number of lines in the file
    fp = fopen(argv[1], "r");
    int line = file_numLines(fp);
    index_t* index = index_new(line);
    index_load(index);
    index_save(index, fp);

    index_delete(index);
    fclose(fp);
    return 0;
}