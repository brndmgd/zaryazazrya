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
    
    void hash_table_insert(HashTable* table, const char* key, void* value) {
        if (table == NULL || key == NULL) {
            return;
        }
    
        unsigned long hash = hash_function(key);
        size_t index = hash % table->bucket_count;
    
        HashNode* node = table->buckets[index];
        while (node != NULL) {
            if (strcmp(node->key, key) == 0) {
                node->value = value;
                return;
            }
            node = node->next;
        }
    
        HashNode* new_node = (entry_t*)pool_alloc(table->allocator);
        if (new_node == NULL) {
            return;
        }
    
        new_node->key = key;
        new_node->value = value;
        new_node->next = table->buckets[index];
        table->buckets[index] = new_node;
    }


    
