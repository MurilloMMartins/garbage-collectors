#include "langobject.h"

#include <stdlib.h>

lang_object_t *new_lang_float(float value) {
  return NULL;
}

lang_object_t *new_lang_integer(int value) {
  lang_object_t *obj = malloc(sizeof(lang_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;

  return obj;
}