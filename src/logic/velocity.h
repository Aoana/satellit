#ifndef VELOCITY_H
#define VELOCITY_H
#include "common.h"
#include "position.h"
#include "person.h"
#include "planet.h"


#define GRAV_CONST 100

enum velocityReturnCode {
    VELOCITY_OK = 0,
    VELOCITY_NOK,
};

struct object;
struct object_list;

int velocity_validate(double, double);
int velocity_update(struct object_list *, struct object *);
#endif
