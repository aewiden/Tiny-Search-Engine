#!/bin/bash

# bad arguments
./crawler http://wikipedia.org fakedir three

# bad arguments
./crawler notaURL ../data/letters 3

# bad arguments
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters four

# bad arguments
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html fakedir 3

# depth below range
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters -1

# depth above range
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 12

# min depth
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 0

# depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 1

# depth 2
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 2

# max depth
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 10

# scrape data
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../data/toscrape 0

# scrape data
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../data/toscrape 1

# scrape data
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../data/toscrape 2

# scrape data
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../data/toscrape 3

# wikipedia data
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wikipedia 0

# wikipedia data
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wikipedia 1

# wikipedia data
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wikipedia 2

# invalid link
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 12


