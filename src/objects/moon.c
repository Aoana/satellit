#include "moon.h"

enum moonReturnCode moon_add(gholder *gh,
	double x, double y, double m, double vx, double vy) {

	struct SDL_Surface *image;
	gfx_image *gfx_img;

	gfx_img = gfx_get_image(gh->imgl,"gfx_moon.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return MOON_ADD_FAILED;
	}
	image = gfx_img->image;

	if (object_add(gh->mnl, gh->mnl->n_objs, image, x, y, m, vx, vy) != OBJECT_OK) {
		printf("ERR: Unable to add moon\n");
		return MOON_ADD_FAILED;
	}
	return MOON_OK;
}

