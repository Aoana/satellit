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

struct object_list * object_list_init() {
	struct object_list *objl;
	objl = calloc(1, sizeof(struct object_list));
	objl->n_objs = 0;
	objl->head = NULL;
	return objl;
}

int object_list_destroy(struct object_list *objl) {
	free(objl);
	return 0;
}

struct object * object_init(int id, SDL_Surface *image,
	double x, double y, double m, double vx, double vy) {
	struct object *obj;
	obj = calloc(1, sizeof(struct object));
	obj->id = id;
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

int object_destroy(struct object *obj) {
	position_destroy(obj->pos);
	free(obj);
	return 0;
}

enum objectReturnCode object_add(struct object_list *objl, int id,
	SDL_Surface *image, double x, double y, double m, double vx, double vy) {

	struct object *obj;
	obj = object_init(id, image, x, y, m, vx, vy);
	if (obj == NULL) {
		printf("WARN: Unable to init object number\n");
		return OBJECT_ADD;
	}
	DL_APPEND(objl->head, obj);
	objl->n_objs++;
	return OBJECT_OK;
}

enum objectReturnCode object_remove(struct object_list *objl, struct object *obj) {
	DL_DELETE(objl->head,obj);
	if(object_destroy(obj) != OBJECT_OK) {
		return OBJECT_REM;
	}
	objl->n_objs--;
	return OBJECT_OK;
}

enum objectReturnCode object_remove_mult(struct object_list *objl) {
	struct object *obj, *tmp;
	DL_FOREACH_SAFE(objl->head,obj,tmp) {
		if(object_remove(objl, obj) != OBJECT_OK) {
			return OBJECT_REM;
		}
    }
	return OBJECT_OK;
}

enum objectReturnCode object_remove_id(struct object_list *objl, int id) {
	struct object *obj, *tmp;
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

enum objectReturnCode object_update(struct object_list *objl, struct object *obj) {
	if (position_update(objl, obj) != POSITION_OK) {
		return OBJECT_OOB;
	}
	if (collision_planet_mult(objl, obj) != COLLISION_OK) {
		return OBJECT_COL;
	}
	return OBJECT_OK;
}

enum objectReturnCode object_update_mult(struct object_list *objl_src, struct object_list *objl_update) {
	enum objectReturnCode ret;
	struct object *obj, *tmp;
	DL_FOREACH_SAFE(objl_update->head, obj, tmp) {
		if((ret = object_update(objl_src, obj)) != OBJECT_OK) {
			printf("WARN: Object update failed %s, id=%d\n", object_enum2str(ret), obj->id);

			if (object_remove(objl_update, obj) != OBJECT_OK) {
				printf("ERR: Failed to remove object, id=%d\n", obj->id);
			}
		}
	}
	return OBJECT_OK;
}

