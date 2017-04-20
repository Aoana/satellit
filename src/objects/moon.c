#include "moon.h"

unsigned int moon_add(gholder *gh,
	double x, double y, double m, double vx, double vy) {

	struct SDL_Surface *image;
	gfx_image *gfx_img;

	gfx_img = gfx_get_image(gh->imgl,"gfx_moon.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return OBJECT_ADD;
	}
	image = gfx_img->image;

	/*TODO: Define an update function for moon*/
	if (object_add(gh->mnl, gh->mnl->n_objs, image, NULL, x, y, m, vx, vy) != OBJECT_OK) {
		printf("ERR: Unable to add moon\n");
		return OBJECT_ADD;
	}
	return OBJECT_ADD;
}

