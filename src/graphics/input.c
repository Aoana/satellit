#include "input.h"

void input_get_intro(gholder *gh) {

	SDL_Event event;
	char new_str[128];

	/* Loop through waiting messages and process them */

	while (SDL_PollEvent(&event)) {
		switch (event.type) {

			/* Setting the initial values for the rocket */
			/* Closing the Window or pressing Escape will exit the program */
			case SDL_QUIT:
				gh->state = STATE_SHUTDOWN;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_UP:
						if(gh->vy_0 < 101) {gh->vy_0 = gh->vy_0 + INPUT_INCR;}
						break;

					case SDLK_DOWN:
						if(gh->vy_0 > -101) {gh->vy_0 = gh->vy_0 - INPUT_INCR;}
						break;

					case SDLK_RIGHT:
						if(gh->vx_0 < 101) {gh->vx_0 = gh->vx_0 + INPUT_INCR;}
						break;

					case SDLK_LEFT:
						if(gh->vx_0 > 0) {gh->vx_0 = gh->vx_0 - INPUT_INCR;}
						break;

					case SDLK_RETURN:
						gh->state = STATE_RUNTIME;
						gfx_change_text(gh->header, "Bon Voyage!");
						break;

					case SDLK_ESCAPE:
						gh->state = STATE_SHUTDOWN;
						break;

					default:
						break;
				}
				break;
		}
	}

	if (event.key.keysym.sym == SDLK_UP ||
		event.key.keysym.sym == SDLK_DOWN ||
		event.key.keysym.sym == SDLK_RIGHT ||
		event.key.keysym.sym == SDLK_LEFT) {

		snprintf(new_str, sizeof(new_str), "Start Values: vx0 %f vy0 %f, Press Enter to start", gh->vx_0, gh->vy_0);
		gfx_change_text(gh->header, new_str);

	}
}

void input_get_runtime(gholder *gh) {

	SDL_Event event;

	/* Loop through waiting messages and process them */
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

			/* Closing the Window or pressing Escape will exit the program */
			case SDL_QUIT:
				gh->state = STATE_SHUTDOWN;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						gh->state = STATE_SHUTDOWN;
						break;

					default:
						break;
				}
				break;
		}
	}
}
