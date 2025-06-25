#include "langobject.h"

#include <stdlib.h>
#include <string.h>

lang_object_t *new_lang_pair(lang_object_t *first, lang_object_t *second) {
  if (first == NULL || second == NULL) {
    return NULL;
  }

  lang_object_t *obj = (lang_object_t *)malloc(sizeof(lang_object_t));
  if (obj == NULL) {
    return NULL;
  }
  
  obj->kind = PAIR;
  obj->data.v_pair.first = first;
  obj->data.v_pair.second = second;

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