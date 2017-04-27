#include "base.h"

unsigned int base_add(gholder *gh, int type, double x, double y) {

	gfx_image *gfx_img;
	object *base;

	if (type == 0) {
		gfx_img = gfx_get_image(gh->imgl,"gfx_base_home.png");
		printf("INFO: Adding home base, id=%d\n", type);
	} else if (type == 1) {
		printf("INFO: Adding goal base, id=%d\n", type);
		gfx_img = gfx_get_image(gh->imgl,"gfx_base_goal.png");
	} else {
		printf("ERR: %s called with wrong type", __func__);
		exit(1);
	}

	if (gfx_img == NULL) {
		printf("ERR: Unable to get image\n");
		return OBJECT_ADD;
	}

	base = object_init(type, gfx_img->image, x, y, 0, 0, 0);
	if (base == NULL) {
		printf("ERR: Unable to initialize base\n");
		return OBJECT_ADD;
	}

	if (type == 0) {
		gh->hbase = base;
	} else {
		gh->gbase = base;
	}

	return OBJECT_OK;
}

