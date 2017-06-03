/**
 * @file
 * @brief Description of the global holder and functions
 */

#ifndef GHOLDER_H
#define GHOLDER_H
#include "common.h"
#include "object.h"
#include "graphics.h"
#include "gstate.h"

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

#endif

