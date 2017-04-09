#ifndef POSITION_H
#define POSITION_H
#include "common.h"
#include "planet.h"
#include "velocity.h"

struct position {
	double x;
	double y;
	double vx;
	double vy;
};

enum positionReturnCode {
    POSITION_OK = 0,
    POSITION_ERR_OOB,
    POSITION_ERR_VEL,
};

int position_validate(int x, int y);
struct position * position_init(int, int, int, int);
int position_destroy(struct position *);
int position_update(struct planet_list *ptl, struct person *pn);
#endif
