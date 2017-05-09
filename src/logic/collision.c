#include "collision.h"

enum collisionReturnCode collision_object(object *pt, object *rt) {

	double dx, dy, d, rad;
	int w, h;
	dx = pt->pos->x - rt->pos->x;
	dy = pt->pos->y - rt->pos->y;
	d = sqrt(pow(dx,2)+pow(dy,2));
	SDL_QueryTexture(pt->image, NULL, NULL, &w, &h);
	rad = (w+h)/4;
	if ( d < rad ) {
		return COLLISION_OBJ;

	}
	return COLLISION_OK;
}

enum collisionReturnCode collision_boundary(object *rt) {
	return COLLISION_OK;
}

enum collisionReturnCode collision_object_mult(object_list *ptl, object *rt) {
	object *pt;
	DL_FOREACH(ptl->head, pt) {
		if (collision_object(pt, rt) != COLLISION_OK) {
			return COLLISION_OBJ;
		}
	}
	return COLLISION_OK;
}

