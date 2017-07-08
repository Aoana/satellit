#include "rocket.h"

unsigned int rocket_add(gholder *gh,
	double x, double y, double m, double vx, double vy) {

	struct SDL_Texture *image;
	gfx_image *gfx_img;

	gfx_img = gfx_image_get(gh->imgl,"gfx_ship_moving.png");
	if (gfx_img == NULL ) {
		LOG("ERR: Unable to get image");
		return OBJECT_ADD;
	}
	image = gfx_img->image;

	LOG("INFO: Adding rocket id=%d", gh->rtl->n_objs);
	if (object_add(gh->rtl, gh->rtl->n_objs, image, x, y, m, vx, vy) != OBJECT_OK) {
		LOG("ERR: Unable to add rocket");
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
			LOG("ERR: Failed to remove object, id=%d", rt->id);
		}
		gh->state = STATE_GAMEOVER;
		if(audio_play_sound(gh,"src/audio/sounds/42103__marcuslee__laser-paintball.wav") != 0) {
			LOG("ERR: Could not queue audio for ship OOB");
		}
		return OBJECT_OOB;
	}

	/* Check collision for all planets */
	if (collision_object_mult(gh->ptl, rt) != COLLISION_OK) {
		rt->dead = 1;
		rt->image = (gfx_image_get(gh->imgl, "gfx_ship_broken.png"))->image;
		gh->state = STATE_GAMEOVER;
		if(audio_play_sound(gh,"src/audio/sounds/231889__zxin__crash.wav") != 0) {
			LOG("ERR: Could not queue audio for ship collision with planet");
		}
		return OBJECT_COL;
	}

	/* Check collision for goal */
	if (collision_object(gh->gbase, rt) != COLLISION_OK) {
		rt->dead = 1;
		rt->image = (gfx_image_get(gh->imgl, "gfx_ship_landed.png"))->image;
		gh->state = STATE_VICTORY;
		if(audio_play_sound(gh,"src/audio/sounds/198874__bone666138__fanfare.wav") != 0) {
			LOG("ERR: Could not queue audio for victory");
		}
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
			LOG("WARN: Rocket update failed %s, id=%d", object_enum2str(ret), obj->id);
		}
	}
	return OBJECT_OK;
}

