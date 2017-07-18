#include "graphics.h"

SDL_Texture *sdl_image_load(SDL_Renderer *renderer, char *name) {

	/* Load the image using SDL Image */
	SDL_Surface *temp = IMG_Load(name);
	SDL_Texture *image;
	
	if (temp == NULL) 	{
		return NULL;
	}

	image = SDL_CreateTextureFromSurface(renderer, temp);
	if (image == NULL) 	{
		return NULL;
	}
	
	SDL_FreeSurface(temp);

	/* Return the processed image */
	return image;
}


enum graphicsReturnCode gfx_screen_init(char *title, int width, int height,
	SDL_Window **window, SDL_Renderer **renderer) {

	/* Initialise SDL Video */
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
		return GRAPHICS_SDL;
	}

	*window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_FULLSCREEN);
	if (*window == NULL) {
		return GRAPHICS_SDL;
	}

	*renderer = SDL_CreateRenderer(*window, -1, 0);
	if (*renderer == NULL) {
		SDL_DestroyWindow(*window);
		return GRAPHICS_SDL;
	}

	if (SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255) != 0) {
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		return GRAPHICS_SDL;
	}

	/* Initialise text management */
	if(TTF_Init() != 0) {
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		return GRAPHICS_TTF;
	}

	return GRAPHICS_OK;
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

	gfx_image_list *imgl = calloc(1, sizeof(gfx_image_list));

	return imgl;
}

void gfx_image_list_destroy(gfx_image_list *imgl) {

	free(imgl);
}

gfx_text *gfx_text_init(char *font_path, int font_size) {

	gfx_text *text = calloc(1, sizeof(gfx_text));
	text->font = TTF_OpenFont(font_path, font_size);
	if (text->font == NULL) {
		return NULL;
	}
	text->fontcolor.r = 255;
	text->fontcolor.b = 255;
	text->fontcolor.g = 255;
	text->text = NULL;

	return text;
}

void gfx_text_destroy(gfx_text *text) {

	if(text->text != NULL) {
		SDL_DestroyTexture(text->text);
	}
	free(text);
}

gfx_image *gfx_image_init(char *name) {

	gfx_image *img = calloc(1,sizeof(gfx_image));
	if (img == NULL) {
		return NULL;
	}
	img->name = strdup(name);
	if (img->name == NULL) {
		free(img);
		return NULL;
	}
	return img;
}

enum graphicsReturnCode gfx_image_destroy(gfx_image *img) {

	if(img == NULL) {
		return GRAPHICS_OK;
	}

	if(img->image != NULL) {
		SDL_DestroyTexture(img->image);
	}

	free(img->name);
	free(img);

	return GRAPHICS_OK;
}

enum graphicsReturnCode gfx_image_load(SDL_Renderer *renderer, gfx_image *img, char* path) {

	if(renderer == NULL || img == NULL) {
		return GRAPHICS_ARG;
	}

	if(img->image != NULL) {
		SDL_DestroyTexture(img->image);
	}

	img->image = sdl_image_load(renderer, path);
	if (img->image == NULL) {
		free(img->name);
		free(img);
		return GRAPHICS_SDL;
	}

	return GRAPHICS_OK;
}

gfx_image * gfx_image_get(gfx_image_list *imgl, char *image) {

	gfx_image *img;

	DL_FOREACH(imgl->head,img) {
		if (strcmp(img->name, image) == 0) {
			return img;
		}
	}
	return NULL;
}


int gfx_image_init_mult(SDL_Renderer *renderer, gfx_image_list *imgl, char *folder) {

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
			img = gfx_image_init(file->d_name);
			if (img == NULL) {
				LOG("ERR: Could not init image %s", file->d_name);
				gfx_image_destroy_mult(imgl);
				return 1;
			}
			if (gfx_image_load(renderer, img, img_path) != GRAPHICS_OK) {
				LOG("ERR: Could not load image %s", img_path);
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

	gfx_image *img,*tmp;

	DL_FOREACH_SAFE(imgl->head,img,tmp) {
		DL_DELETE(imgl->head,img);
		gfx_image_destroy(img);
		imgl->n_images--;
	}
}


enum graphicsReturnCode gfx_text_set(SDL_Renderer *renderer, gfx_text *text, char *new_txt) {

	SDL_Surface *surf;

	if(text->text != NULL) {
		SDL_DestroyTexture(text->text);
	}

	surf = TTF_RenderText_Blended(text->font, new_txt, text->fontcolor);
	if(surf == NULL) {
		return GRAPHICS_TTF;
	}

	text->text = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	if(text->text == NULL) {
		return GRAPHICS_SDL;
	}

	return GRAPHICS_OK;

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

enum graphicsReturnCode gfx_line_draw(SDL_Renderer *renderer, int s_x, int s_y, int e_x, int e_y) {

	if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0) {
		return GRAPHICS_SDL;
	}

	if(SDL_RenderDrawLine(renderer, s_x, s_y, e_x, e_y) != 0) {
		return GRAPHICS_SDL;
	}
	
	return GRAPHICS_OK;

}
