#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"
#include "rocket.h"
#include "planet.h"

#define UPDATE_FREQ 25

struct gholder;

typedef struct gfx_image {
	char *name;
	SDL_Surface *image;	
	TTF_Font* font;
	SDL_Color fontcolor;
	struct gfx_image *next, *prev;
} gfx_image;

typedef struct gfx_image_list {
	int n_images;
	struct gfx_image *head;	
} gfx_image_list;

SDL_Surface *gfx_load_image(char *);
void gfx_draw_image(SDL_Surface *, int, int);
void gfx_update_screen(struct gholder *);
gfx_image_list * gfx_init_images(void);
gfx_image_list * gfx_init_texts(void);
void gfx_change_text(gfx_image_list *, char *, char *);
gfx_image * gfx_get_image(gfx_image_list *, char *);
void gfx_destroy_images(gfx_image_list *);
void gfx_destroy_texts(gfx_image_list *txtl);

extern SDL_Surface *screen;

#endif
