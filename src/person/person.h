#ifndef PERSON_H
#define PERSON_H
#include "common.h"
#include "position.h"
#include "graphics.h"
#include "init.h"

struct person {
	char *name;
	struct position *pos;
	SDL_Surface *image;
	struct person *next, *prev;
};

struct person * person_init(char *, char *, int, int);
struct person * person_init_mult(char *, char *,int);
int person_destroy(struct person *);
int person_destroy_mult(struct person *);
int person_update(struct person *);
int person_update_mult(struct person *);
#endif

