/**
 * @file
 * @brief Input handling in game
 */
#ifndef INPUT_H
#define INPUT_H
#include "common.h"
#include "gholder.h"
#endif

#define INPUT_INCR 5 /**< Velocity increment for input. */

struct gholder;

/**
 * @brief Get input during intro phase.
 * @param gh Pointer to global game holder.
 *
 * Input handling from arrow keys for setting initial velocity.
 * Handling of shutdown (ESC or closing screen).
 */
void input_get_intro(struct gholder *gh);

/**
 * @brief Get input during game phase.
 * @param gh Pointer to global game holder.
 *
 * Handling of shutdown (ESC or closing screen).
 */
void input_get_runtime(struct gholder *gh);
