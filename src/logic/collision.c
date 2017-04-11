#include "collision.h"

enum collisionReturnCode collision_planet(struct object * pt, struct object *rt) {
	return COLLISION_OK;
}

enum collisionReturnCode collision_boundary(struct object *rt) {
	return COLLISION_OK;
}

enum collisionReturnCode collision_planet_mult(struct object_list *ptl, struct object *rt) {
	return COLLISION_OK;
}

