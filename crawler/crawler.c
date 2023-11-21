/* 
 * tiny search engine - crawler
 *
 * see crawler.h for more information.
 *
 * Avery Widen, Winter 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../libcs50/set.h"
#include "../libcs50/counters.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/hash.h"    
#include "../common/pagedir.h"


int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);


int main(const int argc, char* argv[])
{   
    if(argc == 4) {
        char** seedURL = &argv[1];
        char** pageDirectory = &argv[2];
        int depth = atoi(argv[3]);
        int* maxDepth = &depth;
        parseArgs(argc, argv, seedURL, pageDirectory, maxDepth);
        crawl(argv[1], argv[2], depth);
    }
    else {
        fprintf(stderr, "Usage error: invalid arguments. \n");
        exit(1);
    }
    return 0;
}


static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth)
{
    char* normURL = normalizeURL((char*)seedURL);

   if(maxDepth == NULL || *maxDepth <= 0 || *maxDepth >= 10) {
      fprintf(stderr, "Max depth is not within accepted range. \n");
        exit(1);
    }

    if(pageDirectory == NULL || !pagedir_init((char*)pageDirectory)) {
        fprintf(stderr, "Unable to intialize page directory.\n");
        exit(1);
    }

    if(!isInternalURL((normURL))) {
        fprintf(stderr, "URL is not internal.\n");
        exit(1);
    }

}

static void crawl(char* seedURL, char* pageDirectory, const int maxDepth)
{
    webpage_t* page = webpage_new(seedURL, 0, NULL); 
    webpage_t* nextPage;
    bag_t* bag = bag_new();
    hashtable_t* seen = hashtable_new(200);
    int docID = 1;
    
    bag_insert(bag, page);
    hashtable_insert(seen, webpage_getURL(page), "");

    while(((nextPage = bag_extract(bag)) != NULL))
    {
        pagedir_save(nextPage, pageDirectory, docID);

        if(webpage_fetch(nextPage) == NULL) {
            fprintf(stderr, "File doesn't exist.\n");
            free(nextPage);
            free(seedURL);
            exit(1);
        }
        if(pagedir_init(pageDirectory)) {
            pagedir_save(nextPage, pageDirectory, docID);
            docID++;
        }
        if(webpage_getDepth(page) < maxDepth) {
            pageScan(nextPage, bag, seen);
        }
        webpage_delete(page);
    }

    bag_delete(bag, NULL);
    hashtable_delete(seen, NULL);

}


static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen)
{
    int* pos = 0;
    while(webpage_getNextURL(page, pos) != NULL) {
        if(isInternalURL(webpage_getNextURL(page, pos))) {
            // fix key
            if(hashtable_insert(pagesSeen, webpage_getNextURL(page, pos), "")) {
                webpage_t* nextPage = webpage_new(webpage_getNextURL(page, pos), webpage_getDepth(page) + 1, NULL);
                bag_insert(pagesToCrawl, nextPage);
            }
        }
        else {
            printf("Page seen");
        }
        free(page);
    }
}