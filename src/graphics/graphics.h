#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"
#include "person.h"
#include "planet.h"

#define UPDATE_FREQ 25

struct object;

struct gfx_image {
	char *name;
	SDL_Surface *image;	
	struct gfx_image *next, *prev;
};

struct gfx_image_list {
	int n_images;
	struct gfx_image *head;	
};

SDL_Surface *gfx_load_image(char *);
void gfx_draw_image(SDL_Surface *, int, int);
void gfx_update_screen(struct object *, struct object *);
struct gfx_image_list * gfx_init_images(void);
struct gfx_image * gfx_get_image(struct gfx_image_list *, char *);
void gfx_destroy_images(struct gfx_image_list *);
extern SDL_Surface *screen;

#endif
