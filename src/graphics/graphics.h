#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "common.h"
#include "person.h"

#define RES_WIDTH 1920
#define RES_HEIGHT 1080

struct person;
SDL_Surface *loadImage(char *);
void drawImage(SDL_Surface *, int , int);
void gfx_update_mult(struct person *);
extern SDL_Surface *screen;
#endif
