/**
 * @file
 * @brief Description of the object API
 */

#ifndef OBJECT_H
#define OBJECT_H
#include "common.h"
#include "position.h"
#include "graphics.h"
#include "collision.h"

/**
 * @brief Return codes for the object API.
 */
enum objectReturnCode {
	OBJECT_OK = 0,	/**< Object call OK. */
	OBJECT_ADD,		/**< Addition of object failed. */
	OBJECT_REM,		/**< Removal of object failed. */
	OBJECT_OOB,		/**< Object is out of bounds. */
	OBJECT_COL,		/**< Object has collided with other object. */
	OBJECT_NFD,		/**< Object not found. */
};

/**
 * @brief Object structure.
 */
typedef struct object {
	int id;					/**< Unique id for object. */
	int dead;				/**< Set to non-zero if further updates are not needed, zero by default. */
	double mass;			/**< Total mass of object. */
	struct position *pos;	/**< Position of object. */
	SDL_Surface *image;		/**< Image representation of object. */
	struct object *next;	/**< List pointer next. */
	struct object *prev;	/**< List pointer previous. */
} object;

/**
 * @brief Object list structure.
 */
typedef struct object_list {
	int n_objs;				/**< Number of objects in list. */
	struct object *head;	/**< Pointer to head of list */
} object_list;

struct gfx_image_list;

/**
 * @brief Translate from object return code to string.
 * @param ret Enum to be translated to string.
 * @return String pointer to result, string "NULL" if not found.
 *
 */
const char* object_enum2str(enum objectReturnCode ret);

/**
 * @brief Object list initialization and allocation.
 * @return Pointer to object list, NULL if failed
 * @see object_list_destroy
 *
 */
object_list * object_list_init(void);

/**
 * @brief Object list destruction and free.
 * @param objl Pointer to object list
 * @return 0 if passed
 * @see object_list_init
 *
 */
int object_list_destroy(object_list *objl);

/**
 * @brief Object initialization and allocation.
 * @param id Unique ID
 * @param image Pointer to image of object
 * @param x X position
 * @param y Y position
 * @param m Mass
 * @param vx X start velocity
 * @param vy Y start velocity
 * @return pointer to object if passed, NULL if failed
 * @see object_destroy
 *
 */
object * object_init(int id, SDL_Surface *image,
	double x, double y, double m, double vx, double vy);

/**
 * @brief Object destruction
 * @param obj Pointer to object
 * @return zero of passed, non-zero if failed
 * @see object_init
 *
 */
int object_destroy(object *obj);

/**
 * @brief Creation of an object and adding it to list.
 * @param objl Pointer to list to which to add.
 * @param id Unique ID
 * @param image Pointer to image of object
 * @param x X position
 * @param y Y position
 * @param m Mass
 * @param vx X start velocity
 * @param vy Y start velocity
 * @return return OBJECT_OK if passed, OBJECT_ADD if failed
 * @see objectReturnCode
 * @see object_remove
 *
 */
enum objectReturnCode object_add(object_list *objl, int id, SDL_Surface * image,
	double x, double y, double m, double vx, double vy);

/**
 * @brief Removal of an object including removal from list.
 * @param objl Pointer to list.
 * @param obj Pointer to object to remove.
 * @return return OBJECT_OK if passed, OBJECT_REM if failed
 * @see objectReturnCode
 * @see object_add
 *
 */
enum objectReturnCode object_remove(object_list *objl, object *obj);

/**
 * @brief Removal of an object using ID, including removal from list.
 * @param objl Pointer to list.
 * @param id Unique ID of object to remove.
 * @return return OBJECT_OK if passed, OBJECT_REM if failed
 * @see objectReturnCode
 * @see object_remove
 * @see object_add
 *
 */
enum objectReturnCode object_remove_id(object_list *objl, int id);

/**
 * @brief Removal of all objects list, used for cleanup.
 * @param objl Pointer to list.
 * @return return OBJECT_OK if passed, OBJECT_REM if failed
 * @see objectReturnCode
 * @see object_remove
 * @see object_add
 *
 */
enum objectReturnCode object_remove_mult(object_list *objl);
#endif

