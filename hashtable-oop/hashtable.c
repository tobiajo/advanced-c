#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

struct entry {
	char *key;
	char *value;
	struct entry *next;
};

struct hashtable {
	int buckets;
	int size;
	struct entry **table;
};

typedef struct entry *Entry;

static unsigned long djb2_hash(char *);
static void free_bucket(Entry *);
static void free_entry(Entry *);

//-----------------------------------------------------------------------------
// Create, destory
//-----------------------------------------------------------------------------

HashTable newHashTable(int buckets) {
	HashTable ht = malloc(sizeof(struct hashtable));
	ht->table = malloc(buckets * sizeof(struct entry *));
	for (int i = 0; i < buckets; i++) {
		ht->table[i] = NULL;
	}
	ht->buckets = buckets;
	ht->size = 0;
	return ht;
}

void freeHashTable(HashTable *thisPtr) {
	for (int i = 0; i < (*thisPtr)->buckets; i++) {
		free_bucket(&(*thisPtr)->table[i]);
	}
	free((*thisPtr)->table);
	(*thisPtr)->table = NULL;
	free(*thisPtr);
	*thisPtr = NULL;
}

//-----------------------------------------------------------------------------
// Public methods
//-----------------------------------------------------------------------------

int HashTable_buckets(HashTable this) {
	return this->buckets;
}

const char *HashTable_get(HashTable this, char *key) {
	Entry e;
	int b = djb2_hash(key) % this->buckets;
	for (e = this->table[b]; e != NULL; e = e->next) {
		if (strcmp(e->key, key) == 0) {
			return e->value;
		}
	}
	return NULL;
}

bool HashTable_put(HashTable this, char *key, char *value) {
	Entry *ePtr;
	int b = djb2_hash(key) % this->buckets;
	for (ePtr = &this->table[b]; *ePtr != NULL; ePtr = &(*ePtr)->next) {
		if (strcmp((*ePtr)->key, key) == 0) {
			return false;
		}
	}
	*ePtr = malloc(sizeof(struct entry));
	(*ePtr)->key = strdup(key);
	(*ePtr)->value = strdup(value);
	(*ePtr)->next = NULL;
	this->size++;
	return true;
}

bool HashTable_remove(HashTable this, char *key) {
	Entry *ePtr, next;
	int b = djb2_hash(key) % this->buckets;
	for (ePtr = &this->table[b]; *ePtr != NULL; ePtr = &(*ePtr)->next) {
		if (strcmp((*ePtr)->key, key) == 0) {
			next = (*ePtr)->next;
			free_entry(ePtr);
			*ePtr = next;
			this->size--;
			return true;
		}
	}
	return false;
}

int HashTable_size(HashTable this) {
	return this->size;
}

//-----------------------------------------------------------------------------
// Private methods
//-----------------------------------------------------------------------------

static unsigned long djb2_hash(char *str) {
	unsigned long hash = 5381;
	unsigned char c;
	while ((c = *str++) != '\0') {
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}
	return hash;
}

static void free_bucket(Entry *ePtr) {
	if (*ePtr == NULL) {
		return;
	}
	free_bucket(&(*ePtr)->next);
	free_entry(ePtr);
}

static void free_entry(Entry *ePtr) {
	free((*ePtr)->key);
	free((*ePtr)->value);
	(*ePtr)->key = NULL;
	(*ePtr)->value = NULL;
	free(*ePtr);
	*ePtr = NULL;
}
