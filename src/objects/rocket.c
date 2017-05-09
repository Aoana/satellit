#include "rocket.h"

unsigned int rocket_add(gholder *gh,
	double x, double y, double m, double vx, double vy) {

	struct SDL_Texture *image;
	gfx_image *gfx_img;

	gfx_img = gfx_image_get(gh->imgl,"gfx_ship_moving.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return OBJECT_ADD;
	}
	image = gfx_img->image;

	printf("INFO: Adding rocket id=%d\n", gh->rtl->n_objs);
	if (object_add(gh->rtl, gh->rtl->n_objs, image, x, y, m, vx, vy) != OBJECT_OK) {
		printf("ERR: Unable to add rocket\n");
		return OBJECT_ADD;
	}
	return OBJECT_OK;
}

unsigned int rocket_update(gholder *gh, struct object *rt) {

	if (rt->dead != 0) {
		return OBJECT_OK;
	}

	/* Update position for rocket (gravity from planets taken into account */
	if (position_update(gh->ptl, rt) != POSITION_OK) {
		if (object_remove(gh->rtl, rt) != OBJECT_OK) {
			printf("ERR: Failed to remove object, id=%d\n", rt->id);
		}
		gh->state = STATE_GAMEOVER;
		return OBJECT_OOB;
	}

	/* Check collision for all planets */
	if (collision_object_mult(gh->ptl, rt) != COLLISION_OK) {
		rt->dead = 1;
		rt->image = (gfx_image_get(gh->imgl, "gfx_ship_broken.png"))->image;
		gh->state = STATE_GAMEOVER;
		return OBJECT_COL;
	}

	/* Check collision for goal */
	if (collision_object(gh->gbase, rt) != COLLISION_OK) {
		rt->dead = 1;
		rt->image = (gfx_image_get(gh->imgl, "gfx_ship_landed.png"))->image;
		gh->state = STATE_VICTORY;
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
		if ((ret = rocket_update(gh, obj)) != OBJECT_OK) {
			printf("WARN: Rocket update failed %s, id=%d\n", object_enum2str(ret), obj->id);
		}
	}
	return OBJECT_OK;
}

