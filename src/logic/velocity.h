/**
 * @file
 * @brief Velocity handling
 */

#ifndef VELOCITY_H
#define VELOCITY_H
#include "common.h"
#include "position.h"
#include "rocket.h"
#include "planet.h"


#define GRAV_CONST 1000 /**< Gravitational constant, only for tweaking */

/**
 * @brief Return codes for velocity handling.
 *
 */
enum velocityReturnCode {
    VELOCITY_OK = 0,
    VELOCITY_NOK,
};

struct object;
struct object_list;

/**
 * @brief Validate velocity vectors.
 * @param vx Velocity in X.
 * @param vy Velocity in Y.
 * @return VELOCITY_OK if pass, VELOCITY_NOK if failed.
 *
 */
enum velocityReturnCode velocity_validate(double vx, double vy);

/**
 * @brief Update velocity based on gravitation.
 * @param ptl Pointer to object list that excerts gravitation (planet list).
 * @param rt Pointer to object to update velocity.
 * @return VELOCITY_OK if pass, VELOCITY_NOK if failed.
 *
 */
enum velocityReturnCode velocity_update(struct object_list *ptl, struct object *rt);
#endif
