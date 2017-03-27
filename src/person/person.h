#include "common.h"
#include "position.h"
#include "graphics.h"
#include "init.h"

struct person {
	char *name;
	struct position *pos;
	SDL_Surface *image;
};

struct person * person_init(char *, char *, int, int);
int person_destroy(struct person *);
int person_update(struct person *);
int person_init_mult(int);

