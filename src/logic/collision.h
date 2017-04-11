#ifndef POSITION_H
#define POSITION_H
#include "common.h"
#include "object.h"

enum collisionReturnCode {
    COLLISION_OK = 0,
    COLLISION_ERR_OOB,
    COLLISION_ERR_VEL,
};

enum collisionReturnCode collision_planet(struct object *, struct object *);
enum collisionReturnCode collision_boundary(struct object *);
enum collisionReturnCode collision_planet_mult(struct object_list *, struct object *);
#endif
