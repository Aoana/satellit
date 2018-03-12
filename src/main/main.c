#include "main.h"

void set_log_path(char *buf) {

	char log_name[64] = "/gravbounce.log";
    strcpy(buf, getenv("GB_WS"));
	strcat(buf, log_name);
}

int main(int argc, char *argv[])
{
	gholder *gh;
	int start_map = 1;

#ifdef DEBUG
	char log_path[128];
	if (getenv("GB_WS") == NULL) {
		printf( "GB_WS not set, source envsetting\n");
		exit(1);
	}
	set_log_path(log_path);
	if (log_init(log_path) != 0) {
		printf("ERR: Initialization of logging failed, quitting, err = %s\n", strerror(errno));
		exit(1);
	}
	if (argc == 2) {
		start_map = atoi(argv[1]);
		LOG("DEBUG: start map set to %s", argv[1]);
	}
#endif

	LOG("####### Starting a new game of %s", argv[0]);

	/* Initialize the global holder */
	gh = gholder_init();

	/* Start up SDL */
	if(gfx_screen_init("GravBounce", RES_WIDTH, RES_HEIGHT, &gh->window, &gh->renderer) != 0) {
		LOG("ERR: Could not init screen");
		exit(1);
	}

	/* Initialize images */
	gh->imgl = gfx_image_list_init();
	if (gh->imgl == NULL) {
		LOG("ERR: Could not init image list");
		exit(1);
	}
	if (gfx_populate_list_folder(gh->renderer, gh->imgl, "src/graphics/images/") != 0) {
		LOG("ERR: Could not load one or more images");
		exit(1);
	}

	/* Initialize Texts */
	gh->header = gfx_text_init("src/graphics/fonts/FreeMono.ttf", 30);
	if (gh->header == NULL) {
		LOG("ERR: Could not init texts");
		exit(1);
	}

	/* Initialize Audio */
	if (audio_init(gh) != 0) {
		LOG("ERR: Could not init audio");
		exit(1);
	}

	/* Loading Map 1 (unless debug overwrite) */
	if(map_load_next(gh, start_map) != 0) {
		LOG("ERR: Loading map failed");
		exit(1);
	}

intro:
	gholder_state_intro(gh);

	gholder_state_runtime(gh);

	gholder_state_finish(gh);

	if(gh->state == STATE_INTRO) {
		goto intro;
	}

	/* Exit the program and cleanup */
	gfx_text_destroy(gh->header);
	gfx_screen_destroy(gh->window, gh->renderer);
	gholder_destroy(gh);

#ifdef DEBUG
	if (log_destroy() != 0) {
		printf("ERR: Shutting down logging failed, err = %s\n", strerror(errno));
	}
#endif

	exit(0);
}
