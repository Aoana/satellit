/**
 * @file
 * @brief Description of the object moon
 */

#ifndef MOON_H
#define MOON_H
#include "object.h"
#include "gholder.h"

struct gholder;
struct object;

#define MOON_R 200 /**< Radius of moon rotation. */


/**
 * @brief Add a moon object.
 * @param gh Pointer to the global game holder.
 * @param x Position X
 * @param y Position Y
 * @param m Mass of moon
 * @return OBJECT_OK if passed, OBJECT_ADD if failed.
 * @see objectReturnCode.
 * @see object_add.
 *
 */
unsigned int moon_add(struct gholder *gh,
	double x, double y, double m);

/**
 * @brief Update function for moon object.
 * @param gh Pointer to the global game holder.
 * @param mn Pointer to moon object to be updated.
 * @return OBJECT_OK if passed, objectReturncode if failed.
 * @see objectReturnCode.
 * @see moon_update_mult.
 *
 */
unsigned int moon_update(struct gholder *gh, struct object *mn);

/**
 * @brief Update function for all moon objects.
 * @param gh Pointer to the global game holder.
 * @return OBJECT_OK if passed, objectReturncode if failed.
 * @see objectReturnCode.
 * @see moon_update
 *
 */
unsigned int moon_update_mult(struct gholder *gh);
#endif

