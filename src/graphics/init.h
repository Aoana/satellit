#ifndef INIT_H
#define INIT_H

#include "common.h"

void gfx_init(char *, int , int );
void gfx_cleanup(SDL_Surface *);
extern SDL_Surface *screen;
#endif
