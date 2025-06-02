#include "pool_allocator.h"
#include <stdlib.h>

typedef struct {
  size_t count;
  void *object;
} ref_count_t;

ref_count_t *rc_init(void *obj, pool_allocator_t *allocator);
void rc_increase(ref_count_t *rc);
void rc_decrease(ref_count_t *rc, pool_allocator_t *allocator);
