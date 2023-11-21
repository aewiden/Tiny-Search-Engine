/* 
 * tiny search engine - crawler.h
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

/***************** main ******************************/
/*
* Takes stdIn, only parses the arguments and crawls.
*
*
*/
int main(const int argc, char* argv[]);

/***************** parseArgs ******************************/
/*
*
* Given arguments from the command line, extract them into the function parameters; returns only if successful.
* 
* for seedURL, normalizes the URL and validates it is an internal URL
* for pageDirectory, calls pagedir_init()
* for maxDepth, ensures it is an integer in specified range
* if any trouble is found, prints an error to stderr and exit non-zero.
*
*
*/
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth);


/***************** crawl ******************************/
/*
* initialize the hashtable and add the seedURL
* initializes the bag and adds a webpage representing the seedURL at depth 0
* fetches the HTML for that webpage
* saves the webpage to pageDirectory upon a successful fetch
* if the webpage is not at maxDepth, pageScans that HTML
* deletes that webpage, deletes the hashtable, and deletes the bag
*
* Caller provides: pointer to seedURL to crawl, pointer to page directory for saving, and an integer for the max depth
*/
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);

/***************** pageScan ******************************/
/*
* Checks if the next valid URL is Internal, inserts the webpage into the hashtable
*creates a webpage_t for it upon successful insertion and puts it in the bag
*
* Caller provides: pointer to page for scanning, pointer to bag of pages left to crawl, pointer to hashtable of seen pages
*/
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);