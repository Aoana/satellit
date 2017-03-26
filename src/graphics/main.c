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
	init("A Pond of Ducks", RES_WIDTH, RES_HEIGHT);
	
	/* Call the cleanup function when the program exits */
	atexit(cleanup);

	go = 1;
	
	smileyImage = loadImage(image_str);
	p_smiley1 = position_init(360, 0, 0, 0);
	
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
	position_destroy(p_smiley1);
	
	exit(0);
}
