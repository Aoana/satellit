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

struct gfx_image_list * gfx_init_images() {

	int n_img = 1, i;
	struct gfx_image *img;
	char * image_str;
	struct gfx_image_list *imgl = calloc(1, sizeof(struct gfx_image_list));

	char img1[] ="/home/aoana/duckspond/src/graphics/images/gfx_pony.png";
	image_str = img1;

	printf("DEBUG: Image %s\n", image_str);

	for( i = 0; i < n_img; i++){
		img = calloc(1,sizeof(struct gfx_image));
		img->id = i;
		img->image = gfx_load_image(image_str);
		if (img->image == NULL) {
			printf("ERR: Image %s not found\n", image_str);
			return NULL;
		}
		DL_APPEND(imgl->head,img);
		imgl->n_images++;
	}

	return imgl;
}

struct gfx_image * gfx_get_image(struct gfx_image_list *imgl, int id) {

	struct gfx_image *img;

	DL_FOREACH(imgl->head,img) {
		if(img->id == id) {
			return img;
		}
	}
	return NULL;
}

char * gfx_destroy_images(struct gfx_image_list *imgl) {
	return NULL;
}
