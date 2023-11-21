/* 
 * tiny search engine - pagedir.h
 *
 * Avery Widen, Winter 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h"


/***************** pagedir_init ******************************/
/*
* Caller provides: pointer to directory to initialize 
* constructs the pathname for the .crawler file in that directory
* opens the file for writing; on error, returns false.
* closes the file and returns true.
*
*/
bool pagedir_init(const char* pageDirectory);


/***************** pagedir_save ******************************/
/*
* Caller provides: pointer to webpage for saving, pointer to directory to save to, and the integer document ID
* constructs the pathname for the page file in pageDirectory
* opens that file for writing
* prints the URL, prints the depth, and prints the contents of the webpage
* closes the file
*
*/
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
