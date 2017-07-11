#include "object.h"
#include "CUnit/Basic.h"

/* Pointer to the file used by the tests. */
//static object_list *objl = NULL;

int init_suite(void) {
      return 0;
}

int destroy_suite(void) {
	return 0;
}

void test_object_list_init(void) {
	CU_ASSERT(0 == 0);
}

void test_object_add(void) {
	CU_ASSERT(0 == 0);
}

int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite, destroy_suite);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - Init functions first and destroy functions last */
   if ((NULL == CU_add_test(pSuite, "Test of object list", test_object_list_init)) ||
       (NULL == CU_add_test(pSuite, "Test of object add", test_object_add))) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
