#ifndef GHOLDER_H
#define GHOLDER_H
#include "common.h"
#include "object.h"
#include "graphics.h"

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
	struct object_list *rtl;	/**< Pointer to object list for all rockets. */
	struct object_list *ptl;	/**< Pointer to object list or all planets. */
	struct object_list *mnl;	/**< Pointer to object list for all moons. */
	struct object *hbase;		/**< Pointer to home base object. */
	struct object *gbase;		/**< Pointer to goal base object. */
	struct gfx_image_list *imgl;/**< Pointer to image list. */
	struct gfx_image_list *txtl;/**< Pointer to text list. */
	double vx_0;				/**< Initial X velocity for rocket. */
	double vy_0;				/**< Initial Y velocity for rocket. */
} gholder; 

gholder * gholder_init(void);
int gholder_destroy(gholder *);
void gholder_update_screen(gholder * gh);
#endif

