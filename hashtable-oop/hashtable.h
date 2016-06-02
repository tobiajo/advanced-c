#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct hashtable *HashTable;

// Create, destory
HashTable newHashTable(int);
void freeHashTable(HashTable *);

// Public methods
int HashTable_buckets(HashTable);
const char *HashTable_get(HashTable, char *);
bool HashTable_put(HashTable, char *, char *);
bool HashTable_remove(HashTable, char *);
int HashTable_size(HashTable);

#endif
