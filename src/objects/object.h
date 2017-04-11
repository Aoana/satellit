#ifndef OBJECT_H
#define OBJECT_H
#include "common.h"
#include "position.h"
#include "graphics.h"
#include "init.h"
#include "collision.h"

struct object {
	int id;
	double mass;
	struct position *pos;
	SDL_Surface *image;
	struct object *next, *prev;
};

struct object_list {
	int n_objs;
	struct object *head;
};

enum objectReturnCode {
	OBJECT_OK = 0,
	OBJECT_ADD,
	OBJECT_REM,
	OBJECT_OOB,
	OBJECT_COL,
	OBJECT_NFD,
};

struct gfx_image_list;

const char* object_enum2str(enum objectReturnCode);
struct object_list * object_list_init(void);
int object_list_destroy(struct object_list*);
struct object * object_init(int, SDL_Surface *,
	double, double, double, double, double);
int object_destroy(struct object *);
enum objectReturnCode object_add(struct object_list *, int, SDL_Surface *,
	double, double, double, double, double);
enum objectReturnCode object_remove(struct object_list *, struct object *);
enum objectReturnCode object_remove_id(struct object_list *, int);
enum objectReturnCode object_remove_mult(struct object_list *);
enum objectReturnCode object_update(struct object_list *, struct object *);
enum objectReturnCode object_update_mult(struct object_list *, struct object_list *);
#endif

