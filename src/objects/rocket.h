/**
 * @file
 * @brief Description of the object rocket
 */

#ifndef ROCKET_H
#define ROCKET_H
#include "object.h"
#include "gholder.h"

struct gholder;
struct object;

/**
 * @brief Add a rocket object.
 * @param gh Pointer to the global game holder.
 * @param x Position X
 * @param y Position Y
 * @param m Mass of rocket
 * @param vx Start X velocity
 * @param vy Start Y velocity
 * @return OBJECT_OK if passed, OBJECT_ADD if failed.
 * @see objectReturnCode.
 * @see object_add.
 *
 */
unsigned int rocket_add(struct gholder *gh,
	double x, double y, double m, double vx, double vy);

/**
 * @brief Update function for rocket object.
 * @param gh Pointer to the global game holder.
 * @param rt Pointer to rocket object to be updated.
 * @return OBJECT_OK if passed, objectReturncode if failed.
 * @see objectReturnCode.
 * @see rocket_update_mult.
 *
 */
unsigned int rocket_update(struct gholder *gh, struct object *rt);

/**
 * @brief Update function for all rocket objects.
 * @param gh Pointer to the global game holder.
 * @return OBJECT_OK if passed, objectReturncode if failed.
 * @see objectReturnCode.
 * @see rocket_update
 *
 */
unsigned int rocket_update_mult(struct gholder *gh);
#endif

