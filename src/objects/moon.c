#include "moon.h"

unsigned int moon_add(gholder *gh,
	double x, double y, double m, double vx, double vy) {

	struct SDL_Surface *image;
	gfx_image *gfx_img;

	gfx_img = gfx_get_image(gh->imgl,"gfx_moon.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return OBJECT_ADD;
	}
	image = gfx_img->image;

	printf("INFO: Adding moon, id=%d\n", gh->mnl->n_objs);
	if (object_add(gh->mnl, gh->mnl->n_objs, image, x, y, m, vx, vy) != OBJECT_OK) {
		printf("ERR: Unable to add moon\n");
		return OBJECT_ADD;
	}
	return OBJECT_OK;
}

unsigned int moon_update(gholder *gh, struct object *mn) {

	if (mn->dead != 0) {
		return OBJECT_OK;
	}

	if (position_update(gh->ptl, mn) != POSITION_OK) {
		if (object_remove(gh->mnl, mn) != OBJECT_OK) {
			printf("ERR: Failed to remove object, id=%d\n", mn->id);
		}
		return OBJECT_OOB;
	}

	if (collision_object_mult(gh->ptl, mn) != COLLISION_OK) {
		gfx_image *gfx_img;
		mn->dead = 1;
		gfx_img = gfx_get_image(gh->imgl, "gfx_moon_crash.png");
		mn->image = gfx_img->image;
		return OBJECT_COL;
	}

	return OBJECT_OK;
}

unsigned int moon_update_mult(gholder *gh) {
	enum objectReturnCode ret;
	object *obj, *tmp;
	DL_FOREACH_SAFE(gh->mnl->head, obj, tmp) {
		if (obj->dead != 0) {
			continue;
		} 
		if ((ret = moon_update(gh, obj)) != OBJECT_OK) {
			printf("WARN: Moon update failed %s, id=%d\n", object_enum2str(ret), obj->id);
		}
	}
	return OBJECT_OK;
}

