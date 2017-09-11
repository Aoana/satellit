#include "moon.h"

unsigned int moon_velocity_update(object *mn) {

	static double angle = 0;
	angle += 0.05;

	mn->pos->vx = sin(angle)*MOON_R;
	mn->pos->vy = cos(angle)*MOON_R;

	return OBJECT_OK;

}

unsigned int moon_add(gholder *gh,
	double x, double y, double m, double vx, double vy) {

	struct SDL_Texture *image;
	gfx_image *gfx_img;
	object *moon;

	gfx_img = gfx_image_get(gh->imgl,"gfx_moon_moving.png");
	if (gfx_img == NULL ) {
		LOG("ERR: Unable to get image");
		return OBJECT_ADD;
	}
	image = gfx_img->image;

	LOG("INFO: Adding moon, id=%d %f %f %f %f %f", gh->mnl->n_objs, x, y, m, vx, vy);

	moon = object_init(gh->mnl->n_objs, image, x, y, m, vx, vy);
	if (moon == NULL ) {
		LOG("ERR: Unable to init moon");
		return OBJECT_ADD;
	}

	if (object_list_add(gh->mnl, moon) != OBJECT_OK) {
		LOG("ERR: Unable to add moon");
		return OBJECT_ADD;
	}
	return OBJECT_OK;
}

unsigned int moon_update(gholder *gh, struct object *mn) {

	if (mn->dead != 0) {
		return OBJECT_OK;
	}

	if (position_update(mn->pos) != POSITION_OK) {
		if (object_list_remove(gh->mnl, mn) != OBJECT_OK) {
			LOG("ERR: Failed to remove object, id=%d", mn->id);
		}
		if (object_destroy(mn) != OBJECT_OK) {
			LOG("ERR: Failed to destroy object, id=%d", mn->id);
		}
		return OBJECT_OOB;
	}

	/* Update velocity based on circular movement */
	if (moon_velocity_update(mn) != OBJECT_OK) {
		LOG("ERR: Failed to apply velocity update for moon, id=%d", mn->id);
	}

	if (collision_object_mult(gh->ptl, mn) != COLLISION_OK) {
		mn->dead = 1;
		mn->image = (gfx_image_get(gh->imgl, "gfx_moon_crash.png"))->image;
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
			LOG("WARN: Moon update failed %s, id=%d", object_enum2str(ret), obj->id);
		}
	}
	return OBJECT_OK;
}

