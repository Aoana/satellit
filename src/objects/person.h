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

struct person_list {
	int n_pns;
	struct person *head;
};

enum personReturnCode {
    PERSON_OK = 0,
    PERSON_ADD_FAILED,
    PERSON_REMOVE_FAILED,
    PERSON_UPDATE_FAILED,
    PERSON_NOT_FOUND,
};

struct gfx_image_list;
struct planet_list;

struct person_list * person_list_init(void);
int person_list_destroy(struct person_list*);
struct person * person_init(int, SDL_Surface *, int, int);
int person_destroy(struct person *);
enum personReturnCode person_add(struct person_list *, int, SDL_Surface *, int, int);
enum personReturnCode person_add_rocket(struct person_list *, struct gfx_image_list *, int, int);
enum personReturnCode person_add_mult(struct person_list *, struct gfx_image_list *, int );
enum personReturnCode person_remove(struct person_list *, struct person *);
enum personReturnCode person_remove_id(struct person_list *, int);
enum personReturnCode person_remove_mult(struct person_list *);
enum personReturnCode person_update(struct planet_list *, struct person *);
enum personReturnCode person_update_mult(struct planet_list *, struct person_list *);
#endif

