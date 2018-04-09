/**
 * @file
 * @brief Description of the global holder and functions
 */

#ifndef GHOLDER_H
#define GHOLDER_H
#include "common.h"
#include "object.h"
#include "graphics.h"
#include "input.h"
#include "moon.h"
#include "rocket.h"
#include "audio.h"
#include "maps.h"

/**
 * @brief State of a game.
 */
enum gstate {
	STATE_INTRO = 0,	/**< Game is at welcome screen and where input is gathered. */
	STATE_RUNTIME,		/**< Game is running. */
	STATE_GAMEOVER,		/**< Game over. */
	STATE_VICTORY,		/**< Game finished successfully. */
	STATE_SHUTDOWN,		/**< Game set to shutdown */
};

/**
 * @brief Structure for global game holder.
 */
typedef struct gholder {
	enum gstate state;			/**< State of current game. */
	SDL_Window *window;			/**< Window of game. */
	SDL_Renderer *renderer;		/**< Renderer for game. */
	SDL_Texture *background;	/**< Current Background in game. */
	struct object_list *rtl;	/**< Pointer to object list for all rockets. */
	struct object_list *ptl;	/**< Pointer to object list or all planets. */
	struct object_list *mnl;	/**< Pointer to object list for all moons. */
	struct object *hbase;		/**< Pointer to home base object. */
	struct object *gbase;		/**< Pointer to goal base object. */
	struct gfx_image_list *imgl;/**< Pointer to image list. */
	struct gfx_text *header;	/**< Pointer to header of game. */
	double vx_0;				/**< Initial X velocity for rocket. */
	double vy_0;				/**< Initial Y velocity for rocket. */
	int map_number;				/**< Current map number */
	SDL_AudioDeviceID *audiodev;/**< Audio device. */
} gholder;

/**
 * @brief Allocate and initialize the global holder.
 * @return Pointer to global holder, NULL if failed.
 *
 */
gholder * gholder_init(void);

/**
 * @brief Remove and free global holder.
 * @param gh Pointer to global holder.
 * @return 0 if passed, non-zero if failed.
 *
 */
int gholder_destroy(gholder *gh);

/**
 * @brief Set the background of game.
 * @param gh Pointer to global holder.
 * @param background String ID of background to use.
 * @return 0 if passed, non-zero if failed.
 *
 */
int gholder_background_set(gholder *gh, char *background);

/**
 * @brief Update the screen of the game.
 * @param gh Pointer to global holder.
 *
 */
void gholder_update_screen(gholder *gh);

/**
 * @brief Enter intro state. Move to next stage when Enter is pressed.
 * @param gh Pointer to global holder.
 *
 */
void gholder_state_intro(gholder *gh);

/**
 * @brief Enter runtime state. Move to next stage when game over or victory.
 * @param gh Pointer to global holder.
 *
 */
void gholder_state_runtime(gholder *gh);

/**
 * @brief Enter finish state. Shuts down when Esc is pressed.
 * @param gh Pointer to global holder.
 *
 */
void gholder_state_finish(gholder *gh);
#endif

