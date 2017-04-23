#include "graphics.h"

/*
 * Helper functions
 */

void set_image_folder(char *buf) {

	char img_dir[32] = "/src/graphics/images/";

    strcpy(buf, getenv("DUCKSPOND"));
	strcat(buf, img_dir);
}

/*
 * Graphics API
 */

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
	dest.x = x-(image->w/2);
	dest.y = y-(image->h/2);
	dest.w = image->w;
	dest.h = image->h;
	
	/* Blit the entire image onto the screen at coordinates x and y */
	SDL_BlitSurface(image, NULL, screen, &dest);
}

void gfx_update_screen(gholder * gh) {
	
	object *rt;
	object *pt;
	object *mn;

	/* Blank the screen */
	SDL_FillRect(screen, NULL, 0);
	
	/* Draw the planets to x and y */
	DL_FOREACH(gh->ptl->head, pt) {
		gfx_draw_image(pt->image, pt->pos->x, pt->pos->y);
	}

	/* Draw the moons to x and y */
	DL_FOREACH(gh->mnl->head, mn) {
		gfx_draw_image(mn->image, mn->pos->x, mn->pos->y);
	}

	/* Draw the rockets to x and y */
	DL_FOREACH(gh->rtl->head, rt) {
		gfx_draw_image(rt->image, rt->pos->x, rt->pos->y);
	}

	/* Swap the image buffers */
	SDL_Flip(screen);
}

gfx_image_list * gfx_init_images() {

	gfx_image *img;
	DIR *dir;
	struct dirent *file;
	gfx_image_list *imgl = calloc(1, sizeof(gfx_image_list));
	char img_path[128];

	set_image_folder(img_path);
	printf ("INFO: Loading images in dir %s\n",img_path);
	if ((dir = opendir(img_path)) != NULL) {
		while ((file = readdir(dir)) != NULL) {
			if (strcmp(file->d_name,".") == 0 || strcmp(file->d_name,"..") == 0) {
				continue;
			}
			strcat(img_path, file->d_name);
			img = calloc(1,sizeof(gfx_image));
			img->name = strdup(file->d_name);
			img->image = gfx_load_image(img_path);
			if (img->image == NULL) {
				printf("ERR: Could not load image %s\n", img_path);
				return NULL;
			}
			DL_APPEND(imgl->head,img);
			imgl->n_images++;

			/* Reset img_dir to top */
			set_image_folder(img_path);
		}
		closedir (dir);
	} else {
		printf("ERR: Could not read images\n");
		return NULL;
	}

	return imgl;
}

gfx_image * gfx_get_image(gfx_image_list *imgl, char *image) {

	gfx_image *img;

	DL_FOREACH(imgl->head,img) {
		if (strcmp(img->name, image) == 0) {
			return img;
		}
	}
	return NULL;
}

void gfx_destroy_images(gfx_image_list *imgl) {

	gfx_image *img,*tmp;

	DL_FOREACH_SAFE(imgl->head,img,tmp) {
		DL_DELETE(imgl->head,img);
		gfx_cleanup(img->image);
		free(img->name);
		free(img);
		imgl->n_images--;
	}
}
