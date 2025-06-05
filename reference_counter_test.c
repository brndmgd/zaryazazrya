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

void create_cycle_reference_test() {
  pool_allocator_t *allocator = pool_init(10, sizeof(ref_count_t));
  assert(allocator != NULL);
  cycle_object *obj1 = create_cycle_object(allocator);
  cycle_object *obj2 = create_cycle_object(allocator);
  assert(obj1 != NULL);
  assert(obj2 != NULL);
  assert(obj1->rc != NULL);
  assert(obj2->rc != NULL);
  assert(obj1->rc->count == 1);
  assert(obj2->rc->count == 1);
  create_cycle_reference(obj1, obj2);
  assert(obj1->ref_to == obj2);
  assert(obj2->ref_to == obj1);
  assert(obj1->rc->count == 2);
  assert(obj2->rc->count == 2);
  assert(detected_cycle(obj1) == 1);
  assert(detected_cycle(obj2) == 1);
  delete_cycle(allocator, obj1);
  pool_deinit(allocator);
}

void detected_cycle_test() {
  pool_allocator_t *allocator = pool_init(10, sizeof(ref_count_t));
  assert(allocator != NULL);
  cycle_object *obj1 = create_cycle_object(allocator);
  cycle_object *obj2 = create_cycle_object(allocator);
  cycle_object *obj3 = create_cycle_object(allocator);
  assert(obj1 != NULL);
  assert(obj2 != NULL);
  assert(obj3 != NULL);
  obj1->ref_to = obj2;
  rc_increase(obj2->rc);
  obj2->ref_to = obj3;
  rc_increase(obj3->rc);
  obj3->ref_to = obj1;
  rc_increase(obj1->rc);
  assert(detected_cycle(obj1) == 1);
  assert(detected_cycle(obj2) == 1);
  assert(detected_cycle(obj3) == 1);
  cycle_object *obj4 = create_cycle_object(allocator);
  assert(obj4 != NULL);
  assert(detected_cycle(obj4) == 0);
  delete_cycle(allocator, obj1);
  rc_decrease(obj4->rc, allocator);
  pool_deinit(allocator);
}

int main() {
  create_reference_test();
  increase_reference_test();
  decrease_reference_test();
  custom_dtor_and_ctor_test();
  default_dtor_and_ctor_test();
  create_cycle_reference_test();
  detected_cycle_test();
  return 0;
}
