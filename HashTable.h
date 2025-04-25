#include <stdlib.h>

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

void hashtable_init(HashTable* table, size_t capacity, pool_allocator_t* allocator)

