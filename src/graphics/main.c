#include "main.h"

extern void init(char *, int, int);
extern void getInput(void);

int main(int argc, char *argv[])
{
	struct person_list *pnl;
	struct planet_list *ptl;
	struct gfx_image_list *imgl;

	if ( argc != 1 ) {
		/* We print argv[0] assuming it is the program name */
		printf( "No arguments\n");
		exit(0);
	}

	if (getenv("DUCKSPOND") == NULL) {
		printf( "DUCKSPOND not set, source envsetting\n");
		exit(0);
	}
	
	/* Start up SDL */
	init("A Pond of Ducks", RES_WIDTH, RES_HEIGHT);

	/* Initialize person list */
	pnl = person_list_init();
	/* Initialize planet list */
	ptl = planet_list_init();

	/* Initialize images */
	imgl = gfx_init_images();
	if (imgl == NULL) {
		printf("ERR: Could not init one or more images\n");
		exit(1);
	}

	/* Add rocket */
	if (person_add_rocket(pnl, imgl, (int)(SPACE_W_MIN),(SPACE_H_MAX+SPACE_H_MIN)*0.5) != PERSON_OK) {
		printf( "Init rocket failed\n");
		exit(1);
	}

	/* Add planet 1*/
	if (planet_add_planet1(ptl, imgl, (int)(SPACE_W_MIN+SPACE_W_MAX)*0.3,(SPACE_H_MAX+SPACE_H_MIN)*0.3) != PLANET_OK) {
		printf( "Init planet failed\n");
		exit(1);
	}
	/* Add planet 2*/
	if (planet_add_planet1(ptl, imgl, (int)(SPACE_W_MIN+SPACE_W_MAX)*0.7,(SPACE_H_MAX+SPACE_H_MIN)*0.7) != PLANET_OK) {
		printf( "Init planet failed\n");
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
		gfx_update_screen(pnl->head, ptl->head);

		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}
	
	/* Exit the program */
	person_remove_mult(pnl);
	person_list_destroy(pnl);
	
	exit(0);
}
