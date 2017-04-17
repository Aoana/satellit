#include "rocket.h"

enum rocketReturnCode rocket_add(gholder *gh,
	double x, double y, double m, double vx, double vy) {

	struct SDL_Surface *image;
	gfx_image *gfx_img;

	gfx_img = gfx_get_image(gh->imgl,"gfx_ship.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return ROCKET_ADD_FAILED;
	}
	image = gfx_img->image;

	if (object_add(gh->rtl, gh->rtl->n_objs, image, x, y, m, vx, vy) != OBJECT_OK) {
		printf("ERR: Unable to add rocket\n");
		return ROCKET_ADD_FAILED;
	}
	return ROCKET_OK;
}

enum rocketReturnCode rocket_update_mult(gholder *gh) {
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
	return ROCKET_OK;
}

