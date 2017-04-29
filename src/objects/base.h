/**
 * @file
 * @brief Description of the object base
 */

#ifndef BASE_H
#define BASE_H
#include "object.h"
#include "gholder.h"

struct gholder;
struct object;

/**
 * @brief Add a base object.
 * @param gh Pointer to the global game holder.
 * @param type Type of base, 0 home base, 1 goal base
 * @param x Position X
 * @param y Position Y
 * @return OBJECT_OK if passed, OBJECT_ADD if failed.
 * @see objectReturnCode.
 * @see object_add.
 *
 */
unsigned int base_add(gholder *gh, int type, double x, double y);
#endif

