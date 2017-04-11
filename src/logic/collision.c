#include "collision.h"

enum collisionReturnCode collision_planet(struct object * pt, struct object *rt) {

	double dx, dy, d, rad;
	dx = pt->pos->x - rt->pos->x;
	dy = pt->pos->y - rt->pos->y;
	d = sqrt(pow(dx,2)+pow(dy,2));
	rad = (pt->image->w+pt->image->h)/4;
	if ( d < rad ) {
		return COLLISION_ERR_OOB;
	}
	return COLLISION_OK;
}

enum collisionReturnCode collision_boundary(struct object *rt) {
	return COLLISION_OK;
}

enum collisionReturnCode collision_planet_mult(struct object_list *ptl, struct object *rt) {
	struct object *pt;
	DL_FOREACH(ptl->head, pt) {
		if (collision_planet(pt, rt) != COLLISION_OK) {
			return COLLISION_ERR_PLANET;
		}
	}
	return COLLISION_OK;
}

