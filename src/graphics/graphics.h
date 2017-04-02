#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"
#include "person.h"

#define UPDATE_FREQ 200

struct person;

struct gfx_image {
	int id;
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
void gfx_update_screen(struct person *);
struct gfx_image_list * gfx_init_images(void);
extern SDL_Surface *screen;

#endif
