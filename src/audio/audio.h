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
 * @return Pointer to audiodevice if passed, NULL if failed.
 *
 */
SDL_AudioDeviceID * audio_init();

/**
 * @brief Destroy audio device and structures.
 * @param audiodev SDL audio device.
 * @return 0 if passed, 1 if failed.
 *
 */
int audio_destroy(SDL_AudioDeviceID *audiodev);

/**
 * @brief Play a sound.
 * @param audiodev SDL audio device.
 * @param sound path to sound to be played.
 * @return 0 if passed, 1 if failed.
 *
 */
int audio_play_sound(SDL_AudioDeviceID *audiodev, char *sound);
#endif

