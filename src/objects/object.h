#ifndef OBJECT_H
#define OBJECT_H
#include "common.h"
#include "position.h"
#include "graphics.h"
#include "init.h"
#include "collision.h"

typedef struct object {
	int id;
	int dead;
	double mass;
	struct position *pos;
	SDL_Surface *image;
	int (*object_update)(struct object_list *, struct object *);
	struct object *next, *prev;
} object;

typedef struct object_list {
	int n_objs;
	struct object *head;
} object_list;

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
object_list * object_list_init(void);
int object_list_destroy(object_list*);
object * object_init(int, SDL_Surface *,
	double, double, double, double, double);
int object_destroy(object *);
enum objectReturnCode object_add(object_list *, int, SDL_Surface *,
	double, double, double, double, double);
enum objectReturnCode object_remove(object_list *, object *);
enum objectReturnCode object_remove_id(object_list *, int);
enum objectReturnCode object_remove_mult(object_list *);
enum objectReturnCode object_update(object_list *, object *);
enum objectReturnCode object_update_mult(object_list *,
	object_list *, struct gfx_image_list *);
#endif

