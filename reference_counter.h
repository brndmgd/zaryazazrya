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

ref_count_t *rc_init(void *obj, pool_allocator_t *allocator, constructor ctor,
                     deconstructor dtor);
void rc_increase(ref_count_t *rc);
void rc_decrease(ref_count_t *rc, pool_allocator_t *allocator);
void default_dtor(void *object, pool_allocator_t *allocator);

