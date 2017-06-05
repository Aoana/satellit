#include "graphics.h"

SDL_Texture *sdl_image_load(SDL_Renderer *renderer, char *name) {

	/* Load the image using SDL Image */
	SDL_Surface *temp = IMG_Load(name);
	SDL_Texture *image;
	
	if (temp == NULL) 	{
		LOG("ERR: Failed to load image %s: %s", name, SDL_GetError());
		return NULL;
	}

	image = SDL_CreateTextureFromSurface(renderer, temp);
	if (image == NULL) 	{
		LOG("Failed to convert image %s to native format", name);
		return NULL;
	}
	
	SDL_FreeSurface(temp);

	/* Return the processed image */
	return image;
}


int gfx_screen_init(char *title, int width, int height,
	SDL_Window **window, SDL_Renderer **renderer) {

	/* Initialise SDL Video */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG("ERR: Could not initialize SDL: %s", SDL_GetError());
		return 1;
	}

	*window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_FULLSCREEN);
	if (*window == NULL) {
		LOG("ERR: Couldn't create window %d x %d: %s", width, height, SDL_GetError());
		return 1;
	}

	*renderer = SDL_CreateRenderer(*window, -1, 0);
	if (*renderer == NULL) {
		LOG("ERR: Couldn't create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(*window);
		return 1;
	}

	if (SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255) != 0) {
		LOG("ERR: Couldn't set draw color: %s", SDL_GetError());
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		return 1;
	}

	/* Initialise text management */
	if(TTF_Init() != 0) {
		LOG("ERR: TTF_Init: %s", TTF_GetError());
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		return 1;
	}

	return 0;
}

void gfx_screen_destroy(SDL_Window *window, SDL_Renderer *renderer) {

	/* Shut dow text management */
	TTF_Quit();

	/* Destroy the renderer */
	if (renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	/* Destroy the window */
	if (window != NULL) {
		SDL_DestroyWindow(window);
	}

	/* Shut down SDL */
	SDL_Quit();
}

gfx_image_list *gfx_image_list_init() {

	/*LOG("DEBUG: Enter %s", __func__);*/

	gfx_image_list *imgl = calloc(1, sizeof(gfx_image_list));

	return imgl;
}

void gfx_image_list_destroy(gfx_image_list *imgl) {

	/*LOG("DEBUG: Enter %s", __func__);*/

	free(imgl);
}

gfx_text *gfx_text_init(char *font_path, int font_size) {

	/*LOG("DEBUG: Enter %s", __func__);*/

	LOG ("INFO: Loading font %s", font_path);

	gfx_text *text = calloc(1, sizeof(gfx_text));
	text->font = TTF_OpenFont(font_path, font_size);
	if (text->font == NULL) {
		LOG("ERR: Unable to load font: %s %s ", font_path, TTF_GetError());
		return NULL;
	}
	text->fontcolor.r = 255;
	text->fontcolor.b = 255;
	text->fontcolor.g = 255;
	text->text = NULL;

	return text;
}

void gfx_text_destroy(gfx_text *text) {

	/*LOG("DEBUG: Enter %s", __func__);*/
	if(text->text != NULL) {
		SDL_DestroyTexture(text->text);
	}
	free(text);
}

gfx_image *gfx_image_init(SDL_Renderer *renderer, char *name, char* path) {

	/*LOG("DEBUG: Enter %s", __func__);*/

	gfx_image *img = calloc(1,sizeof(gfx_image));
	img->name = strdup(name);
	img->image = sdl_image_load(renderer, path);
	if (img->image == NULL) {
		LOG("ERR: Could not load image %s", path);
		free(img->name);
		free(img);
		return NULL;
	}
	return img;
}

void gfx_image_destroy(gfx_image *img) {

	/*LOG("DEBUG: Enter %s", __func__);*/

	SDL_DestroyTexture(img->image);
	free(img->name);
	free(img);
}

int gfx_image_init_mult(SDL_Renderer *renderer, gfx_image_list *imgl, char *folder) {

	/*LOG("DEBUG: Enter %s", __func__);*/

	gfx_image *img;
	DIR *dir;
	struct dirent *file;
	char img_path[128];

	strcpy(img_path, folder);
	LOG ("INFO: Loading images in dir %s",img_path);
	if ((dir = opendir(img_path)) != NULL) {
		while ((file = readdir(dir)) != NULL) {
			if (strcmp(file->d_name,".") == 0 || strcmp(file->d_name,"..") == 0) {
				continue;
			}
			strcat(img_path, file->d_name);
			img = gfx_image_init(renderer, file->d_name, img_path);
			if (img == NULL) {
				LOG("ERR: Could not init image image %s", img_path);
				gfx_image_destroy_mult(imgl);
				return 1;
			}
			DL_APPEND(imgl->head,img);
			imgl->n_images++;

			/* Reset img_dir to top */
			strcpy(img_path, folder);
		}
		closedir (dir);
	} else {
		LOG("ERR: Could not read images");
		gfx_image_destroy_mult(imgl);
		return 1;
	}

	return 0;
}

void gfx_image_destroy_mult(gfx_image_list *imgl) {

	/*LOG("DEBUG: Enter %s", __func__);*/

	gfx_image *img,*tmp;

	DL_FOREACH_SAFE(imgl->head,img,tmp) {
		DL_DELETE(imgl->head,img);
		gfx_image_destroy(img);
		imgl->n_images--;
	}
}


gfx_image * gfx_image_get(gfx_image_list *imgl, char *image) {

	/*LOG("DEBUG: Enter %s", __func__);*/

	gfx_image *img;

	DL_FOREACH(imgl->head,img) {
		if (strcmp(img->name, image) == 0) {
			return img;
		}
	}
	return NULL;
}


void gfx_text_set(SDL_Renderer *renderer, gfx_text *text, char *new_txt) {

	/*LOG("DEBUG: Enter %s", __func__);*/

	SDL_Surface *surf;

	if(text->text != NULL) {
		SDL_DestroyTexture(text->text);
	}

	surf = TTF_RenderText_Blended(text->font, new_txt, text->fontcolor);
	if(surf == NULL) {
		LOG("ERR: Unable to render text to %s, %s", new_txt, TTF_GetError());
		exit(1);
	}

	text->text = SDL_CreateTextureFromSurface(renderer, surf);
	if(text->text == NULL) {
		LOG("ERR: Unable to create texture from text, %s, %s", new_txt, TTF_GetError());
		exit(1);
	}

	SDL_FreeSurface(surf);

}

void gfx_surface_draw(SDL_Renderer *renderer, SDL_Texture *image, int x, int y, double angle) {

	SDL_Rect dest;
	int w, h;

	if(image == NULL) {
		return;
	}

	SDL_QueryTexture(image, NULL, NULL, &w, &h);

	/* Set the blitting rectangle to the size of the src image */
	dest.x = x-(w/2);
	dest.y = y-(h/2);
	dest.w = w;
	dest.h = h;

	/* Blit the entire image onto the screen at coordinates x and y */
	SDL_RenderCopyEx(renderer, image, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}

void gfx_line_draw(SDL_Renderer *renderer, int s_x, int s_y, int e_x, int e_y) {

	if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0) {
		LOG("ERR: Unable to set renderer color for line, %s", SDL_GetError());
		exit(1);
	}

	if(SDL_RenderDrawLine(renderer, s_x, s_y, e_x, e_y) != 0) {
		LOG("ERR: Unable to draw line %s", SDL_GetError());
		exit(1);
	}

}
