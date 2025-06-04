#include "reference_counter.h"
#include <assert.h>

void create_reference_test() {
  pool_allocator_t *allocator = pool_init(10, sizeof(ref_count_t));
  void *object = (int *)pool_alloc(allocator);
  ref_count_t *ref_counter = rc_init(object, allocator, NULL, NULL);

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
  ref_count_t *ref_counter = rc_init(object, allocator, NULL, NULL);

  rc_increase(ref_counter);
  assert(ref_counter->count == 2);

  pool_free(allocator, ref_counter->object);
  pool_free(allocator, ref_counter);
  pool_deinit(allocator);
}

void decrease_reference_test() {
  pool_allocator_t *allocator = pool_init(10, sizeof(ref_count_t));
  void *object = (int *)pool_alloc(allocator);
  ref_count_t *ref_counter = rc_init(object, allocator, NULL, NULL);

  rc_increase(ref_counter);
  rc_decrease(ref_counter, allocator);
  assert(ref_counter->count == 1);
  rc_decrease(ref_counter, allocator);
  pool_deinit(allocator);
}

void custom_dtor_and_ctor_test() {
  typedef struct {
    int x;
    char y;
  } test_type;
  void *constructor(pool_allocator_t * allocator) {
    test_type *t = (test_type *)pool_alloc(allocator);
    if (t == NULL) {
      return NULL;
    }
    t->x = 10;
    t->y = 'y';
    return (void *)t;
  }
  void destructor(void *object, pool_allocator_t *allocator) {
    if (object == NULL) {
      return;
    }
    test_type *t = (test_type *)object;
    pool_free(allocator, t);
  }
  pool_allocator_t *allocator = pool_init(10, sizeof(ref_count_t));
  ref_count_t *rc = rc_init(NULL, allocator, constructor, destructor);
  assert(rc != NULL);
  assert(rc->count == 1);
  test_type *t = (test_type *)rc->object;
  assert(t != NULL);
  assert(t->x == 10);
  assert(t->y == 'y');
  assert(rc->ctor == constructor);
  assert(rc->dtor == destructor);
  rc_decrease(rc, allocator);
  pool_deinit(allocator);
}

void default_dtor_and_ctor_test() {
  pool_allocator_t *allocator = pool_init(10, sizeof(ref_count_t));
  void *object = (int *)pool_alloc(allocator);
  ref_count_t *ref_counter = rc_init(object, allocator, NULL, NULL);
  assert(ref_counter->dtor == default_dtor);
  assert(ref_counter->ctor == NULL);
  rc_decrease(ref_counter, allocator);
  pool_deinit(allocator);
}

int main() {
  create_reference_test();
  increase_reference_test();
  decrease_reference_test();
  custom_dtor_and_ctor_test();
  default_dtor_and_ctor_test();
  return 0;
}

