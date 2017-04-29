/**
 * @file
 * @brief Graphics handling
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"
#include "rocket.h"
#include "planet.h"

#define UPDATE_FREQ 25 /**< Update frequency for the game. */

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

/**
 * @brief Removal of an object including removal from list.
 * @param name Full path to image.
 * @return Pointer to image if passed, NULL if failed.
 *
 */
SDL_Surface *gfx_load_image(char *name);

/**
 * @brief Draw image to screen according to coordinates.
 * @param image Pointer to image.
 * @param x Coordinate X.
 * @param y Coordinate Y.
 *
 */
void gfx_draw_image(SDL_Surface *image, int x, int y);

/**
 * @brief Initialize all images as a image list.
 * @return Pointer image list, NULL if failed.
 *
 */
gfx_image_list * gfx_init_images(void);

/**
 * @brief Initialize all texts as an image list.
 * @return Pointer image list, NULL if failed.
 *
 */
gfx_image_list * gfx_init_texts(void);

/**
 * @brief Change text content of text object.
 * @param txtl Pointer to text list.
 * @param id Unique identifier for text object.
 * @param new_text New text to be used in text object.
 *
 */
void gfx_change_text(gfx_image_list *txtl, char *id, char *new_text);

/**
 * @brief Get image from image list.
 * @param imgl Pointer to image list.
 * @param id Unique identifier for image object.
 * @return Pointer to image, NULL if failed.
 *
 */
gfx_image * gfx_get_image(gfx_image_list *imgl, char *id);

/**
 * @brief Destroy all images of image list.
 * @param imgl Pointer to image list.
 *
 */
void gfx_destroy_images(gfx_image_list *imgl);

/**
 * @brief Destroy all texts in text list.
 * @param txtl Pointer to text list.
 *
 */
void gfx_destroy_texts(gfx_image_list *txtl);

extern SDL_Surface *screen;

#endif
