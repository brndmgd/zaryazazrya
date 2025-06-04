
#include "reference_counter.h"

void default_dtor(void *object, pool_allocator_t *allocator) {
  if (object) {
    pool_free(allocator, object);
  }
}

ref_count_t *rc_init(void *obj, pool_allocator_t *allocator, constructor ctor,
                     deconstructor dtor) {
  if (allocator == NULL) {
    return NULL;
  }

  ref_count_t *rc = (ref_count_t *)pool_alloc(allocator);
  if (rc == NULL) {
    return NULL;
  }

  rc->count = 1;

  rc->ctor = ctor;

  if (ctor) {
    rc->object = ctor(allocator);
    if (rc->object == NULL) {
      pool_free(allocator, rc);
      return NULL;
    }
  } else {
    rc->object = obj;
  }
  rc->dtor = (dtor != NULL ? dtor : default_dtor);

  return rc;
}

void rc_increase(ref_count_t *rc) {
  if (rc) {
    rc->count += 1;
  }
}

void rc_decrease(ref_count_t *rc, pool_allocator_t *allocator) {
  if (rc == NULL || allocator == NULL) {
    return;
  }

  if (rc->count == 0) {
    return;
  }

  rc->count -= 1;
  if (rc->count == 0) {
    if (rc->dtor) {
      rc->dtor(rc->object, allocator);
    }
    pool_free(allocator, rc);
  }
}
