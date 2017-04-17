#ifndef POSITION_H
#define POSITION_H
#include "common.h"
#include "planet.h"
#include "velocity.h"

typedef struct position {
	double x;
	double y;
	double vx;
	double vy;
} position;

enum positionReturnCode {
    POSITION_OK = 0,
    POSITION_ERR_OOB,
    POSITION_ERR_VEL,
};

int position_validate(double x, double y);
position * position_init(double, double, double, double);
int position_destroy(position *);
int position_update(struct object_list *ptl, struct object *pn);
#endif
