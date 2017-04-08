#ifndef PLANET_H
#define PLANET_H
#include "common.h"
#include "position.h"
#include "graphics.h"
#include "init.h"

struct planet {
	int id;
	int mass;
	struct position *pos;
	SDL_Surface *image;
	struct planet *next, *prev;
};

struct planet_list {
	int n_pts;
	struct planet *head;
};

enum planetReturnCode {
    PLANET_OK = 0,
    PLANET_ADD_FAILED,
    PLANET_REMOVE_FAILED,
    PLANET_UPDATE_FAILED,
    PLANET_NOT_FOUND,
};

struct gfx_image_list;

struct planet_list * planet_list_init(void);
int planet_list_destroy(struct planet_list*);
struct planet * planet_init(int, SDL_Surface *, int, int, int);
int planet_destroy(struct planet *);
enum planetReturnCode planet_add(struct planet_list *, int, SDL_Surface *image, int, int, int);
enum planetReturnCode planet_add_planet1(struct planet_list *, struct gfx_image_list *, int, int, int);
enum planetReturnCode planet_remove(struct planet_list *, struct planet *);
enum planetReturnCode planet_remove_id(struct planet_list *, int);
enum planetReturnCode planet_update(struct planet *);
#endif

