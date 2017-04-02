#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"
#include "person.h"

#define UPDATE_FREQ 200

struct person;

SDL_Surface *gfx_load_image(char *);
void gfx_draw_image(SDL_Surface *, int, int);
void gfx_update_screen(struct person *);
extern SDL_Surface *screen;

#endif
