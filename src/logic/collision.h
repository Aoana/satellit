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
