/**
 * @file
 * @brief Description of the object planet
 */

#ifndef PLANET_H
#define PLANET_H
#include "object.h"
#include "gholder.h"

struct gholder;

/**
 * @brief Add a planet object.
 * @param gh Pointer to the global game holder.
 * @param x Position X
 * @param y Position Y
 * @param m Mass of planet
 * @return OBJECT_OK if passed, OBJECT_ADD if failed.
 * @see objectReturnCode.
 * @see object_add.
 *
 */
unsigned int planet_add(struct gholder *gh,
	double x, double y, double m);
#endif

