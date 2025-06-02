#include "reference_counter.h"

ref_count_t *rc_init(void *obj, pool_allocator_t *allocator) {
  if (obj == NULL || allocator == NULL)
    return NULL;

  ref_count_t *rc = (ref_count_t *)pool_alloc(allocator);
  if (rc == NULL)
    return NULL;

  rc->count = 1;
  rc->object = obj;
  return rc;
}

void rc_increase(ref_count_t *rc) {
  if (rc)
    rc->count++;
}

void rc_decrease(ref_count_t *rc, pool_allocator_t *allocator) {
  if (rc)
    rc->count--;
  if (rc->count == 0) {
    if (rc->object == NULL) {
      pool_free(allocator, rc);
      return;
    }

    pool_free(allocator, rc->object);
    pool_free(allocator, rc);
  }
}
