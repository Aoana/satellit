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
 * @brief Collision handling
 */

#ifndef COLLISION_H
#define COLLISION_H
#include "common.h"
#include "object.h"

/**
 * @brief Return codes for collision checks.
 *
 */
enum collisionReturnCode {
    COLLISION_OK = 0,	/**< No collision has occured. */
    COLLISION_OBJ,		/**< Collision occured with object. */
    COLLISION_OOB,		/**< Collision occured with boundary. */
};

struct object;
struct object_list;

/**
 * @brief Check collision between two objects.
 * @param pt Pointer to object to check against.
 * @param rt Pointer to object to check (active object).
 * @return COLLISION_OK if pass, COLLISION_OBJ if collision occured.
 *
 */
enum collisionReturnCode collision_object(struct object *pt, struct object *rt);

/**
 * @brief Check collision for object and boundary
 * @param rt Pointer to object to check (active object).
 * @return COLLISION_OK if pass, COLLISION_OOB if collision occured.
 *
 */
enum collisionReturnCode collision_boundary(struct object *rt);

/**
 * @brief Check collision between an object and a list of objects.
 * @param ptl Pointer to object list to check against.
 * @param rt Pointer to object to check (active object).
 * @return COLLISION_OK if pass, COLLISION_OBJ if collision occured.
 *
 */
enum collisionReturnCode collision_object_mult(struct object_list *ptl, struct object *rt);
#endif
