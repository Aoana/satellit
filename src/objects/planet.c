#include "planet.h"

unsigned int planet_add(gholder *gh, double x, double y, double m) {

	struct SDL_Texture *image;
	struct gfx_image *gfx_img;

	gfx_img = gfx_image_get(gh->imgl,"gfx_planet_1.png");
	if (gfx_img == NULL ) {
		LOG("ERR: Unable to get image");
		return OBJECT_ADD;
	}
	image = gfx_img->image;

	LOG("INFO: Adding planet, id=%d %f %f %f", gh->ptl->n_objs, x, y, m);
	if (object_add(gh->ptl, gh->ptl->n_objs, image, x, y, m, 0, 0) != OBJECT_OK) {
		LOG("ERR: Unable to add planet");
		return OBJECT_ADD;
	}
	return OBJECT_OK;
}

