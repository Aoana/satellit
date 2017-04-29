#ifndef POSITION_H
#define POSITION_H
#include "common.h"
#include "planet.h"
#include "velocity.h"

/**
 * @brief Structure for position and velocity.
 */
typedef struct position {
	double x;	/**< Position pixel in X. */
	double y;	/**< Position pixel in Y. */
	double vx;	/**< Velocity in X. */
	double vy;	/**< Velocity in Y. */
} position;

enum positionReturnCode {
    POSITION_OK = 0,	/**< Position OK. */
    POSITION_ERR_OOB,	/**< Position out of bounds. */
    POSITION_ERR_VEL,	/**< Faulty Velocity. */
};

int position_validate(double x, double y);
position * position_init(double, double, double, double);
int position_destroy(position *);
int position_update(struct object_list *ptl, struct object *pn);
#endif
