#include "main.h"

extern void getInput(void);

int main(int argc, char *argv[])
{
	struct person_list *pnl;
	struct planet_list *ptl;
	struct gfx_image_list *imgl;
	double vx_0, vy_0;

	if ( argc != 3 ) {
		/* We print argv[0] assuming it is the program name */
		printf( "%s [vx_0] [vy_0]\n", argv[0]);
		exit(0);
	}


	if (getenv("DUCKSPOND") == NULL) {
		printf( "DUCKSPOND not set, source envsetting\n");
		exit(0);
	}
	vx_0 = strtod(argv[1], NULL);
	vy_0 = strtod(argv[2], NULL);
	
	/* Start up SDL */
	gfx_init("A Pond of Ducks", RES_WIDTH, RES_HEIGHT);

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
	if (person_add_rocket(pnl, imgl, (int)(SPACE_W_MIN),
	(int)(SPACE_H_MAX+SPACE_H_MIN)*0.5, 1, vx_0, vy_0) != PERSON_OK) {
		printf( "Init rocket failed\n");
		exit(1);
	}

	/* Add planet 1*/
	if (planet_add_planet1(ptl, imgl, (int)(SPACE_W_MIN+SPACE_W_MAX)*0.3,
	(int)(SPACE_H_MAX+SPACE_H_MIN)*0.6, pow(10,3)) != PLANET_OK) {
		printf( "Init planet failed\n");
		exit(1);
	}

	/* Loop indefinitely for messages */
	while (1) {
		getInput();

		/* Update position for all objects */
		if (person_update_mult(ptl, pnl) != 0) {
			printf("ERR: Position update failed\n");
			exit(1);
		}

		/* Update Screen */
		gfx_update_screen(pnl->head, ptl->head);

		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}
	
	/* Exit the program and cleanup */
	person_remove_mult(pnl);
	person_list_destroy(pnl);
	planet_remove_mult(ptl);
	planet_list_destroy(ptl);
	
	exit(0);
}
