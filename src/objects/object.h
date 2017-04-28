/**
 * @file
 * @brief Description of the object API
 */

#ifndef OBJECT_H
#define OBJECT_H
#include "common.h"
#include "position.h"
#include "graphics.h"
#include "init.h"
#include "collision.h"

/**
 * @brief Return codes for the object API.
 *
 */
enum objectReturnCode {
	OBJECT_OK = 0,	/**< Object call OK. */
	OBJECT_ADD,		/**< Addition of object failed. */
	OBJECT_REM,		/**< Removal of object failed. */
	OBJECT_OOB,		/**< Object is out of bounds. */
	OBJECT_COL,		/**< Object has collided with other object. */
	OBJECT_NFD,		/**< Object not found. */
};

typedef struct object {
	int id;					/**< Unique id for object. */
	int dead;				/**< Set to non-zero if further updates are not needed, zero by default. */
	double mass;			/**< Total mass of object. */
	struct position *pos;	/**< Position of object. */
	SDL_Surface *image;		/**< Image representation of object. */
	struct object *next;	/**< List pointer next. */
	struct object *prev;	/**< List pointer previous. */
} object;

typedef struct object_list {
	int n_objs;				/**< Number of objects in list. */
	struct object *head;	/**< Pointer to head of list */
} object_list;

struct gfx_image_list;

const char* object_enum2str(enum objectReturnCode);

/**
 * @brief Object list initialization and allocation.
 * @param void
 * @return Pointer to object list, NULL if failed
 * @see object_list_destroy
 *
 */
object_list * object_list_init(void);

/**
 * @brief Object list destruction and free.
 * @param Pointer to object list
 * @return 0 if passed
 * @see object_list_init
 *
 */
int object_list_destroy(object_list*);

/**
 * @brief Object initialization.
 * @param param1 Unique ID
 * @param param2 Pointer to image of object
 * @param param3 X position
 * @param param4 Y position
 * @param param5 Mass
 * @param param6 X velocity
 * @param param7 Y velocity
 * @return pointer to object if passed, NULL if failed
 * @see object_destroy
 *
 */
object * object_init(int, SDL_Surface *,
	double, double, double, double, double);

/**
 * @brief Object destruction
 * @param param1 Pointer to object
 * @return zero of passed, non-zero if failed
 * @see object_init
 *
 */
int object_destroy(object *);

enum objectReturnCode object_add(object_list *, int, SDL_Surface *,
	double, double, double, double, double);
enum objectReturnCode object_remove(object_list *, object *);
enum objectReturnCode object_remove_id(object_list *, int);
enum objectReturnCode object_remove_mult(object_list *);
#endif

