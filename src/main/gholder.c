#include "gholder.h"

gholder * gholder_init(void) {

	object_list *rtl, *ptl, *mnl;
	gfx_image_list *imgl, *txtl;
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

	/* Initialize images */
	imgl = gfx_init_images();
	if (imgl == NULL) {
		printf("ERR: Could not init one or more images\n");
		return NULL;
	}

	/* Initialize Texts */
	txtl = gfx_init_texts();
	if (txtl == NULL) {
		printf("ERR: Could not init texts\n");
		return NULL;
	}

	gh = calloc(1,sizeof(gholder));
	gh->rtl = rtl;
	gh->ptl = ptl;
	gh->mnl = mnl;
	gh->hbase = NULL;
	gh->gbase = NULL;
	gh->imgl = imgl;
	gh->txtl = txtl;
	gh->vx_0 = 0;
	gh->vy_0 = 0;
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
	gfx_destroy_images(gh->imgl);
	gfx_destroy_texts(gh->txtl);

	return 0;

}

void gholder_update_screen(gholder * gh) {

	object *rt;
	object *pt;
	object *mn;
	gfx_image *txt;

	/* Blank the screen */
	SDL_FillRect(screen, NULL, 0);

	/* Draw the planets to x and y */
	DL_FOREACH(gh->ptl->head, pt) {
		gfx_draw_image(pt->image, pt->pos->x, pt->pos->y);
	}

	/* Draw the moons to x and y */
	DL_FOREACH(gh->mnl->head, mn) {
		gfx_draw_image(mn->image, mn->pos->x, mn->pos->y);
	}

	/* Draw the Home and Goal base */
	gfx_draw_image(gh->hbase->image, gh->hbase->pos->x, gh->hbase->pos->y);
	gfx_draw_image(gh->gbase->image, gh->gbase->pos->x, gh->gbase->pos->y);

	/* Draw the rockets to x and y */
	DL_FOREACH(gh->rtl->head, rt) {
		gfx_draw_image(rt->image, rt->pos->x, rt->pos->y);
	}

	/* Draw the text to x and y */
	DL_FOREACH(gh->txtl->head, txt) {
		gfx_draw_image(txt->image, (double)RES_WIDTH/2, (double)SPACE_H_MIN);
	}

	/* Swap the image buffers */
	SDL_Flip(screen);
}

