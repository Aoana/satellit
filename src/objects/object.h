/**
 * @file
 * @brief Description of the object API
 */

#ifndef OBJECT_H
#define OBJECT_H
#include "common.h"
#include "position.h"

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
	SDL_Texture *image;		/**< Image representation of object. */
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
object * object_init(int id, SDL_Texture *image,
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
enum objectReturnCode object_add(object_list *objl, int id, SDL_Texture *image,
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
 * @brief Removal of all objects list, used for cleanup.
 * @param objl Pointer to list.
 * @return return OBJECT_OK if passed, OBJECT_REM if failed
 * @see objectReturnCode
 * @see object_remove
 * @see object_add
 *
 */
enum objectReturnCode object_remove_mult(object_list *objl);

/**
 * @brief Update position of obj based on gravity from objl.
 * @param objl Pointer to list.
 * @param objl Pointer to object to be updated.
 * @return return OBJECT_OK if passed, OBJECT_OOB if failed
 * @see objectReturnCode
 *
 */
enum objectReturnCode object_position_update(struct object_list *objl, struct object *obj);

/**
 * @brief Return the velocity angle of object.
 * @param obj Pointer to object.
 * @return return angle of object
 *
 */
double object_get_angle(object *obj);
#endif

