#include "planet.h"

unsigned int planet_add(gholder *gh, double x, double y, double m) {

	struct SDL_Surface *image;
	struct gfx_image *gfx_img;

	gfx_img = gfx_get_image(gh->imgl,"gfx_planet1.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return OBJECT_ADD;
	}
	image = gfx_img->image;

	printf("INFO: Adding planet, id=%d\n", gh->ptl->n_objs);
	if (object_add(gh->ptl, gh->ptl->n_objs, image, x, y, m, 0, 0) != OBJECT_OK) {
		printf("ERR: Unable to add planet\n");
		return OBJECT_ADD;
	}
	return OBJECT_OK;
}

