#include <stdio.h>
#include "hashtable.h"

int main(int argc, char *argv[]) {

	HashTable ht = newHashTable(65535);
	
	HashTable_put(ht, "1", "two");
	HashTable_put(ht, "2", "three");
	HashTable_put(ht, "3", "five");
	HashTable_put(ht, "4", "seven");
	HashTable_put(ht, "5", "eleven");
	HashTable_put(ht, "6", "thirteen");
	HashTable_put(ht, "7", "seventeen");

	HashTable_remove(ht, "1");
	HashTable_remove(ht, "2");
	HashTable_remove(ht, "6");
	HashTable_remove(ht, "7");

	HashTable_put(ht, "3", "not allowed");

	printf("%s\n", HashTable_get(ht, "1"));
	printf("%s\n", HashTable_get(ht, "2"));
	printf("%s\n", HashTable_get(ht, "3"));
	printf("%s\n", HashTable_get(ht, "4"));
	printf("%s\n", HashTable_get(ht, "5"));
	printf("%s\n", HashTable_get(ht, "6"));
	printf("%s\n", HashTable_get(ht, "7"));

	printf("size: %d\n", HashTable_size(ht));	

	freeHashTable(&ht);

	return 0;
}
