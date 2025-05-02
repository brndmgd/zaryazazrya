#include <stdlib.h>


    void hash_table_init(HashTable* table, size_t capacity, pool_allocator_t* allocator){
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

    unsigned long hash_function(const char* str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++)) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash;
    }
    
    
