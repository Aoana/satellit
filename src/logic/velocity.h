#ifndef VELOCITY_H
#define VELOCITY_H
#include "common.h"
#include "position.h"
#include "person.h"
#include "planet.h"

#define UPDATE_FREQ_VEL 1/UPDATE_FREQ

enum velocityReturnCode {
    VELOCITY_OK = 0,
    VELOCITY_NOK,
};

struct person;
struct planet_list;

int velocity_validate(int, int);
int velocity_update(struct planet_list *, struct person *);
#endif
