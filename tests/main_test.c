#include <stdlib.h>

#include "./munit/munit.h"
#include "../src/langobject.h"

static MunitResult test_integer_constant(const MunitParameter params[], void *data) {
  munit_assert_int(INTEGER, ==, 0);

  return MUNIT_OK;
}

static MunitResult test_integer_obj(const MunitParameter params[], void *data) {
  lang_object_t *obj = malloc(sizeof(lang_object_t));
  obj->kind = INTEGER;
  obj->data.v_int = 0;

  munit_assert_int(obj->kind, ==, INTEGER);
  munit_assert_int(obj->data.v_int, ==, 0);

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    {"/integer_constant", test_integer_constant, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/integer_obj", test_integer_obj, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite test_suite = {
    "object_integer_def", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
