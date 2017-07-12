#include "position.h"
#include "object.h"
#include "CUnit/Basic.h"

/*****************
 * Position tests
 ******************/

int init_position_suite(void) {
	return 0;
}

int destroy_position_suite(void) {
	return 0;
}

void test_position_validate(void) {
	CU_ASSERT(POSITION_OK == position_validate(SPACE_W_MIN, SPACE_H_MIN));
	CU_ASSERT(POSITION_OK == position_validate(SPACE_W_MIN, SPACE_H_MAX));
	CU_ASSERT(POSITION_OK == position_validate(SPACE_W_MAX, SPACE_H_MIN));
	CU_ASSERT(POSITION_OK == position_validate(SPACE_W_MAX, SPACE_H_MAX));
	CU_ASSERT(POSITION_OK == position_validate(SPACE_W_MIN+1, SPACE_H_MIN+1));
	CU_ASSERT(POSITION_OK == position_validate(SPACE_W_MIN+1, SPACE_H_MAX-1));
	CU_ASSERT(POSITION_OK == position_validate(SPACE_W_MAX-1, SPACE_H_MIN+1));
	CU_ASSERT(POSITION_OK == position_validate(SPACE_W_MAX-1, SPACE_H_MAX-1));
	CU_ASSERT(POSITION_ERR_OOB == position_validate(SPACE_W_MIN-1, SPACE_H_MIN));
	CU_ASSERT(POSITION_ERR_OOB == position_validate(SPACE_W_MIN, SPACE_H_MIN-1));
	CU_ASSERT(POSITION_ERR_OOB == position_validate(SPACE_W_MAX+1, SPACE_H_MAX));
	CU_ASSERT(POSITION_ERR_OOB == position_validate(SPACE_W_MAX, SPACE_H_MAX+1));
}

void test_position_init(void) {
	CU_ASSERT(0 == 0);
}

/*****************
 * Object tests
 ******************/

int init_object_suite(void) {
	return 0;
}

int destroy_object_suite(void) {
	return 0;
}

void test_object_list(void) {
	CU_ASSERT(0 == 0);
}

void test_object(void) {
	CU_ASSERT(0 == 0);
}

int main()
{
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* Add suite position and test cases */
	pSuite = NULL;
	pSuite = CU_add_suite("suite_position", init_position_suite, destroy_position_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "Test of position validation", test_position_validate)) ||
		(NULL == CU_add_test(pSuite, "Test of position init", test_position_init))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Add suite objects and test cases */
	pSuite = NULL;
	pSuite = CU_add_suite("suite_objects", init_object_suite, destroy_object_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "Test of object list", test_object_list)) ||
		(NULL == CU_add_test(pSuite, "Test of object add", test_object))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
