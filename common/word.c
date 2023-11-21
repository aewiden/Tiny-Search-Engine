/* 
 * tiny search engine - word.c
 *
 * Avery Widen, Winter 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../libcs50/webpage.h"

char* normalizeWord(const char* word);

char* normalizeWord(const char* word)
{
  if (word == NULL) {
    return NULL;
  }

  // Allocate space for resulting URL - which will be no longer than url.
  char* result = malloc(strlen(word)+1);
  if (result == NULL) {
    return NULL;
  } else {
    // initialize it to empty string
    *result = '\0';
  }
  for(int i = 0; i < strlen(word); i++) {
    result[i] = tolower(word[i]);
  }
  return result;
}
