#include <stdlib.h>

#include "../src/langobject.h"
#include "./munit/munit.h"

/*
  INTEGER OBJECT TESTS
*/
static MunitResult test_integer_constant(const MunitParameter params[],
                                         void *data) {
  munit_assert_int(INTEGER, ==, 0);

  return MUNIT_OK;
}

static MunitResult test_integer_obj(const MunitParameter params[], void *data) {
  lang_object_t *obj = malloc(sizeof(lang_object_t));
  obj->kind = INTEGER;
  obj->data.v_int = 0;

  munit_assert_int(obj->kind, ==, INTEGER);
  munit_assert_int(obj->data.v_int, ==, 0);

  free(obj);

  return MUNIT_OK;
}

static MunitResult test_positive(const MunitParameter params[], void *data) {
  lang_object_t *int_object = new_lang_integer(42);
  munit_assert_int(int_object->kind, ==, INTEGER);
  munit_assert_int(int_object->data.v_int, ==, 42);

  free(int_object);

  return MUNIT_OK;
}

static MunitResult test_zero(const MunitParameter params[], void *data) {
  lang_object_t *int_object = new_lang_integer(0);
  munit_assert_int(int_object->kind, ==, INTEGER);
  munit_assert_int(int_object->data.v_int, ==, 0);

  free(int_object);

  return MUNIT_OK;
}

static MunitResult test_negative(const MunitParameter params[], void *data) {
  lang_object_t *int_object = new_lang_integer(-5);
  munit_assert_int(int_object->kind, ==, INTEGER);
  munit_assert_int(int_object->data.v_int, ==, -5);

  free(int_object);

  return MUNIT_OK;
}

/*
  CREATING TEST SUITE
*/
static MunitTest test_suite_tests[] = {
    {"/integer_constant", test_integer_constant, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/integer_obj", test_integer_obj, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/positive", test_positive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/zero", test_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/negative", test_negative, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite test_suite = {
    "object_integer", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};

/*
  RUNNING TESTS
*/
int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
