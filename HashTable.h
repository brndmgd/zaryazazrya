#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include "pool_allocator.h"

typedef struct HashNode
{
    const char *key;
    void* value;
    struct HashNode *next;
} HashNode;

typedef struct
{
    size_t bucket_count;
    HashNode **buckets;
    pool_allocator_t *allocator;
} HashTable;

unsigned long hash_function(const char* str);

void hash_table_init(HashTable* table, size_t capacity, pool_allocator_t* allocator);

void hash_table_insert(HashTable* table, const char* key, void* value);

void* hashtable_get(HashTable* table, const char* key);

void hashtable_del(HashTable* table, const char* key);

void hashtable_free(HashTable* table);

#endif