#include "common.h"

#define RES_WIDTH 1920
#define RES_HEIGHT 1080

SDL_Surface *loadImage(char *);
void updateScreen(SDL_Surface *, int, int);
void drawImage(SDL_Surface *, int , int);
extern SDL_Surface *screen;
