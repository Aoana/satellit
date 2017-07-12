/**
 * @file
 * @brief Position handling
 */

#ifndef POSITION_H
#define POSITION_H
#include "common.h"
#include "object.h"
#include "velocity.h"

//struct object;
//struct object_list;

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
 * @return Pointer to created position, NULL if failed.
 *
 */
position * position_init(double x, double y, double vx, double vy);

/**
 * @brief Destroy and free position.
 * @param p Pointer to position to destroy.
 * @return 0 if passed, non-zero if failed.
 *
 */
int position_destroy(position *p);

/**
 * @brief Validate position towards boundaries of game.
 * @param x Position in X.
 * @param y Position in Y.
 * @return POSITION_OK if pass, POSITION_ERR_OOB if out if bounds.
 *
 */
enum positionReturnCode position_validate(double x, double y);

#endif
