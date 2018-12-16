/*
 Copyright [2018] [Anders Markendahl]

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

/**
 * @file
 * @brief Map structure the global holder and functions
 */

#ifndef MAPS_H
#define MAPS_H
#include <libconfig.h>
#include "common.h"
#include "gholder.h"
#include "object.h"
#include "planet.h"
#include "moon.h"
#include "rocket.h"
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

/**
 * @brief Unload current map and load next map, also set state to intro.
 * @param gh Pointer to global holder.
 * @param map_num set specific map number, if 0 take next map.
 * @return 0 if passed, 1 if failed.
 *
 */
int map_load_next(struct gholder *gh, int map_num);
#endif

