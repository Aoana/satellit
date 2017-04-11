#include "person.h"

enum rocketReturnCode rocket_add(struct object_list *pnl, struct gfx_image_list *imgl,
	double x, double y, double m, double vx, double vy) {

	struct SDL_Surface *image;
	struct gfx_image *gfx_img;

	gfx_img = gfx_get_image(imgl,"gfx_ship.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return ROCKET_ADD_FAILED;
	}
	image = gfx_img->image;

	if (object_add(pnl, pnl->n_objs, image, x, y, m, vx, vy) != OBJECT_OK) {
		printf("ERR: Unable to add rocket\n");
		return ROCKET_ADD_FAILED;
	}
	return ROCKET_OK;
}

