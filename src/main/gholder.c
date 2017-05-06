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

void gholder_update_screen(gholder * gh) {

	object *rt;
	object *pt;
	object *mn;

	/* Blank the screen */
	SDL_FillRect(gh->screen, NULL, 0);

	/* Draw the planets to x and y */
	DL_FOREACH(gh->ptl->head, pt) {
		gfx_surface_draw(gh->screen, pt->image, pt->pos->x, pt->pos->y);
	}

	/* Draw the moons to x and y */
	DL_FOREACH(gh->mnl->head, mn) {
		gfx_surface_draw(gh->screen, mn->image, mn->pos->x, mn->pos->y);
	}

	/* Draw the Home and Goal base */
	gfx_surface_draw(gh->screen, gh->hbase->image, gh->hbase->pos->x, gh->hbase->pos->y);
	gfx_surface_draw(gh->screen, gh->gbase->image, gh->gbase->pos->x, gh->gbase->pos->y);

	/* Draw the rockets to x and y */
	DL_FOREACH(gh->rtl->head, rt) {
		gfx_surface_draw(gh->screen, rt->image, rt->pos->x, rt->pos->y);
	}

	/* Draw the header, hardcoded position. */
	gfx_surface_draw(gh->screen, gh->header->text, (double)RES_WIDTH/2, (double)SPACE_H_MIN);

	/* Swap the image buffers */
	SDL_Flip(gh->screen);
}

