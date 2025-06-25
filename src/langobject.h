#pragma once

typedef struct LangObject lang_object_t;

typedef enum LangObjectKind {
  INTEGER,
  FLOAT,
  STRING,
  PAIR,
} lang_object_kind_t;

typedef struct LangPair {
  lang_object_t *first;
  lang_object_t *second;
} lang_pair_t;

typedef union LangObjectData {
  int v_int;
  float v_float;
  char *v_string;
  lang_pair_t v_pair;
} lang_object_data_t;

typedef struct LangObject {
  lang_object_kind_t kind;
  lang_object_data_t data;
} lang_object_t;

lang_object_t *new_lang_integer(int value);
lang_object_t *new_lang_float(float value);
lang_object_t *new_lang_string(char *value);
lang_object_t *new_lang_pair(lang_object_t *first, lang_object_t *second);