/**
 * @file
 * @brief Map structure the global holder and functions
 */

#ifndef MAPS_H
#define MAPS_H
#include "common.h"
#include "gholder.h"
#include "object.h"
#include "planet.h"
#include "moon.h"
#include "rocket.h"
#include "gholder.h"
#include "base.h"

/**
 * @brief Load a new map structure and create all objects, also set state to intro.
 * @param gh Pointer to global holder.
 * @param map string to map name.
 * @return 0 if passed, 1 if failed.
 *
 */
int map_load(struct gholder *gh, char *map);

/**
 * @brief Unload a map structure and destroy all objects.
 * @param gh Pointer to global holder.
 * @return 0 if passed, 1 if failed.
 *
 */
int map_unload(struct gholder *gh);
#endif

