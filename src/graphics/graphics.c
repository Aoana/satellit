#include "graphics.h"

SDL_Surface *gfx_init_screen(char *title, int width, int height) {

	SDL_Surface *screen;

	/* Initialise SDL Video */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		return NULL;
	}

	screen = SDL_SetVideoMode(width, height, 0, SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_FULLSCREEN);

	if (screen == NULL) {
		printf("Couldn't set screen mode to %d x %d: %s\n", width, height, SDL_GetError());
		return NULL;
	}

	/* Initialise text management */
	if(TTF_Init() != 0) {
		printf("ERR: TTF_Init: %s\n", TTF_GetError());
		return NULL;
	}

	/* Set the screen title */
	SDL_WM_SetCaption(title, NULL);

	return screen;
}

void gfx_destroy_screen(SDL_Surface *screen) {

	/* Shut dow text management */
	TTF_Quit();

	/* Free the image */
	if (screen != NULL) {
		SDL_FreeSurface(screen);
	}

	/* Shut down SDL */
	SDL_Quit();
}

gfx_image_list *gfx_image_list_init() {

	/*printf("DEBUG: Enter %s\n", __func__);*/

	gfx_image_list *imgl = calloc(1, sizeof(gfx_image_list));

	return imgl;
}

void gfx_image_list_destroy(gfx_image_list *imgl) {

	/*printf("DEBUG: Enter %s\n", __func__);*/

	free(imgl);
}

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

int gfx_load_image_folder(gfx_image_list *imgl, char *folder) {

	/*printf("DEBUG: Enter %s\n", __func__);*/

	gfx_image *img;
	DIR *dir;
	struct dirent *file;
	char img_path[128];

	strcpy(img_path, folder);
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
				return 1;
			}
			DL_APPEND(imgl->head,img);
			imgl->n_images++;

			/* Reset img_dir to top */
			strcpy(img_path, folder);
		}
		closedir (dir);
	} else {
		printf("ERR: Could not read images\n");
		free(imgl);
		return 1;
	}

	return 0;
}

void gfx_draw_image(SDL_Surface *screen, SDL_Surface *image, int x, int y) {

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


gfx_text *gfx_text_init(char *font_path, int font_size) {

	/*printf("DEBUG: Enter %s\n", __func__);*/

	printf ("INFO: Loading font %s\n", font_path);

	gfx_text *text = calloc(1, sizeof(gfx_text));
	text->font = TTF_OpenFont(font_path, font_size);
	if (text->font == NULL) {
		printf("ERR: Unable to load font: %s %s \n", font_path, TTF_GetError());
		return NULL;
	}
	text->fontcolor.r = 255;
	text->fontcolor.b = 255;
	text->fontcolor.g = 255;
	text->text = NULL;

	return text;
}

void gfx_text_destroy(gfx_text *text) {

	/*printf("DEBUG: Enter %s\n", __func__);*/
	if(text->text != NULL) {
		SDL_FreeSurface(text->text);
	}
	free(text);
}

void gfx_text_change(gfx_text *text, char *new_txt) {

	/*printf("DEBUG: Enter %s\n", __func__);*/

	if(text->text != NULL) {
		SDL_FreeSurface(text->text);
	}
	text->text = TTF_RenderText_Blended(text->font, new_txt, text->fontcolor);
	if(text->text == NULL) {
		printf("ERR: Unable to change text to %s, %s\n", new_txt, TTF_GetError());
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
		SDL_FreeSurface(img->image);
		free(img->name);
		free(img);
		imgl->n_images--;
	}
}
void gfx_destroy_text(gfx_text *text) {

	/*printf("DEBUG: Enter %s\n", __func__);*/

	SDL_FreeSurface(text->text);
	free(text);
}
