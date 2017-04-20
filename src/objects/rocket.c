#include "rocket.h"

unsigned int rocket_add(gholder *gh,
	double x, double y, double m, double vx, double vy) {

	struct SDL_Surface *image;
	gfx_image *gfx_img;

	gfx_img = gfx_get_image(gh->imgl,"gfx_ship.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return OBJECT_ADD;
	}
	image = gfx_img->image;

	if (object_add(gh->rtl, gh->rtl->n_objs, image, &rocket_update, x, y, m, vx, vy) != OBJECT_OK) {
		printf("ERR: Unable to add rocket\n");
		return OBJECT_ADD;
	}
	return OBJECT_OK;
}

unsigned int rocket_update(gholder *gh, struct object *rt) {

	if (rt->dead != 0) {
		return OBJECT_OK;
	}

	if (position_update(gh->ptl, rt) != POSITION_OK) {
		if (object_remove(gh->rtl, rt) != OBJECT_OK) {
			printf("ERR: Failed to remove object, id=%d\n", rt->id);
		}
		return OBJECT_OOB;
	}

	if (collision_planet_mult(gh->ptl, rt) != COLLISION_OK) {
		/*TODO Free the old picture*/
		gfx_image *gfx_img;
		rt->dead = 1;
		gfx_img = gfx_get_image(gh->imgl, "gfx_broken_ship.png");
		rt->image = gfx_img->image;
		return OBJECT_COL;
	}

	return OBJECT_OK;
}

unsigned int rocket_update_mult(gholder *gh) {
	enum objectReturnCode ret;
	object *obj, *tmp;
	DL_FOREACH_SAFE(gh->rtl->head, obj, tmp) {
		if (obj->dead != 0) {
			continue;
		}
		if((ret = object_update(gh->ptl, obj)) != OBJECT_OK) {
			printf("WARN: Object update failed %s, id=%d\n", object_enum2str(ret), obj->id);
			if (ret == OBJECT_COL) {
				gfx_image *gfx_img;
				obj->dead = 1;
				gfx_img = gfx_get_image(gh->imgl, "gfx_broken_ship.png");
				obj->image = gfx_img->image;
			} else {
				if (object_remove(gh->rtl, obj) != OBJECT_OK) {
					printf("ERR: Failed to remove object, id=%d\n", obj->id);
				}
			}
		}
	}
	return OBJECT_OK;
}

