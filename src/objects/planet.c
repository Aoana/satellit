#include "planet.h"

enum planetReturnCode planet_add(gholder *gh, double x, double y, double m) {

	struct SDL_Surface *image;
	struct gfx_image *gfx_img;

	gfx_img = gfx_get_image(gh->imgl,"gfx_planet1.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return PLANET_ADD_FAILED;
	}
	image = gfx_img->image;

	if (object_add(gh->ptl, gh->ptl->n_objs, image, x, y, m, 0, 0) != OBJECT_OK) {
		printf("ERR: Unable to add planet\n");
		return PLANET_ADD_FAILED;
	}
	return PLANET_OK;
}

