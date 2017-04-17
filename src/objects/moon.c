#include "moon.h"

enum moonReturnCode moon_add(object_list *mnl, gfx_image_list *imgl,
	double x, double y, double m, double vx, double vy) {

	struct SDL_Surface *image;
	gfx_image *gfx_img;

	gfx_img = gfx_get_image(imgl,"gfx_moon.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return MOON_ADD_FAILED;
	}
	image = gfx_img->image;

	if (object_add(mnl, mnl->n_objs, image, x, y, m, vx, vy) != OBJECT_OK) {
		printf("ERR: Unable to add moon\n");
		return MOON_ADD_FAILED;
	}
	return MOON_OK;
}

