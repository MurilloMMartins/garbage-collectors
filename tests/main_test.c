#include <stdlib.h>

#include "../src/langobject.h"
#include "./munit/munit.h"

/*
  INTEGER OBJECT TESTS
*/
static MunitResult integer_test_positive(const MunitParameter params[],
                                         void *data) {
  lang_object_t *int_object = new_lang_integer(42);
  munit_assert_int(int_object->kind, ==, INTEGER);
  munit_assert_int(int_object->data.v_int, ==, 42);

  free(int_object);

  return MUNIT_OK;
}

static MunitResult integer_test_zero(const MunitParameter params[],
                                     void *data) {
  lang_object_t *int_object = new_lang_integer(0);
  munit_assert_int(int_object->kind, ==, INTEGER);
  munit_assert_int(int_object->data.v_int, ==, 0);

  free(int_object);

  return MUNIT_OK;
}

static MunitResult integer_test_negative(const MunitParameter params[],
                                         void *data) {
  lang_object_t *int_object = new_lang_integer(-5);
  munit_assert_int(int_object->kind, ==, INTEGER);
  munit_assert_int(int_object->data.v_int, ==, -5);

  free(int_object);

  return MUNIT_OK;
}

static MunitTest integer_tests[] = {
    {"/positive", integer_test_positive, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/zero", integer_test_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/negative", integer_test_negative, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite integer_suite = {
    "integer_object", integer_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};

/*
  FLOAT OBJECT TESTS
*/
static MunitResult float_test_positive(const MunitParameter params[],
                                       void *data) {
  lang_object_t *obj = new_lang_float(42);
  munit_assert_int(obj->kind, ==, FLOAT);
  munit_assert_float(obj->data.v_float, ==, 42);

  free(obj);

  return MUNIT_OK;
}

static MunitResult float_test_zero(const MunitParameter params[], void *data) {
  lang_object_t *obj = new_lang_float(0.0);
  munit_assert_int(obj->kind, ==, FLOAT);
  munit_assert_float(obj->data.v_float, ==, 0.0);

  free(obj);

  return MUNIT_OK;
}

static MunitResult float_test_negative(const MunitParameter params[],
                                       void *data) {
  lang_object_t *obj = new_lang_float(-5.0);
  munit_assert_int(obj->kind, ==, FLOAT);
  munit_assert_float(obj->data.v_float, ==, -5.0);

  free(obj);

  return MUNIT_OK;
}

static MunitTest float_tests[] = {
    {"/positive", float_test_positive, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/zero", float_test_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/negative", float_test_negative, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite float_suite = {
    "float_object", float_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};

/*
  STRING OBJECT TESTS
*/
static MunitResult string_test(const MunitParameter params[], void *data) {
  char *input = "Hello, World!";
  lang_object_t *obj = new_lang_string(input);

  munit_assert_int(obj->kind, ==, STRING);
  munit_assert_ptr_not_equal(obj->data.v_string, input);
  munit_assert_string_equal(obj->data.v_string, input);

  free(obj->data.v_string);
  free(obj);

  return MUNIT_OK;
}

static MunitTest string_tests[] = {
    {"/str_copied", string_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite string_suite = {
    "string_object", string_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};

/*
  PAIR OBJECT TEST
*/
static MunitResult pair_returns_null(const MunitParameter params[],
                                     void *data) {
  lang_object_t *pair = new_lang_pair(NULL, NULL);

  munit_assert_null(pair);

  return MUNIT_OK;
}

static MunitResult pair_multiple_objects(const MunitParameter params[],
                                         void *data) {
  lang_object_t *first = new_lang_integer(1);
  lang_object_t *second = new_lang_integer(2);
  lang_object_t *pair = new_lang_pair(first, second);

  munit_assert_ptr_not_null(pair);

  munit_assert_ptr(first, ==, pair->data.v_pair.first);
  munit_assert_ptr(second, ==, pair->data.v_pair.second);

  munit_assert_int(pair->data.v_pair.first->data.v_int, ==, 1);
  munit_assert_int(pair->data.v_pair.second->data.v_int, ==, 2);

  free(first);
  free(second);
  free(pair);

  return MUNIT_OK;
}

static MunitResult pair_same_object(const MunitParameter params[], void *data) {
  lang_object_t *obj = new_lang_integer(1);
  lang_object_t *pair = new_lang_pair(obj, obj);

  munit_assert_ptr_not_null(pair);

  munit_assert_ptr(obj, ==, pair->data.v_pair.first);
  munit_assert_ptr(obj, ==, pair->data.v_pair.second);

  munit_assert_int(pair->data.v_pair.first->data.v_int, ==, 1);
  munit_assert_int(pair->data.v_pair.second->data.v_int, ==, 1);

  obj->data.v_int = 2;

  munit_assert_int(pair->data.v_pair.first->data.v_int, ==, 2);
  munit_assert_int(pair->data.v_pair.second->data.v_int, ==, 2);

  free(obj);
  free(pair);

  return MUNIT_OK;
}

static MunitTest pair_tests[] = {
    {"/returns_null", pair_returns_null, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/multiple_object", pair_multiple_objects, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/same_object", pair_same_object, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite pair_suite = {
    "pair_object", pair_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};

/*
  ARRAY OBJECT TESTS
*/
static MunitResult array_create_empty_array(const MunitParameter params[],
                                            void *data) {
  lang_object_t *obj = new_lang_array(2);

  munit_assert_int(obj->kind, ==, ARRAY);
  munit_assert_int(obj->data.v_array.size, ==, 2);

  free(obj->data.v_array.elements);
  free(obj);

  return MUNIT_OK;
}

static MunitResult array_used_calloc(const MunitParameter params[],
                                     void *data) {
  lang_object_t *obj = new_lang_array(2);

  munit_assert_ptr_null(obj->data.v_array.elements[0]);
  munit_assert_ptr_null(obj->data.v_array.elements[1]);

  free(obj->data.v_array.elements);
  free(obj);

  return MUNIT_OK;
}

static MunitResult array_test_get_and_set(const MunitParameter params[],
                                          void *data) {
  lang_object_t *obj = new_lang_array(2);

  lang_object_t *first = new_lang_string("First");
  lang_object_t *second = new_lang_integer(3);

  munit_assert(lang_array_set(obj, 0, first));
  munit_assert(lang_array_set(obj, 1, second));

  lang_object_t *retrieved_first = lang_array_get(obj, 0);
  munit_assert_not_null(retrieved_first);
  munit_assert_int(retrieved_first->kind, ==, STRING);
  munit_assert_ptr(first, ==, retrieved_first);

  lang_object_t *retrieved_second = lang_array_get(obj, 1);
  munit_assert_not_null(retrieved_second);
  munit_assert_int(retrieved_second->kind, ==, INTEGER);
  munit_assert_ptr(second, ==, retrieved_second);

  free(first->data.v_string);
  free(first);
  free(second);
  free(obj->data.v_array.elements);
  free(obj);

  return MUNIT_OK;
}

static MunitResult array_test_set_outside_bounds(const MunitParameter params[],
                                                 void *data) {
  lang_object_t *obj = new_lang_array(2);

  lang_object_t *outside = new_lang_string("First");

  munit_assert(lang_array_set(obj, 0, outside));

  munit_assert_false(lang_array_set(obj, 100, outside));

  free(outside->data.v_string);
  free(outside);
  free(obj->data.v_array.elements);
  free(obj);

  return MUNIT_OK;
}

static MunitResult array_test_get_outside_bounds(const MunitParameter params[],
                                                 void *data) {
  lang_object_t *obj = new_lang_array(1);
  lang_object_t *first = new_lang_string("First");
  munit_assert(lang_array_set(obj, 0, first));

  munit_assert_null(lang_array_get(obj, 1));

  free(first->data.v_string);
  free(first);
  free(obj->data.v_array.elements);
  free(obj);

  return MUNIT_OK;
}

static MunitTest array_tests[] = {
    {"/empty", array_create_empty_array, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/used_calloc", array_used_calloc, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/get_and_set", array_test_get_and_set, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/set_outside_bounds", array_test_set_outside_bounds, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/get_outside_bounds", array_test_get_outside_bounds, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite array_suite = {
    "array_object", array_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};

/*
  CREATING TEST SUITE
*/
static const MunitSuite test_suite = {
    "",
    NULL,
    (MunitSuite[]){integer_suite,
                   float_suite,
                   string_suite,
                   pair_suite,
                   array_suite,
                   {NULL}},
    1,
    MUNIT_SUITE_OPTION_NONE,
};

/*
  RUNNING TESTS
*/
int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
