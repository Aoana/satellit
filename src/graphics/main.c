#include "main.h"

extern void init(char *, int, int);
extern void getInput(void);
struct person *head = NULL;

int main(int argc, char *argv[])
{
	int go;
	unsigned int update_freq = 200;
	char *image_str;

	if ( argc != 2 ) {
		/* We print argv[0] assuming it is the program name */
		printf( "usage: %s filename\n", argv[0] );
		exit(0);
	}
	image_str = strdup(argv[1]);
	
	/* Start up SDL */
	init("A Pond of Ducks", RES_WIDTH, RES_HEIGHT);
	
	go = 1;

	head = person_init_mult("pony", image_str, 2);
	if (head == NULL) {
		printf( "Init persons failed");
		exit(1);
	}

	/* Loop indefinitely for messages */
	while (go == 1) {
		getInput();

		/* Update position */
		if (person_update_mult(head) != 0) {
			printf("ERR: Position update failed");
			exit(1);
		}

		/* Update Screen */
		gfx_update_mult(head);
		
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(update_freq);
	}
	
	/* Exit the program */
	free(image_str);
	person_destroy_mult(head);
	
	exit(0);
}
