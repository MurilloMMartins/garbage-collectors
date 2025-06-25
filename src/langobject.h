#pragma once

typedef enum LangObjectKind {
  INTEGER,
  FLOAT,
  STRING,
} lang_object_kind_t;

typedef union LangObjectData {
  int v_int;
  float v_float;
  char *v_string;
} lang_object_data_t;

typedef struct LangObject {
  lang_object_kind_t kind;
  lang_object_data_t data;
} lang_object_t;

lang_object_t *new_lang_integer(int value);
lang_object_t *new_lang_float(float value);
lang_object_t *new_lang_string(char *value);