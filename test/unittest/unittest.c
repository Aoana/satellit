#include "position.h"
#include "object.h"
#include "graphics.h"
#include "CUnit/Basic.h"

/*****************
 * Position tests
 ******************/

position *pos = NULL;

int init_position_suite(void) {
	pos = position_init(SPACE_H_MAX-1, SPACE_H_MAX-1, 0, 0);
	if(pos == NULL) {
		return 1;
	}
	return 0;
}

int destroy_position_suite(void) {
	if(position_destroy(pos) != 0) {
		return 1;
	}
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

void test_position_update(void) {

	position p1 = {SPACE_W_MIN, SPACE_H_MIN, 1, 1};
	position p2 = {SPACE_W_MIN, SPACE_H_MAX, 1, -1};
	position p3 = {SPACE_W_MAX, SPACE_H_MIN, -1, 1};
	position p4 = {SPACE_W_MAX, SPACE_H_MAX, -1, -1};

	position p5 = {SPACE_W_MIN, SPACE_H_MIN, -1, 0};
	position p6 = {SPACE_W_MIN, SPACE_H_MIN, 0, -1};
	position p7 = {SPACE_W_MAX, SPACE_H_MAX, 1, 0};
	position p8 = {SPACE_W_MAX, SPACE_H_MAX, 0, 1};

	CU_ASSERT(POSITION_OK == position_update(&p1));
	CU_ASSERT(POSITION_OK == position_update(&p2));
	CU_ASSERT(POSITION_OK == position_update(&p3));
	CU_ASSERT(POSITION_OK == position_update(&p4));

	CU_ASSERT(POSITION_ERR_OOB == position_update(&p5));
	CU_ASSERT(POSITION_ERR_OOB == position_update(&p6));
	CU_ASSERT(POSITION_ERR_OOB == position_update(&p7));
	CU_ASSERT(POSITION_ERR_OOB == position_update(&p8));
}

/*****************
 * Object tests
 ******************/

object_list *objl = NULL;
object_list *objlN = NULL;
object *obj1 = NULL;
object *obj2 = NULL;
object *obj3 = NULL;
object *obj4 = NULL;
object *objN = NULL;

int init_object_suite(void) {

	objl = object_list_init();
	obj1 = object_init(1, NULL, SPACE_W_MIN, SPACE_H_MIN, 10, 11, 12);
	obj2 = object_init(2, NULL, SPACE_W_MIN, SPACE_H_MAX, 20, 21, 22);
	obj3 = object_init(3, NULL, SPACE_W_MAX, SPACE_H_MIN, 30, 31, 32);
	obj4 = object_init(4, NULL, SPACE_W_MAX, SPACE_H_MAX, 40, 41, 42);
	if (objl == NULL || obj1 == NULL || obj2 == NULL ||
		obj3 == NULL || obj4 == NULL) {
		return 1;
	}
	return 0;
}

int destroy_object_suite(void) {

	object_destroy(obj1);
	object_destroy(obj2);
	object_destroy(obj3);
	object_destroy(obj4);
	object_list_destroy(objl);
	return 0;
}

void test_object_list_add(void) {

	CU_ASSERT(OBJECT_ADD == object_list_add(objlN, obj1));
	CU_ASSERT(OBJECT_ADD == object_list_add(objl, objN));

	CU_ASSERT(OBJECT_OK == object_list_add(objl, obj1));
	CU_ASSERT(OBJECT_OK == object_list_add(objl, obj2));
	CU_ASSERT(OBJECT_OK == object_list_add(objl, obj3));
	CU_ASSERT(OBJECT_OK == object_list_add(objl, obj4));
}

void test_object_list_remove(void) {

	CU_ASSERT(OBJECT_REM == object_list_remove(objlN, obj1));
	CU_ASSERT(OBJECT_REM == object_list_remove(objl, objN));

	CU_ASSERT(OBJECT_OK == object_list_remove(objl, obj2));
	CU_ASSERT(OBJECT_OK == object_list_remove(objl, obj1));
	CU_ASSERT(OBJECT_OK == object_list_remove(objl, obj4));
	CU_ASSERT(OBJECT_OK == object_list_remove(objl, obj3));
}

void test_object_list_cleanup(void) {

	CU_ASSERT(OBJECT_OK == object_list_clean_all(objlN));

	CU_ASSERT(OBJECT_OK == object_list_add(objl, obj1));
	CU_ASSERT(OBJECT_OK == object_list_add(objl, obj2));
	CU_ASSERT(OBJECT_OK == object_list_add(objl, obj3));
	CU_ASSERT(OBJECT_OK == object_list_add(objl, obj4));

	CU_ASSERT(OBJECT_OK == object_list_clean_all(objl));

	obj1 = object_init(1, NULL, SPACE_W_MIN, SPACE_H_MIN, 10, 11, 12);
	obj2 = object_init(2, NULL, SPACE_W_MIN, SPACE_H_MAX, 20, 21, 22);
	obj3 = object_init(3, NULL, SPACE_W_MAX, SPACE_H_MIN, 30, 31, 32);
	obj4 = object_init(4, NULL, SPACE_W_MAX, SPACE_H_MAX, 40, 41, 42);
}

/*****************
 * Graphics tests
 ******************/

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
gfx_image_list *gfxl = NULL;
gfx_image *image = NULL;
gfx_text *text = NULL;

int init_graphics_suite(void) {

	if (gfx_screen_init("test_screen", 1920, 1080, &window, &renderer) != 0) {
		return 1;
	}
	gfxl = gfx_image_list_init();
	if (gfxl == NULL) {
		return 1;
	}
	image = gfx_image_init("test");
	if (image == NULL) {
		return 1;
	}

	return 0;

}

int destroy_graphics_suite(void) {

	gfx_image_destroy(image);
	gfx_image_list_destroy(gfxl);
	gfx_screen_destroy(window, renderer);
	return 0;
}

void test_gfx_image_load(void) {

	CU_ASSERT(GRAPHICS_ARG == gfx_image_load(NULL, image, "test/unittest/images/passing.png"));
	CU_ASSERT(GRAPHICS_ARG == gfx_image_load(renderer, NULL, "test/unittest/images/passing.png"));

	CU_ASSERT(GRAPHICS_SDL == gfx_image_load(renderer, image, "test/unittest/images/faulty.png"));
	CU_ASSERT(GRAPHICS_SDL == gfx_image_load(renderer, image, "test/unittest/images/DOESNOTEXIST.png"));
	CU_ASSERT(GRAPHICS_SDL == gfx_image_load(renderer, image, "test/unittest/images/DOESNOTEXIST"));

	CU_ASSERT(GRAPHICS_OK == gfx_image_load(renderer, image, "test/unittest/images/passing.png"));
	CU_ASSERT(GRAPHICS_OK == gfx_image_load(renderer, image, "test/unittest/images/passing.jpg"));
}

/*****************
 * Utility tests
 ******************/

int init_util_suite(void) {

	system("rm -f /tmp/tmp.log");
	if (log_init("/tmp/tmp.log") != 0) {
		return 1;
	}
	return 0;

}

int destroy_util_suite(void) {

	if (log_destroy() != 0) {
		return 1;
	}
	return 0;

}

void test_log(void) {

	LOG("AAA");
	LOG("BBB%d",1);
	LOG("CCC%f",3.14);
	LOG("DDD%s","ddd");

	CU_ASSERT(0 == system("grep -q AAA /tmp/tmp.log"));
	CU_ASSERT(0 == system("grep -q BBB1 /tmp/tmp.log"));
	CU_ASSERT(0 == system("grep -q CCC3.14 /tmp/tmp.log"));
	CU_ASSERT(0 == system("grep -q DDDddd /tmp/tmp.log"));

}

int main()
{
	CU_pSuite pSuite = NULL;
	unsigned int ret;

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
	if ((NULL == CU_add_test(pSuite, "Validation of position", test_position_validate)) ||
		(NULL == CU_add_test(pSuite, "Initializiation of position", test_position_update))) {
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
	if ((NULL == CU_add_test(pSuite, "Adding object", test_object_list_add)) ||
		(NULL == CU_add_test(pSuite, "Removing objects", test_object_list_remove)) ||
		(NULL == CU_add_test(pSuite, "Cleanup object list", test_object_list_cleanup))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Add suite graphics and test cases */
	pSuite = NULL;
	pSuite = CU_add_suite("suite_graphics", init_graphics_suite, destroy_graphics_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "Loading images", test_gfx_image_load))) {
//		(NULL == CU_add_test(pSuite, "Removing objects", test_object_list_remove)) ||
//		(NULL == CU_add_test(pSuite, "Cleanup object list", test_object_list_cleanup))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Add suite log and test cases */
	pSuite = NULL;
	pSuite = CU_add_suite("suite_util", init_util_suite, destroy_util_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "Log macro", test_log)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	ret = CU_get_number_of_failures();
	CU_cleanup_registry();
	return ret;
}
