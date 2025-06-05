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

cycle_object *create_cycle_object(pool_allocator_t *allocator) {
  if (allocator == NULL) {
    return NULL;
  }
  cycle_object *obj = (cycle_object *)pool_alloc(allocator);
  if (obj == NULL) {
    return NULL;
  }
  obj->rc = rc_init(obj, allocator, NULL, NULL);
  if (obj->rc == NULL) {
    pool_free(allocator, obj);
    return NULL;
  }
  obj->ref_to = NULL;
  return obj;
}

void create_cycle_reference(cycle_object *obj1, cycle_object *obj2) {
  if (obj1 == NULL || obj2 == NULL || obj1->rc == NULL || obj2->rc == NULL) {
    return;
  }
  obj1->ref_to = obj2;
  obj2->ref_to = obj1;
  rc_increase(obj1->rc);
  rc_increase(obj2->rc);
}

int detected_cycle(cycle_object *start) {
  if (start == NULL || start->ref_to == NULL) {
    return 0;
  }
  cycle_object *obj1 = start;
  cycle_object *obj2 = start->ref_to;
  while (obj2 && obj2->ref_to) {
    if (obj1 == obj2) {
      return 1;
    }
    obj1 = (cycle_object *)obj1->ref_to;
    obj2 = ((cycle_object *)obj2->ref_to)->ref_to;
  }
  return 0;
}

void delete_cycle(pool_allocator_t *allocator, cycle_object *obj) {
  if (obj == NULL || obj->rc == NULL || allocator == NULL) {
    return;
  }
  if (detected_cycle(obj)) {
    cycle_object *current = obj;
    cycle_object *next;
    do {
      next = (cycle_object *)current->ref_to;
      if (next == NULL) {
        break;
      }
      current->ref_to = NULL;
      if (next->rc) {
        rc_decrease(next->rc, allocator);
      }
      current = next;
    } while (current && current != obj);
    rc_decrease(obj->rc, allocator);
  }
}
