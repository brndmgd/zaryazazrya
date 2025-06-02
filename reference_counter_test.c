#include "reference_counter.h"
#include <assert.h>

void create_reference_test() {
  pool_allocator_t *allocator = pool_init(10, sizeof(ref_count_t));
  void *object = (int *)pool_alloc(allocator);
  ref_count_t *ref_counter = rc_init(object, allocator);

  assert(ref_counter != NULL);
  assert(ref_counter->object == object);
  assert(ref_counter->count == 1);

  pool_free(allocator, ref_counter->object);
  pool_free(allocator, ref_counter);
  pool_deinit(allocator);
}

void increase_reference_test() {
  pool_allocator_t *allocator = pool_init(10, sizeof(ref_count_t));
  void *object = (int *)pool_alloc(allocator);
  ref_count_t *ref_counter = rc_init(object, allocator);

  rc_increase(ref_counter);
  assert(ref_counter->count == 2);

  pool_free(allocator, ref_counter->object);
  pool_free(allocator, ref_counter);
  pool_deinit(allocator);
}

void decrease_reference_test() {
  pool_allocator_t *allocator = pool_init(10, sizeof(ref_count_t));
  void *object = (int *)pool_alloc(allocator);
  ref_count_t *ref_counter = rc_init(object, allocator);

  rc_increase(ref_counter);
  rc_decrease(ref_counter, allocator);
  assert(ref_counter->count == 1);

  rc_decrease(ref_counter, allocator);
  pool_deinit(allocator);
}

int main() {
  create_reference_test();
  increase_reference_test();
  decrease_reference_test();

  return 0;
}