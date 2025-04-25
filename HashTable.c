#include <stdlib.h>

void hashtable_init(HashTable* table, size_t capacity, Allocator* allocator){
    void hashtable_init(HashTable* table, size_t capacity, pool_allocator_t* allocator){
        if (table == NULL || allocator == NULL || capacity == 0) {
            return;
        }
    
        table->bucket_count = capacity;
        table->allocator = allocator;
    
        table->buckets = (HashNode**)pool_alloc(allocator);
        if (table->buckets == NULL) {
            return;
        }
    
        for (size_t i = 0; i < capacity; ++i) {
            table->buckets[i] = NULL;
        }
    }
}