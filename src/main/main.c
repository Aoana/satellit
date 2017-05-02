#include "main.h"

int main(int argc, char *argv[])
{
	gholder *gh;

	if ( argc != 1 ) {
		/* We print argv[0] assuming it is the program name */
		printf("%s (no arguments)\n", argv[0]);
		exit(0);
	}

	if (getenv("GB_GIT") == NULL) {
		printf( "GB_GIT not set, source envsetting\n");
		exit(0);
	}
	
	/* Initialize the global holder */
	gh = gholder_init();

	/* Start up SDL */
	gh->screen = gfx_init_screen("GravBounce", RES_WIDTH, RES_HEIGHT);
	if (gh->screen == NULL) {
		printf("ERR: Could not init screen\n");
		exit(1);
	}

	/* Initialize images */
	gh->imgl = gfx_init_images();
	if (gh->imgl == NULL) {
		printf("ERR: Could not init one or more images\n");
		exit(1);
	}

	/* Initialize Texts */
	gh->txtl = gfx_init_texts();
	if (gh->txtl == NULL) {
		printf("ERR: Could not init texts\n");
		exit(1);
	}

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

	/* Add home base */
	if (base_add(gh, 0, SPACE_W_MIN, (SPACE_H_MAX+SPACE_H_MIN)*0.5) != OBJECT_OK) {
		printf("ERR: Init home base failed\n");
		exit(1);
	}

	/* Add goal base */
	if (base_add(gh, 1, SPACE_W_MAX, (SPACE_H_MAX+SPACE_H_MIN)*0.5) != OBJECT_OK) {
		printf("ERR: Init goal base failed\n");
		exit(1);
	}

	printf("INFO: Intro Started\n");
	/* Start Intro */
	while (gh->state == STATE_INTRO) {
		/* Get input (and check shutdown signals) */
		input_get_intro(gh);
		/* Print screen */
		gholder_update_screen(gh);
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}
	printf("INFO: Intro Done [%lf,%lf]\n", gh->vx_0, gh->vy_0);

	/* Add rocket */
	if (rocket_add(gh, SPACE_W_MIN, (SPACE_H_MAX+SPACE_H_MIN)*0.5, 1, gh->vx_0, gh->vy_0) != OBJECT_OK) {
		printf("ERR: Init rocket failed\n");
		exit(1);
	}

	/* Countdown */
	sleep(1);

	printf("INFO: Runtime Started\n");
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
		gholder_update_screen(gh);
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}
	printf("INFO: Runtime Done\n");

	if (gh->state == STATE_GAMEOVER) {
		gfx_change_text(gh->txtl, "txt_header", "GAME OVER!");
	} else if (gh->state == STATE_VICTORY) {
		gfx_change_text(gh->txtl, "txt_header", "YOU WON!");
	}
	gholder_update_screen(gh);

	printf("INFO: Finish Started\n");
	while (gh->state != STATE_SHUTDOWN) {
		/* Get shutdown signals */
		input_get_runtime(gh);
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}
	printf("INFO: Finish Done\n");
	
	/* Exit the program and cleanup */
	gholder_destroy(gh);
	exit(0);
}
