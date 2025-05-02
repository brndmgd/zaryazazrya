#include "HashTable.h"
#include <assert.h>
#include <stdio.h>

pool_allocator_t *create_allocator_for_hashtable(size_t bucket_count,
                                                 size_t n_elements) {
  size_t chunk_size = (bucket_count * sizeof(HashNode *) > sizeof(HashNode))
                          ? bucket_count * sizeof(HashNode *)
                          : sizeof(HashNode);
  return pool_init(n_elements + 1, chunk_size);
}

void test_hashtable_init() {
  size_t bucket_count = 10;
  size_t n_elements = 20;
  pool_allocator_t *allocator =
      create_allocator_for_hashtable(bucket_count, n_elements);
  HashTable table;
  hashtable_init(&table, bucket_count, allocator);

  for (size_t i = 0; i < table.bucket_count; ++i) {
    assert(table.buckets[i] == NULL);
  }

  pool_deinit(allocator);
}

void test_hashtable_insert() {
  size_t bucket_count = 10;
  size_t n_elements = 20;
  pool_allocator_t *allocator =
      create_allocator_for_hashtable(bucket_count, n_elements);
  HashTable table;
  hashtable_init(&table, bucket_count, allocator);

  int value = 42;
  hashtable_insert(&table, "key1", &value);

  HashNode *node = table.buckets[hash_function("key1") % table.bucket_count];
  assert(node != NULL);
  assert(node->value == &value);

  pool_deinit(allocator);
}

void test_hashtable_get() {
  size_t bucket_count = 10;
  size_t n_elements = 20;
  pool_allocator_t *allocator =
      create_allocator_for_hashtable(bucket_count, n_elements);
  HashTable table;
  hashtable_init(&table, bucket_count, allocator);

  int value = 42;
  hashtable_insert(&table, "key1", &value);

  void *result = hashtable_get(&table, "key1");
  assert(result != NULL);
  assert(*(int *)result == 42);

  pool_deinit(allocator);
}

void test_hashtable_del() {
  size_t bucket_count = 10;
  size_t n_elements = 20;
  pool_allocator_t *allocator =
      create_allocator_for_hashtable(bucket_count, n_elements);
  HashTable table;
  hashtable_init(&table, bucket_count, allocator);

  int value = 42;
  hashtable_insert(&table, "key1", &value);
  hashtable_del(&table, "key1");

  HashNode *node = table.buckets[hash_function("key1") % table.bucket_count];
  assert(node == NULL);

  pool_deinit(allocator);
}

void test_hashtable_free() {
  size_t bucket_count = 10;
  size_t n_elements = 20;
  pool_allocator_t *allocator =
      create_allocator_for_hashtable(bucket_count, n_elements);
  HashTable table;
  hashtable_init(&table, bucket_count, allocator);

  int value = 42;
  hashtable_insert(&table, "key1", &value);

  hashtable_free(&table);
}

void test_hashtable_collision() {
  size_t bucket_count = 1;
  size_t n_elements = 20;
  pool_allocator_t *allocator =
      create_allocator_for_hashtable(bucket_count, n_elements);
  HashTable table;
  hashtable_init(&table, bucket_count, allocator);

  const char *key1 = "aaj";
  const char *key2 = "aak";
  int value1 = 111;
  int value2 = 222;

  size_t idx1 = hash_function(key1) % table.bucket_count;
  size_t idx2 = hash_function(key2) % table.bucket_count;
  assert(idx1 == idx2);

  hashtable_insert(&table, key1, &value1);
  hashtable_insert(&table, key2, &value2);

  assert(hashtable_get(&table, key1) == &value1);
  assert(hashtable_get(&table, key2) == &value2);

  hashtable_del(&table, key1);
  assert(hashtable_get(&table, key1) == NULL);
  assert(hashtable_get(&table, key2) == &value2);

  pool_deinit(allocator);
}

void test_hashtable_update_value() {
  size_t bucket_count = 10;
  size_t n_elements = 20;
  pool_allocator_t *allocator =
      create_allocator_for_hashtable(bucket_count, n_elements);
  HashTable table;
  hashtable_init(&table, bucket_count, allocator);

  const char *key = "update";
  int value1 = 123;
  int value2 = 456;

  hashtable_insert(&table, key, &value1);
  assert(hashtable_get(&table, key) == &value1);

  hashtable_insert(&table, key, &value2);
  assert(hashtable_get(&table, key) == &value2);

  pool_deinit(allocator);
}

void test_hashtable_get_nonexistent() {
  size_t bucket_count = 10;
  size_t n_elements = 20;
  pool_allocator_t *allocator =
      create_allocator_for_hashtable(bucket_count, n_elements);
  HashTable table;
  hashtable_init(&table, bucket_count, allocator);

  assert(hashtable_get(&table, "no_such_key") == NULL);

  pool_deinit(allocator);
}

void test_hashtable_del_nonexistent() {
  size_t bucket_count = 10;
  size_t n_elements = 20;
  pool_allocator_t *allocator =
      create_allocator_for_hashtable(bucket_count, n_elements);
  HashTable table;
  hashtable_init(&table, bucket_count, allocator);

  hashtable_del(&table, "no_such_key");

  pool_deinit(allocator);
}

void test_hashtable_null_args() {
  hashtable_init(NULL, 10, NULL);
  hashtable_insert(NULL, NULL, NULL);
  assert(hashtable_get(NULL, NULL) == NULL);
  hashtable_del(NULL, NULL);
  hashtable_free(NULL);
}

void test_hashtable_long_key() {
  size_t bucket_count = 10;
  size_t n_elements = 20;
  pool_allocator_t *allocator =
      create_allocator_for_hashtable(bucket_count, n_elements);
  HashTable table;
  hashtable_init(&table, bucket_count, allocator);

  char long_key[256];
  for (int i = 0; i < 255; ++i)
    long_key[i] = 'a';
  long_key[255] = '\0';

  int value = 999;
  hashtable_insert(&table, long_key, &value);
  assert(hashtable_get(&table, long_key) == &value);

  pool_deinit(allocator);
}

void test_hashtable_fill() {
  size_t bucket_count = 10;
  size_t n_elements = 20;
  pool_allocator_t *allocator =
      create_allocator_for_hashtable(bucket_count, n_elements);
  HashTable table;
  hashtable_init(&table, bucket_count, allocator);

  int values[20];
  char keys[20][8];
  for (int i = 0; i < 20; ++i) {
    snprintf(keys[i], sizeof(keys[i]), "k%d", i);
    values[i] = i * 10;
    hashtable_insert(&table, keys[i], &values[i]);
  }
  for (int i = 0; i < 20; ++i) {
    assert(hashtable_get(&table, keys[i]) == &values[i]);
  }

  pool_deinit(allocator);
}

int main() {
  test_hashtable_init();
  test_hashtable_insert();
  test_hashtable_get();
  test_hashtable_collision();
  test_hashtable_update_value();
  test_hashtable_del();
  test_hashtable_free();
  test_hashtable_get_nonexistent();
  test_hashtable_del_nonexistent();
  test_hashtable_null_args();
  test_hashtable_long_key();
  test_hashtable_fill();

  printf("All tests passed successfully!\n");
  return 0;
}
