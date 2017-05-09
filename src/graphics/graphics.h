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
	SDL_Texture *image;		/**< Pointer to actual image. */
	struct gfx_image *next;	/**< List pointer to next object. */
	struct gfx_image *prev; /**< List pointer to previous object. */
} gfx_image;

/**
 * @brief Structure for a text.
 *
 */
typedef struct gfx_text {
	SDL_Texture *text;		/**< Pointer to actual text. */
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
 * @param window Pointer to window pointer to set
 * @param renderer Pointer to renderer pointer to set
 * @return 0 if passed, 1 if failed
 */
int gfx_screen_init(char *title, int width, int height,
	SDL_Window **window, SDL_Renderer **renderer);

/**
 * @brief Destroy video and screen, also shutdown ttf.
 * @param window Pointer to window to be destroyed.
 * @param renderer Pointer to renderer to be destroyed.
 *
 */
void gfx_screen_destroy(SDL_Window *window, SDL_Renderer *renderer);

/**
 * @brief Allocate an image list.
 * @return Pointer to allocated image list
 *
 */
gfx_image_list *gfx_image_list_init();

/**
 * @brief Destroy an image list.
 * @param imgl Pointer to image list to be destroyed.
 *
 */
void gfx_image_list_destroy(gfx_image_list *imgl);

/**
 * @brief Initialize all texts as an image list.
 * @param font_path Full path to font to be used.
 * @param font_size Size of font.
 * @return Pointer text object if passed, NULL if failed.
 *
 */
gfx_text *gfx_text_init(char *font_path, int font_size);

/**
 * @brief Initialize all texts as an image list.
 * @param text Pointer to text to be destroyed
 *
 */
void gfx_text_destroy(gfx_text *text);

/**
 * @brief Initialize an image.
 * @param renderer Pointer to active renderer.
 * @param name ID to use for image.
 * @param path Full file path of image.
 * @return Pointer to created image object, NULL if failed.
 * @see gfx_image_destroy
 *
 */
gfx_image *gfx_image_init(SDL_Renderer *renderer, char *name, char* path);

/**
 * @brief Destroy an image.
 * @param img Pointer to image to destroy.
 * @see gfx_image_init
 *
 */
void gfx_image_destroy(gfx_image *img);

/**
 * @brief Initialize a folder of images and add to image list.
 * @param renderer Pointer to active renderer.
 * @param imgl Pointer to image list to add images to.
 * @param folder Full path to folder.
 * @return 0 if passed, 1 if failed.
 * @see gfx_image_destroy
 *
 * ID for images will be file name.
 */
int gfx_image_init_mult(SDL_Renderer *renderer, gfx_image_list *imgl, char *folder);

/**
 * @brief Destroy a list of images.
 * @param imgl Pointer to image list to destroy.
 * @see gfx_image_init_mult
 *
 */
void gfx_image_destroy_mult(gfx_image_list *imgl);

/**
 * @brief Get image from image list.
 * @param imgl Pointer to image list.
 * @param id Unique identifier for image object.
 * @return Pointer to image, NULL if failed.
 *
 */
gfx_image * gfx_image_get(gfx_image_list *imgl, char *id);

/**
 * @brief Set text content of text object.
 * @param renderer Pointer to active renderer.
 * @param text Pointer to text object.
 * @param new_text New text to be used in text object.
 *
 */
void gfx_text_set(SDL_Renderer *renderer, gfx_text *text, char *new_txt);

/**
 * @brief Draw image to screen according to coordinates.
 * @param renderer Pointer to active renderer.
 * @param image Pointer to image.
 * @param x Coordinate X.
 * @param y Coordinate Y.
 *
 */
void gfx_surface_draw(SDL_Renderer *renderer, SDL_Texture *image, int x, int y);

#endif
