#include "main.h"

extern void init(char *, int, int);
extern void getInput(void);

int main(int argc, char *argv[])
{
	int go;
	unsigned int update_freq = 200;
	char *image_str;
	struct person * pony1;

	if ( argc != 2 ) {
		/* We print argv[0] assuming it is the program name */
		printf( "usage: %s filename\n", argv[0] );
		exit(0);
	}
	image_str = strdup(argv[1]);
	
	/* Start up SDL */
	init("A Pond of Ducks", RES_WIDTH, RES_HEIGHT);
	
	go = 1;
	
	pony1 = person_init("Pony", image_str, 360, 0);
	if (pony1 == NULL) {
		printf( "Init person failed");
		exit(1);
	}

	/* Call the cleanup function when the program exits */

	
	/* Loop indefinitely for messages */
	while (go == 1) {
		getInput();

		/* Update position */
		if (person_update(pony1) != 0) {
			printf("ERR: Position update failed");
			exit(1);
		}

		/* Update Screen */
		updateScreen(pony1->image, pony1->pos->x, pony1->pos->y);
		
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(update_freq);
	}
	
	/* Exit the program */
	free(image_str);
	person_destroy(pony1);
	
	exit(0);
}
