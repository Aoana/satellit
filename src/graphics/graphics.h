#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"
#include "rocket.h"
#include "planet.h"

#define UPDATE_FREQ 25

struct gholder;

/**
 * @brief Structure for an image (text or bitmap).
 */
typedef struct gfx_image {
	char *name;				/**< Name of image. */
	SDL_Surface *image;		/**< Pointer to actual image. */
	TTF_Font* font;			/**< Optional: Font used if image is text. */
	SDL_Color fontcolor;	/**< Optional: Font color used if image is text. */
	struct gfx_image *next;	/**< List pointer to next object. */
	struct gfx_image *prev; /**< List pointer to previous object. */
} gfx_image;

/**
 * @brief Structure for an image list.
 */
typedef struct gfx_image_list {
	int n_images;			/**< Number of images in list */
	struct gfx_image *head;	/**< Pointer to head of list */	
} gfx_image_list;

SDL_Surface *gfx_load_image(char *);
void gfx_draw_image(SDL_Surface *, int, int);
gfx_image_list * gfx_init_images(void);
gfx_image_list * gfx_init_texts(void);
void gfx_change_text(gfx_image_list *, char *, char *);
gfx_image * gfx_get_image(gfx_image_list *, char *);
void gfx_destroy_images(gfx_image_list *);
void gfx_destroy_texts(gfx_image_list *txtl);

extern SDL_Surface *screen;

#endif
