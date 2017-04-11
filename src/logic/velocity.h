#ifndef VELOCITY_H
#define VELOCITY_H
#include "common.h"
#include "position.h"
#include "rocket.h"
#include "planet.h"


#define GRAV_CONST 1000

enum velocityReturnCode {
    VELOCITY_OK = 0,
    VELOCITY_NOK,
};

struct object;
struct object_list;

int velocity_validate(double, double);
int velocity_update(struct object_list *, struct object *);
#endif
