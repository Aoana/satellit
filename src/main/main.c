#include "main.h"

int main(int argc, char *argv[])
{
	gholder *gh;

	if ( argc != 1 ) {
		/* We print argv[0] assuming it is the program name */
		printf("%s (no arguments)\n", argv[0]);
		exit(0);
	}

	if (getenv("DUCKSPOND") == NULL) {
		printf( "DUCKSPOND not set, source envsetting\n");
		exit(0);
	}
	
	/* Start up SDL */
	gfx_init("A Pond of Ducks", RES_WIDTH, RES_HEIGHT);
	
	/* Initialize the global holder */
	gh = gholder_init();

	/* Add planet 1*/
	if (planet_add(gh, (SPACE_W_MIN+SPACE_W_MAX)*0.3, (SPACE_H_MAX+SPACE_H_MIN)*0.6, pow(10,3)) != OBJECT_OK) {
		printf("ERR: Init planet failed\n");
		exit(1);
	}

	/* Add moon */
	if (moon_add(gh, (SPACE_W_MIN+SPACE_W_MAX)*0.4, (SPACE_H_MAX+SPACE_H_MIN)*0.5, 1, 50, 50) != OBJECT_OK) {
		printf("ERR: Init moon failed\n");
		exit(1);
	}

	printf("INFO: Starting Intro\n");
	/* Start Intro */
	while (gh->state == STATE_INTRO) {
		/* Get input (and check shutdown signals) */
		input_get_intro(gh);
		/* Print screen */
		gfx_update_screen(gh);
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}
	printf("INFO: Done Intro\n");

	/* Add rocket */
	if (rocket_add(gh, SPACE_W_MIN, (SPACE_H_MAX+SPACE_H_MIN)*0.5, 1, gh->vx_0, gh->vy_0) != OBJECT_OK) {
		printf("ERR: Init rocket failed\n");
		exit(1);
	}

	/* Countdown */
	sleep(3);

	printf("INFO: Starting Runtime\n");
	/* Start game */
	while (gh->state == STATE_RUNTIME) {
		/* Get shutdown signals */
		input_get_runtime(gh);
		/* Update all rockets */
		if (rocket_update_mult(gh) != 0) {
			printf("ERR: Rocket update failed\n");
			exit(1);
		}
		/* Update all moons */
		if (moon_update_mult(gh) != 0) {
			printf("ERR: Moon update failed\n");
			exit(1);
		}
		/* Print screen */
		gfx_update_screen(gh);
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}
	printf("INFO: Done Runtime\n");
	
	/* Exit the program and cleanup */
	gholder_destroy(gh);
	exit(0);
}
