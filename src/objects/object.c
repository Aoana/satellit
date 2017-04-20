#include "object.h"

const char* object_enum2str(enum objectReturnCode ret) {
	switch (ret) {
		case OBJECT_OK:		return "OBJECT_OK";
		case OBJECT_ADD:	return "OBJECT_ADD";
		case OBJECT_REM:	return "OBJECT_REM";
		case OBJECT_OOB:	return "OBJECT_OOB";
		case OBJECT_COL:	return "OBJECT_COL";
		case OBJECT_NFD:	return "OBJECT_NFD";
		default:			return "NULL";
	}
}

/**
 * @brief Object list initialization.
 * @param void
 * @return Pointer to object list, NULL if failed
 * @see object_list_destroy
 *
 * Initialize and allocate object list.
 */
object_list * object_list_init() {
	object_list *objl;
	objl = calloc(1, sizeof(object_list));
	objl->n_objs = 0;
	objl->head = NULL;
	return objl;
}

/**
 * @brief Object list desctruction.
 * @param Pointer to object list
 * @return 0 if passed
 * @see object_list_init
 *
 * Free object list.
 */
int object_list_destroy(object_list *objl) {
	free(objl);
	return 0;
}

object * object_init(int id, SDL_Surface *image,
	double x, double y, double m, double vx, double vy) {
	object *obj;
	obj = calloc(1, sizeof(object));
	obj->id = id;
	obj->dead = 0;
	obj->mass = m;
	obj->next = NULL;
	obj->prev = NULL;

	obj->pos = position_init(x, y, vx, vy);
	if (obj->pos == NULL) {
		printf("ERR: Unable to init position %f,%f\n", x, y);
		free(obj);
		return NULL;
	}

	obj->image = image;

	return obj;
}

int object_destroy(object *obj) {
	position_destroy(obj->pos);
	free(obj);
	return 0;
}

enum objectReturnCode object_add(object_list *objl, int id, SDL_Surface *image,
	enum objectReturnCode (*obj_upd)(struct gholder *, struct object *),
	double x, double y, double m, double vx, double vy) {

	object *obj;
	obj = object_init(id, image, x, y, m, vx, vy);
	if (obj == NULL) {
		printf("WARN: Unable to init object number\n");
		return OBJECT_ADD;
	}
	obj->obj_upd = obj_upd;
	DL_APPEND(objl->head, obj);
	objl->n_objs++;
	return OBJECT_OK;
}

enum objectReturnCode object_remove(object_list *objl, object *obj) {
	DL_DELETE(objl->head,obj);
	if(object_destroy(obj) != OBJECT_OK) {
		return OBJECT_REM;
	}
	objl->n_objs--;
	return OBJECT_OK;
}

enum objectReturnCode object_remove_mult(object_list *objl) {
	object *obj, *tmp;
	DL_FOREACH_SAFE(objl->head,obj,tmp) {
		if(object_remove(objl, obj) != OBJECT_OK) {
			return OBJECT_REM;
		}
    }
	return OBJECT_OK;
}

enum objectReturnCode object_remove_id(object_list *objl, int id) {
	object *obj, *tmp;
	DL_FOREACH_SAFE(objl->head,obj,tmp) {
		if (obj->id == id) {
			DL_DELETE(objl->head,obj);
			if(object_destroy(obj) != OBJECT_OK) {
				return OBJECT_REM;
			}
			return OBJECT_OK;
		}
    }
	return OBJECT_NFD;
}

enum objectReturnCode object_update(object_list *objl, object *obj) {
	if (position_update(objl, obj) != POSITION_OK) {
		return OBJECT_OOB;
	}
	if (collision_planet_mult(objl, obj) != COLLISION_OK) {
		return OBJECT_COL;
	}
	return OBJECT_OK;
}

enum objectReturnCode object_update_mult(object_list *objl_src,
	object_list *objl_update, gfx_image_list *imgl) {
	enum objectReturnCode ret;
	object *obj, *tmp;
	DL_FOREACH_SAFE(objl_update->head, obj, tmp) {
		if (obj->dead != 0) {
			continue;
		}
		if((ret = object_update(objl_src, obj)) != OBJECT_OK) {
			printf("WARN: Object update failed %s, id=%d\n", object_enum2str(ret), obj->id);
			if (ret == OBJECT_COL) {
				gfx_image *gfx_img;
				obj->dead = 1;
				gfx_img = gfx_get_image(imgl, "gfx_broken_ship.png");
				obj->image = gfx_img->image;
			} else {
				if (object_remove(objl_update, obj) != OBJECT_OK) {
					printf("ERR: Failed to remove object, id=%d\n", obj->id);
				}
			}
		}
	}
	return OBJECT_OK;
}

