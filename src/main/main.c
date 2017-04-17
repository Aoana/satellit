#include "main.h"

extern void getInput(void);

int main(int argc, char *argv[])
{
	gholder *gh;
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
	
	gh = gholder_init();

	/* Add rocket */
	if (rocket_add(gh->rtl, gh->imgl, SPACE_W_MIN, (SPACE_H_MAX+SPACE_H_MIN)*0.5, 1, vx_0, vy_0) != ROCKET_OK) {
		printf( "Init rocket failed\n");
		exit(1);
	}

	/* Add planet 1*/
	if (planet_add(gh->ptl, gh->imgl, (SPACE_W_MIN+SPACE_W_MAX)*0.3, (SPACE_H_MAX+SPACE_H_MIN)*0.6, pow(10,3)) != PLANET_OK) {
		printf( "Init planet failed\n");
		exit(1);
	}

	/* Add moon */
	if (moon_add(gh->mnl, gh->imgl, (SPACE_W_MIN+SPACE_W_MAX)*0.4, (SPACE_H_MAX+SPACE_H_MIN)*0.5, 1, 0, 0) != MOON_OK) {
		printf( "Init moon failed\n");
		exit(1);
	}

	/* Loop indefinitely for messages */
	while (1) {
		getInput();

		/* Update position for all objects */
		if (object_update_mult(gh->ptl, gh->rtl, gh->imgl) != 0) {
			printf("ERR: Position update failed\n");
			exit(1);
		}

		/* Update Screen */
		gfx_update_screen(gh->rtl->head, gh->ptl->head, gh->mnl->head);

		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}
	
	/* Exit the program and cleanup */
	gholder_destroy(gh);
	exit(0);
}
