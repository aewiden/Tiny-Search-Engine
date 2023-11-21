
# valid test
./indexer ~/cs50-dev/shared/tse/output test

# no arguments 
./indexer

# one argument 
./indexer ~/cs50-dev/shared/tse/output

# three or more arguments 
./indexer ~/cs50-dev/shared/tse/output test dogs cats

# invalid pageDirectory (non-existent path)
./indexer ../averytest test

# invalid pageDirectory (not a crawler directory) 
./indexer ../libcs50 test

# invalid indexFile (non-existent path) 
./indexer ../averytest

# invalid indexFile (read-only directory) 
./indexer ../tse-aewiden test

# invalid indexFile (existing, read-only file)
./indexer ~/cs50-dev/shared/tse/output testesttest
