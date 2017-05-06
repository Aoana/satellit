#include "main.h"

void set_image_folder(char *buf) {

	char img_dir[32] = "/src/graphics/images/";
    strcpy(buf, getenv("GB_GIT"));
	strcat(buf, img_dir);
}

void set_font_path(char *buf) {

	char img_dir[64] = "/src/graphics/fonts/FreeMono.ttf";
    strcpy(buf, getenv("GB_GIT"));
	strcat(buf, img_dir);
}


int main(int argc, char *argv[])
{
	gholder *gh;
	char img_folder[128];
	char font_path[128];

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
	gh->screen = gfx_screen_init("GravBounce", RES_WIDTH, RES_HEIGHT);
	if (gh->screen == NULL) {
		printf("ERR: Could not init screen\n");
		exit(1);
	}

	/* Initialize images */
	gh->imgl = gfx_image_list_init();
	if (gh->imgl == NULL) {
		printf("ERR: Could not init image list\n");
		exit(1);
	}
	set_image_folder(img_folder);
	if (gfx_image_init_mult(gh->imgl, img_folder) != 0) {
		printf("ERR: Could not load one or more images\n");
		exit(1);
	}

	/* Initialize Texts */
	set_font_path(font_path);
	gh->header = gfx_text_init(font_path, 30);
	if (gh->header == NULL) {
		printf("ERR: Could not init texts\n");
		exit(1);
	}
	/* Set welcome text*/
	gfx_text_set(gh->header, "Welcome to GravBounce! Please set start velocity using arrow keys");

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
		gfx_text_set(gh->header, "GAME OVER!");
	} else if (gh->state == STATE_VICTORY) {
		gfx_text_set(gh->header, "YOU WON!");
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
