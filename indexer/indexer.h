#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../libcs50/set.h"
#include "../libcs50/counters.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/hash.h"    
#include "../common/pagedir.h"


int main(const int argc, char* argv[]);

void indexBuild(char* filename);

void indexPage(index_t* index, webpage_t* webpage, const int docID);