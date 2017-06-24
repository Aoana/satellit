/**
 * @file
 * @brief Collection of standard includes needed for most code
 */
#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <dirent.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "utlist.h"
#include "log.h"


#define RES_WIDTH 1920 				/**< Resolution width of screen. */
#define RES_HEIGHT 1080				/**< Resolution height of screen. */
#define SPACE_W_MAX RES_WIDTH-100	/**< Playable area, max width. */
#define SPACE_W_MIN 100				/**< Playable area, min width. */
#define SPACE_H_MAX RES_HEIGHT-100	/**< Playable area, max height. */
#define SPACE_H_MIN 100				/**< Playable area, min height. */

#endif
