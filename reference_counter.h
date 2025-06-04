#include "pool_allocator.h"
#include <stdlib.h>

typedef void (*deconstructor)(void *object, pool_allocator_t *allocator);
typedef void *(*constructor)(pool_allocator_t *allocator);

typedef struct {
  size_t count;
  void *object;
  deconstructor dtor;
  constructor ctor;
} ref_count_t;

typedef struct {
  ref_count_t *rc;
  void *ref_to;
} cycle_object;

ref_count_t *rc_init(void *obj, pool_allocator_t *allocator, constructor ctor,
                     deconstructor dtor);
void rc_increase(ref_count_t *rc);
void rc_decrease(ref_count_t *rc, pool_allocator_t *allocator);
void default_dtor(void *object, pool_allocator_t *allocator);
cycle_object *create_cycle_object(pool_allocator_t *allocator);
void create_cycle_reference(cycle_object *obj1, cycle_object *obj2);
int detected_cycle(cycle_object *start);
void delete_cycle(pool_allocator_t *allocator, cycle_object *obj);
