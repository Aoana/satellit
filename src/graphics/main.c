#include "main.h"

extern void init(char *, int, int);
extern void getInput(void);

int main(int argc, char *argv[])
{
	char *image_str;
	struct person_list *pnl;
	struct gfx_image_list *imgl;

	if ( argc != 2 ) {
		/* We print argv[0] assuming it is the program name */
		printf( "usage: %s filename\n", argv[0] );
		exit(0);
	}
	image_str = strdup(argv[1]);
	
	/* Start up SDL */
	init("A Pond of Ducks", RES_WIDTH, RES_HEIGHT);

	/* Initialize person list */
	pnl = person_list_init();

	/* Initialize images */
	imgl = gfx_init_images();
	if (imgl == NULL) {
		printf("ERR: Could not init one or more images\n");
		exit(1);
	}
	
	/* Add multiple persons */
	if (person_add_mult(pnl, imgl, 3) != PERSON_OK) {
		printf( "Init persons failed\n");
		exit(1);
	}

	/* Loop indefinitely for messages */
	while (1) {
		getInput();

		/* Update position for all objects */
		if (person_update_mult(pnl) != 0) {
			printf("ERR: Position update failed\n");
			exit(1);
		}

		/* Update Screen */
		gfx_update_screen(pnl->head);

		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}
	
	/* Exit the program */
	free(image_str);
	person_remove_mult(pnl);
	person_list_destroy(pnl);
	
	exit(0);
}
