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
 * @brief Position handling
 */

#ifndef POSITION_H
#define POSITION_H
#include "common.h"

/**
 * @brief Structure for position and velocity.
 */
typedef struct position {
	double x;	/**< Position pixel in X. */
	double y;	/**< Position pixel in Y. */
	double vx;	/**< Velocity in X. */
	double vy;	/**< Velocity in Y. */
} position;

/**
 * @brief Structure for allowed space.
 */
typedef struct space {
	double max_x;	/**< Position pixel max X. */
	double min_x;	/**< Position pixel min X. */
	double max_y;	/**< Position pixel max Y. */
	double min_y;	/**< Position pixel min Y. */
} space;

/**
 * @brief Return codes for position handling.
 */
enum positionReturnCode {
    POSITION_OK = 0,	/**< Position OK. */
    POSITION_ERR_OOB,	/**< Position out of bounds. */
    POSITION_ERR_VEL,	/**< Faulty Velocity. */
};

/**
 * @brief Initalize and allocate position.
 * @param x Initial position in X.
 * @param y Initial position in Y.
 * @param vx Initial velocity in X.
 * @param vy Initial velocity in Y.
 * @param sp Pointer to allowed space.
 * @return Pointer to created position, NULL if failed.
 *
 */
position * position_init(double x, double y, double vx, double vy, space *sp);

/**
 * @brief Destroy and free position.
 * @param p Pointer to position to destroy.
 * @return 0 if passed, non-zero if failed.
 *
 */
int position_destroy(position *p);

/**
 * @brief Initalize and allocate space
 * @param min_x Min space X-axis.
 * @param max_x Max space X-axis.
 * @param min_y Min space Y-axis.
 * @param max_y Max space Y-axis.
 * @return Pointer to created space, NULL if failed.
 *
 */
space * position_space_init(double min_x, double max_x, double min_y, double max_y);


/**
 * @brief Destroy and free space.
 * @param p Pointer to space to destroy.
 * @return 0 if passed, non-zero if failed.
 *
 */
int position_space_destroy(space *sp);

/**
 * @brief Validate position towards boundaries of game.
 * @param x Position in X.
 * @param y Position in Y.
 * @param y Pointer to allowed space.
 * @return POSITION_OK if pass, POSITION_ERR_OOB if out if bounds.
 *
 */
enum positionReturnCode position_validate(double x, double y, space *sp);

/**
 * @brief Update position of obj based on gravity from objl.
 * @param p Pointer to position to be updated.
 * @param sp Pointer to allowed space.
 * @return return POSITION_OK if passed, POSITION_ERR_OOB if failed
 * @see positionReturnCode
 *
 */
enum positionReturnCode position_update(position *p, space *sp);

/**
 * @brief Return the velocity angle of object.
 * @param p Pointer to position struct.
 * @return return angle of velocity vector
 *
 */
double position_get_angle(position *p);

#endif
