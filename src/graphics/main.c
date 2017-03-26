/* This tutorial will open a 640 x 480 screen,
** load an image and display it at specified coordinates
** and wait for the user to either close
** the window or press escape
*/

#include "main.h"

extern void init(char *, int, int);
extern void cleanup(void);
extern void getInput(void);
extern SDL_Surface *loadImage(char *);
extern void updateScreen(int, int);

int main(int argc, char *argv[])
{
	int go;
	unsigned int update_freq = 200;
	char *image_str;
	struct position * p_smiley1;

	if ( argc != 2 ) {
		/* We print argv[0] assuming it is the program name */
		printf( "usage: %s filename\n", argv[0] );
		exit(0);
	}
	image_str = strdup(argv[1]);
	
	/* Start up SDL */
	init("A Pond of Ducks", 1920, 1080);
	
	/* Call the cleanup function when the program exits */
	atexit(cleanup);

	go = 1;
	
	smileyImage = loadImage(image_str);
	p_smiley1 = calloc(1, sizeof(struct position));
	p_smiley1->x = 360;
	p_smiley1->y = 0;
	p_smiley1->vx = 0;
	p_smiley1->vy = 0;
	
	/* If we get back a NULL image, just exit */
	
	if (smileyImage == NULL) {
		printf("ERR: Image not found");
		exit(0);
	}
	
	/* Loop indefinitely for messages */
	
	while (go == 1) {
		getInput();

		/* Update position */
		if (position_update(p_smiley1) != 0) {
			printf("ERR: Position update failed");
			exit(1);
		}

		/* Update Screen */
		updateScreen(p_smiley1->x, p_smiley1->y);
		
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(update_freq);
	}
	
	/* Exit the program */
	free(image_str);
	free(p_smiley1);
	
	exit(0);
}
