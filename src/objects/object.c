#include "object.h"

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
		return OBJECT_ADD_FAILED;
	}
	DL_APPEND(objl->head, obj);
	objl->n_objs++;
	return OBJECT_OK;
}

enum objectReturnCode object_remove(struct object_list *objl, struct object *obj) {
	DL_DELETE(objl->head,obj);
	if(object_destroy(obj) != OBJECT_OK) {
		return OBJECT_REMOVE_FAILED;
	}
	objl->n_objs--;
	return OBJECT_OK;
}

enum objectReturnCode object_remove_mult(struct object_list *objl) {
	struct object *obj, *tmp;
	DL_FOREACH_SAFE(objl->head,obj,tmp) {
		if(object_remove(objl, obj) != OBJECT_OK) {
			return OBJECT_REMOVE_FAILED;
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
				return OBJECT_REMOVE_FAILED;
			}
			return OBJECT_OK;
		}
    }
	return OBJECT_NOT_FOUND;
}

enum objectReturnCode object_update(struct object_list *objl, struct object *obj) {
	enum positionReturnCode ret;
	if ((ret = position_update(objl, obj)) != POSITION_OK) {
		printf("WARN: Failed to update position, id=%d, ret=%d\n",obj->id, ret);
		return OBJECT_UPDATE_FAILED;
	}
	return OBJECT_OK;
}

enum objectReturnCode object_update_mult(struct object_list *objl_src, struct object_list *objl_update) {
       enum objectReturnCode ret;
       struct object *obj, *tmp;
       DL_FOREACH_SAFE(objl_update->head, obj, tmp) {
               if((ret = object_update(objl_src, obj)) != OBJECT_OK) {
                       printf("WARN: Failed to update object, id=%d, ret=%d, removing\n", obj->id, ret);
                       if (object_remove(objl_update, obj) != OBJECT_OK) {
                               printf("ERR: Failed to remove object, id=%d\n", obj->id);
                       }
               }
       }
       return OBJECT_OK;
}

