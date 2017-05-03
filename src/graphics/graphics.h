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
 * @brief Structure for an image.
 * @see gfx_image_list
 */
typedef struct gfx_image {
	char *name;				/**< Name of image. */
	SDL_Surface *image;		/**< Pointer to actual image. */
	struct gfx_image *next;	/**< List pointer to next object. */
	struct gfx_image *prev; /**< List pointer to previous object. */
} gfx_image;

/**
 * @brief Structure for a text.
 *
 */
typedef struct gfx_text {
	SDL_Surface *text;		/**< Pointer to actual text. */
	TTF_Font* font;			/**< Font used. */
	SDL_Color fontcolor;	/**< Font color. */
	int fontsize;			/**< Font size. */
} gfx_text;

/**
 * @brief Structure for an image list.
 * @see gfx_image
 */
typedef struct gfx_image_list {
	int n_images;			/**< Number of images in list */
	struct gfx_image *head;	/**< Pointer to head of list */	
} gfx_image_list;

/**
 * @brief Initalize video and set screen, also init ttf.
 * @param title Title of the video screen.
 * @param width Width of screen.
 * @param height Height of screen.
 * @return Pointer to initalized screen, NULL if failed
 */
SDL_Surface *gfx_init_screen(char *title, int width, int height);

/**
 * @brief Destroy video and screen, also shutdown ttf.
 * @param screen Pointer to screen to be destroyed.
 *
 */
void gfx_destroy_screen(SDL_Surface *screen);

/**
 * @brief Removal of an object including removal from list.
 * @param name Full path to image.
 * @return Pointer to image if passed, NULL if failed.
 *
 */
SDL_Surface *gfx_load_image(char *name);

/**
 * @brief Draw image to screen according to coordinates.
 * @param screen Pointer to screen to draw on.
 * @param image Pointer to image.
 * @param x Coordinate X.
 * @param y Coordinate Y.
 *
 */
void gfx_draw_image(SDL_Surface* screen, SDL_Surface *image, int x, int y);

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
gfx_text *gfx_init_text(void);

/**
 * @brief Change text content of text object.
 * @param txt Pointer to text object.
 * @param new_text New text to be used in text object.
 *
 */
void gfx_change_text(gfx_text *text, char *new_txt);

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
 * @param text Pointer to text object to destroy.
 *
 */
void gfx_destroy_text(gfx_text *text);

#endif
