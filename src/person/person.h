#ifndef PERSON_H
#define PERSON_H
#include "common.h"
#include "position.h"
#include "graphics.h"
#include "init.h"

struct person {
	int id;
	struct position *pos;
	SDL_Surface *image;
	struct person *next, *prev;
};

enum personReturnCode {
    PERSON_OK = 0,
    PERSON_ADD_FAILED,
    PERSON_REMOVE_FAILED,
    PERSON_UPDATE_FAILED,
};

struct person * person_init(int, char *, int, int);
struct person * person_init_mult(char *,int);
int person_destroy(struct person *);
int person_destroy_mult(struct person *);
enum personReturnCode person_add(struct person *, int, char *, int, int);
enum personReturnCode person_update(struct person *);
enum personReturnCode person_update_mult(struct person *);
#endif

