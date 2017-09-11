#include "rocket.h"

unsigned int rocket_gravity_update(object_list *ptl, object *rt) {

	double a_x = 0, a_y = 0;
	double f_x = 0, f_y = 0;
	double dx, dy, d;
	object *pt;
	position *p = rt->pos;

	DL_FOREACH(ptl->head, pt) {
		dx = pt->pos->x - p->x;
		dy = pt->pos->y - p->y;
		d = sqrt(pow(dx,2)+pow(dy,2));
		f_x = f_x + (GRAV_CONST*pt->mass*rt->mass*dx)/pow(d,3);
		f_y = f_y + (GRAV_CONST*pt->mass*rt->mass*dy)/pow(d,3);
	}
	a_x = f_x/rt->mass;
	a_y = f_y/rt->mass;

	p->vx = p->vx + a_x/UPDATE_FREQ;
	p->vy = p->vy + a_y/UPDATE_FREQ;

	return OBJECT_OK;

}

unsigned int rocket_add(gholder *gh,
	double x, double y, double m, double vx, double vy) {

	struct SDL_Texture *image;
	gfx_image *gfx_img;
	object *rocket;

	gfx_img = gfx_image_get(gh->imgl,"gfx_ship_moving.png");
	if (gfx_img == NULL ) {
		LOG("ERR: Unable to get image");
		return OBJECT_ADD;
	}
	image = gfx_img->image;

	LOG("INFO: Adding rocket id=%d", gh->rtl->n_objs);
	rocket = object_init(gh->rtl->n_objs, image, x, y, m, vx, vy);
	if (rocket == NULL ) {
		LOG("ERR: Unable to init rocket");
		return OBJECT_ADD;
	}
	if (object_list_add(gh->rtl, rocket) != OBJECT_OK) {
		LOG("ERR: Unable to add rocket");
		return OBJECT_ADD;
	}
	return OBJECT_OK;
}

unsigned int rocket_update(gholder *gh, struct object *rt) {

	if (rt->dead != 0) {
		return OBJECT_OK;
	}

	/* Update position for rocket */
	if (position_update(rt->pos) != POSITION_OK) {
		if (object_list_remove(gh->rtl, rt) != OBJECT_OK) {
			LOG("ERR: Failed to remove object, id=%d", rt->id);
		}
		if (object_destroy(rt) != OBJECT_OK) {
			LOG("ERR: Failed to destroy object, id=%d", rt->id);
		}
		gh->state = STATE_GAMEOVER;
		if(audio_play_sound(gh,"src/audio/sounds/42103__marcuslee__laser-paintball.wav") != 0) {
			LOG("ERR: Could not queue audio for ship OOB");
		}
		return OBJECT_OOB;
	}

	/* Update velocity based on gravity */
	if (rocket_gravity_update(gh->ptl, rt) != OBJECT_OK) {
		LOG("ERR: Failed to apply gravity update for rocket, id=%d", rt->id);
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

