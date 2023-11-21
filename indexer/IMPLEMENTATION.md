# CS50 TSE Indexer
## Implementation Spec

In this document we reference the [Requirements Specification](REQUIREMENTS.md) and [Design Specification](DESIGN.md) and focus on the implementation-specific decisions.
The knowledge unit noted that an [implementation spec](https://github.com/CS50winter2023/home/blob/main/knowledge/units/design.md#implementation-spec) may include many topics; not all are relevant to the TSE or the Indexer.
Here we focus on the core subset:

-  Data structures
-  Control flow: pseudo code for overall flow, and for each of the functions
-  Detailed function prototypes and their parameters
-  Testing plan

## Data structures 

We use the following data structures: index (made up of a hashtable of counters), counters, hashtable, and set. 
Both start empty.
The size of the hashtable (slots) is impossible to determine in advance, so we use 200.

## Control flow

The Crawler is implemented in one file `indexer.c`, with three functions.

### main

The `main` function parses the arguments, calls `indexBuild` and `indexPage` and exits zero if successful.

### indexBuild

  creates a new 'index' object
  loops over document ID numbers, counting from 1
    loads a webpage from the document file 'pageDirectory/id'
    if successful, 
      passes the webpage and docID to indexPage

### indexPage

 steps through each word of the webpage,
   skips trivial words (less than length 3),
   normalizes the word (converts to lower case),
   looks up the word in the index,
     adding the word to the index if needed
   increments the count of occurrences of this word in this docID

## Other modules

### pagedir

We create a re-usable module `pagedir.c` to handles the *pagesaver*  mentioned in the design (writing a page to the pageDirectory), and marking it as a Crawler-produced pageDirectory (as required in the spec).
We chose to write this as a separate module, in `../common`, to encapsulate all the knowledge about how to initialize and validate a pageDirectory, and how to write and read page files, in one place... anticipating future use by the Indexer and Querier.

Pseudocode for `pagedir_init`:

	construct the pathname for the .crawler file in that directory
	open the file for writing; on error, return false.
	close the file and return true.


Pseudocode for `pagedir_save`:

	construct the pathname for the page file in pageDirectory
	open that file for writing
	print the URL
	print the depth
	print the contents of the webpage
	close the file

### word

We create a `word.c` module that just contains a function to normalize a word. 

Pseudocode for `word.c`:

    takes a char* word
    checks if it is a valid argument
    sets it all to lowercase
    returns the normalized word


### libcs50

We leverage the modules of libcs50, most notably `bag`, `hashtable`, and `webpage`.
See that directory for module interfaces.
The new `webpage` module allows us to represent pages as `webpage_t` objects, to fetch a page from the Internet, and to scan a (fetched) page for URLs; in that regard, it serves as the *pagefetcher* described in the design.
Indeed, `webpage_fetch` enforces the 1-second delay for each fetch, so our crawler need not implement that part of the spec.

## Function prototypes

### indexer

Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's implementation in `indexer.c` and is not repeated here.

```c
void indexBuild(char* filename);
void indexPage(index_t* index, webpage_t* webpage, const int docID);
```

### index

Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's declaration in `index.h` and is not repeated here.

```c
typedef struct index index_t;
index_t* index_new(int numslots);
void* index_find(index_t* index, const char* key);
void index_print(void* arg, const char* key, void* item);
bool index_insert(index_t* index, const char* key, void* item);
void index_load(char* filename);
void counterFunc(void* arg, const int key, int count);
void index_save(index_t* index, char* filename);
void index_delete(index_t* index);
void deleteFunc(void* item);
```

## Error handling and recovery

All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

Out-of-memory errors are handled by variants of the `mem_assert` functions, which result in a message printed to stderr and a non-zero exit status.
We anticipate out-of-memory errors to be rare and thus allow the program to crash (cleanly) in this way.

All code uses defensive-programming tactics to catch and exit (using variants of the `mem_assert` functions), e.g., if a function receives bad parameters.

## Testing plan

Here is an implementation-specific testing plan.

### Unit testing

There are only two units (indexer and index).
The indexer represents the whole system and is covered below.
The pagedir unit is tiny; it could be tested using a small C 'driver' to invoke its functions with various arguments, but it is likely sufficient to observe its behavior during the system test.
The index function requires a separate `indextest.c` file to test it.

### Integration/system testing

We write a script `testing.sh` that invokes the crawler several times, with a variety of command-line arguments.