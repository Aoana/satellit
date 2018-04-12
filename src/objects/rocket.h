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
 * @brief Description of the object rocket
 */

#ifndef ROCKET_H
#define ROCKET_H
#include "object.h"
#include "collision.h"
#include "gholder.h"

struct gholder;
struct object;

#define GRAV_CONST 1000 /**< Gravity constant, used for tweaking */

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

