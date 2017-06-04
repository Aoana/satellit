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
	if(gfx_screen_init("GravBounce", RES_WIDTH, RES_HEIGHT, &gh->window, &gh->renderer) != 0) {
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
	if (gfx_image_init_mult(gh->renderer, gh->imgl, img_folder) != 0) {
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

	/***** Loading Map *****/
	if(gholder_background_set(gh, "gfx_background1.png") != 0) {
		printf("ERR: Set background failed\n");
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
	/***** Done loading Map *****/

intro:
	gholder_state_intro(gh);

	gholder_state_runtime(gh);

	gholder_state_finish(gh);

	if(gh->state == STATE_INTRO) {
		goto intro;
	}

	/* Exit the program and cleanup */
	gholder_destroy(gh);
	exit(0);
}
