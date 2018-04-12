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

/**
 * @brief Get input during shutdown phase.
 * @param gh Pointer to global game holder.
 *
 * Handling of restart (Enter) or shutdown (ESC or closing screen).
 */
void input_get_finish(struct gholder *gh);
