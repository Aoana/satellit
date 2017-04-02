#include "graphics.h"

SDL_Surface *gfx_load_image(char *name) {

	/* Load the image using SDL Image */
	SDL_Surface *temp = IMG_Load(name);
	SDL_Surface *image;
	
	if (temp == NULL) 	{
		printf("Failed to load image %s\n", name);
		return NULL;
	}
	
	/* Make the background transparent */
	SDL_SetColorKey(temp, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(temp->format, 0, 0, 0));
	
	/* Convert the image to the screen's native format */
	image = SDL_DisplayFormat(temp);
	
	SDL_FreeSurface(temp);
	
	if (image == NULL) 	{
		printf("Failed to convert image %s to native format\n", name);
		return NULL;
	}
	
	/* Return the processed image */
	return image;
}

void gfx_draw_image(SDL_Surface *image, int x, int y) {
	SDL_Rect dest;
	
	/* Set the blitting rectangle to the size of the src image */
	dest.x = x;
	dest.y = y;
	dest.w = image->w;
	dest.h = image->h;
	
	/* Blit the entire image onto the screen at coordinates x and y */
	SDL_BlitSurface(image, NULL, screen, &dest);
}

void gfx_update_screen(struct person *head) {
	
	struct person *pn;

	/* Blank the screen */
	SDL_FillRect(screen, NULL, 0);
	
	/* Draw the image to x and y */
	DL_FOREACH(head, pn) {
		gfx_draw_image(pn->image, pn->pos->x, pn->pos->y);
	}
	
	/* Swap the image buffers */
	SDL_Flip(screen);
}
