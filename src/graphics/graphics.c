#include "graphics.h"

/*
 * Helper functions
 */

void set_image_folder(char *buf) {

	char img_dir[32] = "/src/graphics/images/";

    strcpy(buf, getenv("DUCKSPOND"));
	strcat(buf, img_dir);
}

void set_fonts_folder(char *buf) {

	char img_dir[32] = "/src/graphics/fonts/";

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

	if(image == NULL) {
		return;
	}

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
	gfx_image *txt;

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

	/* Draw the Home and Goal base */
	gfx_draw_image(gh->hbase->image, gh->hbase->pos->x, gh->hbase->pos->y);
	gfx_draw_image(gh->gbase->image, gh->gbase->pos->x, gh->gbase->pos->y);

	/* Draw the rockets to x and y */
	DL_FOREACH(gh->rtl->head, rt) {
		gfx_draw_image(rt->image, rt->pos->x, rt->pos->y);
	}

	/* Draw the text to x and y */
	DL_FOREACH(gh->txtl->head, txt) {
		gfx_draw_image(txt->image, (double)RES_WIDTH/2, (double)SPACE_H_MIN);
	}

	/* Swap the image buffers */
	SDL_Flip(screen);
}

gfx_image_list * gfx_init_images() {

	/*printf("DEBUG: Enter %s\n", __func__);*/

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
				free(imgl);
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
		free(imgl);
		return NULL;
	}

	return imgl;
}

gfx_image_list * gfx_init_texts() {

	/*printf("DEBUG: Enter %s\n", __func__);*/

	gfx_image_list *txtl = calloc(1, sizeof(gfx_image_list));
	char font_path[128];

	set_fonts_folder(font_path);
	strcat(font_path, "FreeMono.ttf");
	printf ("INFO: Loading fonts in dir %s\n", font_path);

	TTF_Init();
	gfx_image *text = calloc(1, sizeof(gfx_image));
	text->font = TTF_OpenFont(font_path, 30);
	if (text->font == NULL) {
		printf("ERR: Unable to load font: %s %s \n", font_path, TTF_GetError());
		exit(1);
	}
	text->fontcolor.r = 255;
	text->fontcolor.b = 255;
	text->fontcolor.g = 255;
	text->image = NULL;
	text->name = strdup("txt_header");
	DL_APPEND(txtl->head, text);
	txtl->n_images++;

	gfx_change_text(txtl, "txt_header", "Welcome to GravBounce! Please set start velocity using arrow keys");

	return txtl;
}

void gfx_change_text(gfx_image_list *txtl, char *id, char *new_txt) {

	/*printf("DEBUG: Enter %s\n", __func__);*/

	gfx_image *text = gfx_get_image(txtl, id);
	if(text == NULL) {
		printf("ERR: Unable to get image %s\n", id);
		exit(1);
	}
	if(text->image != NULL) {
		SDL_FreeSurface(text->image);
	}
	text->image = TTF_RenderText_Blended(text->font, new_txt, text->fontcolor);
	if(text->image == NULL) {
		printf("ERR: Unable to change text to %s, %s %s\n", new_txt, id, TTF_GetError());
		exit(1);
	}

}

gfx_image * gfx_get_image(gfx_image_list *imgl, char *image) {

	/*printf("DEBUG: Enter %s\n", __func__);*/

	gfx_image *img;

	DL_FOREACH(imgl->head,img) {
		if (strcmp(img->name, image) == 0) {
			return img;
		}
	}
	return NULL;
}

void gfx_destroy_images(gfx_image_list *imgl) {

	/*printf("DEBUG: Enter %s\n", __func__);*/

	gfx_image *img,*tmp;

	DL_FOREACH_SAFE(imgl->head,img,tmp) {
		DL_DELETE(imgl->head,img);
		gfx_cleanup(img->image);
		free(img->name);
		free(img);
		imgl->n_images--;
	}
}
void gfx_destroy_texts(gfx_image_list *txtl) {

	/*printf("DEBUG: Enter %s\n", __func__);*/

	gfx_image *img,*tmp;

	DL_FOREACH_SAFE(txtl->head,img,tmp) {
		DL_DELETE(txtl->head,img);
		gfx_cleanup(img->image);
		free(img->name);
		free(img);
		txtl->n_images--;
	}
	TTF_Quit();
}
