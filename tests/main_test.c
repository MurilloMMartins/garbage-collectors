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
  CREATING TEST SUITE
*/
static const MunitSuite test_suite = {
    "",
    NULL,
    (MunitSuite[]){integer_suite, float_suite, {NULL}},
    1,
    MUNIT_SUITE_OPTION_NONE,
};

/*
  RUNNING TESTS
*/
int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
