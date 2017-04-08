#include "planet.h"

struct planet_list * planet_list_init() {
	struct planet_list *ptl;
	ptl = calloc(1, sizeof(struct planet_list));
	ptl->n_pts = 0;
	ptl->head = NULL;
	return ptl;
}

int planet_list_destroy(struct planet_list *ptl) {
	free(ptl);
	return 0;
}

struct planet * planet_init(int id, SDL_Surface *image, int x, int y, int m) {
	struct planet *pt;
	pt = calloc(1, sizeof(struct planet));
	pt->id = id;
	pt->mass = m;
	pt->next = NULL;
	pt->prev = NULL;

	pt->pos = position_init(x, y, 0, 0);
	if (pt->pos == NULL) {
		printf("ERR: Unable to init position %d,%d\n", x, y);
		free(pt);
		return NULL;
	}

	pt->image = image;

	return pt;
}

int planet_destroy(struct planet *pt) {
	position_destroy(pt->pos);
	free(pt);
	return 0;
}

enum planetReturnCode planet_add(struct planet_list *ptl, int id,
									SDL_Surface *image, int x, int y, int m) {
	struct planet *pt;
	pt = planet_init(id, image, x, y, m);
	if (pt == NULL) {
		printf("WARN: Unable to init planet number\n");
		return PLANET_ADD_FAILED;
	}
	DL_APPEND(ptl->head, pt);
	ptl->n_pts++;
	return PLANET_OK;
}

enum planetReturnCode planet_add_planet1(struct planet_list *ptl, struct gfx_image_list *imgl,
										 int x, int y, int m) {

	struct SDL_Surface *image;
	struct gfx_image *gfx_img;

	gfx_img = gfx_get_image(imgl,"gfx_planet1.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return PLANET_ADD_FAILED;
	}
	image = gfx_img->image;

	if (planet_add(ptl, ptl->n_pts, image, x, y, m) != PLANET_OK) {
		printf("ERR: Unable to add planet\n");
		return PLANET_ADD_FAILED;
	}
	return PLANET_OK;
}

enum planetReturnCode planet_remove(struct planet_list *ptl, struct planet *pt) {
	DL_DELETE(ptl->head,pt);
	if(planet_destroy(pt) != PLANET_OK) {
		return PLANET_REMOVE_FAILED;
	}
	ptl->n_pts--;
	return PLANET_OK;
}

enum planetReturnCode planet_remove_mult(struct planet_list *ptl) {
	struct planet *pt, *tmp;
	DL_FOREACH_SAFE(ptl->head,pt,tmp) {
		if(planet_remove(ptl, pt) != PLANET_OK) {
			return PLANET_REMOVE_FAILED;
		}
    }
	return PLANET_OK;
}

enum planetReturnCode planet_remove_id(struct planet_list *ptl, int id) {
	struct planet *pt, *tmp;
	DL_FOREACH_SAFE(ptl->head,pt,tmp) {
		if (pt->id == id) {
			DL_DELETE(ptl->head,pt);
			if(planet_destroy(pt) != PLANET_OK) {
				return PLANET_REMOVE_FAILED;
			}
			return PLANET_OK;
		}
    }
	return PLANET_NOT_FOUND;
}

