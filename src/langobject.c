#include "langobject.h"

#include <stdlib.h>
#include <string.h>

bool lang_array_set(lang_object_t *array, size_t index, lang_object_t *value) {
  if (array == NULL || value == NULL) {
    return false;
  }
  if (array->kind != ARRAY) {
    return false;
  }
  if (array->data.v_array.size <= index) {
    return false;
  }
  
  array->data.v_array.elements[index] = value;
  return true;
}

lang_object_t *lang_array_get(lang_object_t *array, size_t index) {
  if (array == NULL) {
    return NULL;
  }
  if (array->kind != ARRAY) {
    return NULL;
  }
  if (array->data.v_array.size <= index) {
    return NULL;
  }
  
  return array->data.v_array.elements[index];
}

lang_object_t *new_lang_array(size_t size) {
  lang_object_t *obj = (lang_object_t *)malloc(sizeof(lang_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = ARRAY;

  lang_object_t **elements =
      (lang_object_t **)calloc(size, sizeof(lang_object_t *));
  if (elements == NULL) {
    return NULL;
  }

  obj->data.v_array = (lang_array_t){.size = size, .elements = elements};

  return obj;
}

lang_object_t *new_lang_pair(lang_object_t *first, lang_object_t *second) {
  if (first == NULL || second == NULL) {
    return NULL;
  }

  lang_object_t *obj = (lang_object_t *)malloc(sizeof(lang_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = PAIR;
  obj->data.v_pair = (lang_pair_t){.first = first, .second = second};

  return obj;
}

lang_object_t *new_lang_string(char *value) {
  lang_object_t *obj = (lang_object_t *)malloc(sizeof(lang_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = STRING;
  obj->data.v_string = (char *)malloc(sizeof(char) * (strlen(value) + 1));
  if (obj->data.v_string == NULL) {
    return NULL;
  }
  strcpy(obj->data.v_string, value);

  return obj;
}

lang_object_t *new_lang_float(float value) {
  lang_object_t *obj = (lang_object_t *)malloc(sizeof(lang_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;

  return obj;
}

lang_object_t *new_lang_integer(int value) {
  lang_object_t *obj = (lang_object_t *)malloc(sizeof(lang_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;

  return obj;
}