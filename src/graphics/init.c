#include "init.h"

void init(char *title)
{
	/* Initialise SDL Video */
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		
		exit(1);
	}
	
	/* Open a 640 x 480 screen */
	
	screen = SDL_SetVideoMode(640, 480, 0, SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	
	if (screen == NULL)
	{
		printf("Couldn't set screen mode to 640 x 480: %s\n", SDL_GetError());

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
