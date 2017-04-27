#ifndef COLLISION_H
#define COLLISION_H
#include "common.h"
#include "object.h"

enum collisionReturnCode {
    COLLISION_OK = 0,
    COLLISION_OBJ,
    COLLISION_OOB,
};

struct object;

enum collisionReturnCode collision_object(struct object *, struct object *);
enum collisionReturnCode collision_boundary(struct object *);
enum collisionReturnCode collision_object_mult(struct object_list *, struct object *);
#endif
