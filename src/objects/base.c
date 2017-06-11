#include "base.h"

unsigned int base_add(gholder *gh, int type, double x, double y) {

	gfx_image *gfx_img;
	object *base;

	if (type == 0) {
		gfx_img = gfx_image_get(gh->imgl,"gfx_base_home.png");
		LOG("INFO: Adding home base, id=%d %f %f", type, x, y);
	} else if (type == 1) {
		LOG("INFO: Adding goal base, id=%d %f %f", type, x, y);
		gfx_img = gfx_image_get(gh->imgl,"gfx_base_goal.png");
	} else {
		LOG("ERR: %s called with wrong type", __func__);
		exit(1);
	}

	if (gfx_img == NULL) {
		LOG("ERR: Unable to get image");
		return OBJECT_ADD;
	}

	base = object_init(type, gfx_img->image, x, y, 0, 0, 0);
	if (base == NULL) {
		LOG("ERR: Unable to initialize base");
		return OBJECT_ADD;
	}

	if (type == 0) {
		gh->hbase = base;
	} else {
		gh->gbase = base;
	}

	return OBJECT_OK;
}

