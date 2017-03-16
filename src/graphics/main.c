/* This tutorial will open a 640 x 480 screen,
** load an image and display it at specified coordinates
** and wait for the user to either close
** the window or press escape
*/

#include "main.h"

extern void init(char *);
extern void cleanup(void);
extern void getInput(void);
extern SDL_Surface *loadImage(char *);
extern void updateScreen(void);

int main(int argc, char *argv[])
{
	int go;
	char *image_str;

	if ( argc != 2 ) {
		/* We print argv[0] assuming it is the program name */
		printf( "usage: %s filename\n", argv[0] );
		exit(0);
	}

	printf( "arg: %s\n", argv[1]);
	image_str = strdup(argv[1]);
	printf( "str: %s\n", image_str);
	
	/* Start up SDL */
	
	init("Parallel Realities Tutorial 2");
	
	/* Call the cleanup function when the program exits */
	
	atexit(cleanup);

	
	
	go = 1;
	
	smileyImage = loadImage(image_str);
	
	/* If we get back a NULL image, just exit */
	
	if (smileyImage == NULL)
	{
		exit(0);
	}
	
	/* Loop indefinitely for messages */
	
	while (go == 1)
	{
		getInput();
		
		updateScreen();
		
		/* Sleep briefly to stop sucking up all the CPU time */
		
		SDL_Delay(16);
	}
	
	/* Exit the program */
	free(image_str);
	
	exit(0);
}
