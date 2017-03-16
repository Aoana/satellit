#include "init.h"

void init(char *title, int width, int height)
{
	/* Initialise SDL Video */
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		
		exit(1);
	}
	
	screen = SDL_SetVideoMode(width, height, 0, SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	
	if (screen == NULL)
	{
		printf("Couldn't set screen mode to %d x %d: %s\n", width, height, SDL_GetError());

		exit(1);
	}
	
	/* Set the screen title */
	
	SDL_WM_SetCaption(title, NULL);
}

void cleanup()
{
	/* Free the image */
	
	if (smileyImage != NULL)
	{
		SDL_FreeSurface(smileyImage);
	}
	
	/* Shut down SDL */
	
	SDL_Quit();
}
