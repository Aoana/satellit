/**
 * @file
 * @brief Managing sound in game, like init devices and play sounds.
 */

#ifndef SOUND_H
#define SOUND_H
#include "common.h"
#include "gholder.h"
#include "object.h"
#include "planet.h"
#include "moon.h"
#include "rocket.h"
#include "gholder.h"
#include "base.h"

/**
 * @brief Init audio device and load sounds.
 * @param gh Pointer to global holder.
 * @return 0 if passed, 1 if failed.
 *
 */
int audio_init(struct gholder *gh);

/**
 * @brief Destroy audio device and structures.
 * @param gh Pointer to global holder.
 * @return 0 if passed, 1 if failed.
 *
 */
int audio_destroy(struct gholder *gh);

/**
 * @brief Play a sound.
 * @param gh Pointer to global holder.
 * @param sound path to sound to be played.
 * @return 0 if passed, 1 if failed.
 *
 */
int audio_play_sound(struct gholder *gh, char *sound);
#endif

