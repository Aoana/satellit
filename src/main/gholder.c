#include "gholder.h"

gholder *gholder_init(void) {

	object_list *rtl, *ptl, *mnl;
	gholder *gh;

	/* Initialize rocket list */
	rtl = object_list_init();
	if (rtl == NULL) {
		printf("ERR: Could not init one or more images\n");
		return NULL;
	}

	/* Initialize planet list */
	ptl = object_list_init();
	if (ptl == NULL) {
		printf("ERR: Could not init planet list\n");
		return NULL;
	}

	/* Initialize moon list */
	mnl = object_list_init();
	if (mnl == NULL) {
		printf("ERR: Could not init moon list\n");
		return NULL;
	}

	gh = calloc(1,sizeof(gholder));
	gh->rtl = rtl;
	gh->ptl = ptl;
	gh->mnl = mnl;
	gh->state = STATE_INTRO;

	return gh;
}

int gholder_destroy(gholder *gh) {

	object_remove_mult(gh->rtl);
	object_list_destroy(gh->rtl);
	object_remove_mult(gh->ptl);
	object_list_destroy(gh->ptl);
	object_remove_mult(gh->mnl);
	object_list_destroy(gh->mnl);
	gfx_image_destroy_mult(gh->imgl);
	gfx_text_destroy(gh->header);

	return 0;
}

int gholder_background_set(gholder *gh, char *background) {

	gfx_image *tmp = gfx_image_get(gh->imgl, background);
	if(tmp == NULL) {
		printf("ERR: Unable to set background to %s\n", background);
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
		gfx_surface_draw(gh->renderer, rt->image, rt->pos->x, rt->pos->y, object_get_angle(rt));
	}

	/* Draw the header, hardcoded position. */
	gfx_surface_draw(gh->renderer, gh->header->text, (double)RES_WIDTH/2, (double)SPACE_H_MIN, 0);

	/* Swap the image buffers */
	SDL_RenderPresent(gh->renderer);
}

void gholder_state_intro(gholder *gh) {

	printf("INFO: Enter %s\n", __func__);

	/* Start Intro */
	while (gh->state == STATE_INTRO) {
		/* Get input (and check shutdown signals) */
		input_get_intro(gh);
		/* Print screen */
		gholder_update_screen(gh);
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}

	printf("INFO: Leave %s\n", __func__);
}

void gholder_state_runtime(gholder *gh) {

	printf("INFO: Enter %s\n", __func__);

	/*TODO Switch to hbase position*/
	/* Add rocket */
	if (rocket_add(gh, SPACE_W_MIN, (SPACE_H_MAX+SPACE_H_MIN)*0.5, 1, gh->vx_0, gh->vy_0) != OBJECT_OK) {
		printf("ERR: Init rocket failed\n");
		exit(1);
	}

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

	printf("INFO: Leave %s\n", __func__);
}

void gholder_state_finish(gholder *gh) {

	printf("INFO: Enter %s\n", __func__);

	if (gh->state == STATE_GAMEOVER) {
		gfx_text_set(gh->renderer, gh->header, "GAME OVER!");
	} else if (gh->state == STATE_VICTORY) {
		gfx_text_set(gh->renderer, gh->header, "YOU WON!");
	}
	gholder_update_screen(gh);

	while (gh->state != STATE_SHUTDOWN) {
		/* Get shutdown signals */
		input_get_runtime(gh);
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(UPDATE_FREQ);
	}

	printf("INFO: Leave %s\n", __func__);

}
