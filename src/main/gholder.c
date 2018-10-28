/*
 Copyright [2018] [Anders Markendahl]

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#include "gholder.h"

gholder *gholder_init(void) {

	object_list *rtl, *ptl, *mnl;
	gholder *gh;

	/* Initialize rocket list */
	rtl = object_list_init();
	if (rtl == NULL) {
		LOG("ERR: Could not init one or more images");
		return NULL;
	}

	/* Initialize planet list */
	ptl = object_list_init();
	if (ptl == NULL) {
		LOG("ERR: Could not init planet list");
		return NULL;
	}

	/* Initialize moon list */
	mnl = object_list_init();
	if (mnl == NULL) {
		LOG("ERR: Could not init moon list");
		return NULL;
	}

	gh = calloc(1,sizeof(gholder));
	gh->rtl = rtl;
	gh->ptl = ptl;
	gh->mnl = mnl;
	gh->state = STATE_INTRO;
	gh->map_number = 0;

	return gh;
}

int gholder_destroy(gholder *gh) {

	object_list_clean_all(gh->rtl);
	object_list_destroy(gh->rtl);
	object_list_clean_all(gh->ptl);
	object_list_destroy(gh->ptl);
	object_list_clean_all(gh->mnl);
	object_list_destroy(gh->mnl);
	gfx_destroy_list(gh->imgl);
	free(gh->sp);

	return 0;
}

int gholder_background_set(gholder *gh, char *background) {

	gfx_image *tmp = gfx_image_get(gh->imgl, background);
	if(tmp == NULL) {
		LOG("ERR: Unable to set background to %s", background);
		return 1;
	}

	gh->background = tmp->image;

	return 0;
}

void gholder_update_screen(gholder * gh) {

	object *rt;
	object *pt;
	object *mn;

	/* Blank the screen */
	SDL_SetRenderDrawColor(gh->renderer, 0, 0, 0, 255);
	SDL_RenderClear(gh->renderer);

	/* Draw the background. */
	gfx_surface_draw(gh->renderer, gh->background, (double)RES_WIDTH/2, (double)RES_HEIGHT/2, 0);

	/* Draw the Line describing init velocity*/
	gfx_line_draw(gh->renderer,
		gh->hbase->pos->x, gh->hbase->pos->y,
		gh->hbase->pos->x+gh->vx_0*2, gh->hbase->pos->y+gh->vy_0*2);

	/* Draw the planets to x and y */
	DL_FOREACH(gh->ptl->head, pt) {
		gfx_surface_draw(gh->renderer, pt->image, pt->pos->x, pt->pos->y, 0);
	}

	/* Draw the moons to x and y */
	DL_FOREACH(gh->mnl->head, mn) {
		gfx_surface_draw(gh->renderer, mn->image, mn->pos->x, mn->pos->y, 0);
	}

	/* Draw the Home and Goal base */
	gfx_surface_draw(gh->renderer, gh->hbase->image, gh->hbase->pos->x, gh->hbase->pos->y, 0);
	gfx_surface_draw(gh->renderer, gh->gbase->image, gh->gbase->pos->x, gh->gbase->pos->y, 0);

	/* Draw the rockets to x and y */
	DL_FOREACH(gh->rtl->head, rt) {
		gfx_surface_draw(gh->renderer, rt->image, rt->pos->x, rt->pos->y, position_get_angle(rt->pos));
	}

	/* Draw the header, hardcoded position. */
	gfx_surface_draw(gh->renderer, gh->header->text, (double)RES_WIDTH/2, (double)gh->sp->min_y, 0);

	/* Swap the image buffers */
	SDL_RenderPresent(gh->renderer);
}

void gholder_state_intro(gholder *gh) {

	LOG("INFO: Enter %s", __func__);

	/* Start background sound */
	if(audio_play_sound(gh->audiodev, "src/audio/sounds/371516__mrthenoronha__space-game-theme-loop.wav") != 0) {
		LOG("ERR: Could not queue audio for background music");
	}

	/* Start Intro */
	while (gh->state == STATE_INTRO) {
		/* Get input (and check shutdown signals) */
		input_get_intro(gh);
		/* Print screen */
		gholder_update_screen(gh);
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}

	LOG("INFO: Leave %s", __func__);
}

void gholder_state_runtime(gholder *gh) {

	LOG("INFO: Enter %s", __func__);

	/* Add rocket */
	if (rocket_add(gh, gh->hbase->pos->x, gh->hbase->pos->y, 1, gh->vx_0, gh->vy_0) != OBJECT_OK) {
		LOG("ERR: Init rocket failed");
		exit(1);
	}

	/* Start game */
	while (gh->state == STATE_RUNTIME) {
		/* Get shutdown signals */
		input_get_runtime(gh);
		/* Update all rockets */
		if (rocket_update_mult(gh) != 0) {
			LOG("ERR: Rocket update failed");
			exit(1);
		}
		/* Update all moons */
		if (moon_update_mult(gh) != 0) {
			LOG("ERR: Moon update failed");
			exit(1);
		}
		/* Print screen */
		gholder_update_screen(gh);
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}

	LOG("INFO: Leave %s", __func__);
}

void gholder_state_finish(gholder *gh) {

	LOG("INFO: Enter %s", __func__);

	if (gh->state == STATE_GAMEOVER) {
		gfx_text_set(gh->renderer, gh->header, "GAME OVER! PRESS ENTER TO TRY AGAIN");
	} else if (gh->state == STATE_VICTORY) {
		gfx_text_set(gh->renderer, gh->header, "YOU WON! PRESS ENTER TO RUN NEXT MAP");

		/* Loading next map */
		if(map_load_next(gh, 0) != 0) {
			LOG("ERR: Loading next map failed");
			exit(1);
		}
	}
	gholder_update_screen(gh);

	/* Break when we have gotten shutdown or we want to restart */
	while (gh->state != STATE_SHUTDOWN && gh->state != STATE_INTRO) {
		/* Get shutdown signals */
		input_get_finish(gh);
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}

	LOG("INFO: Leave %s", __func__);

}
