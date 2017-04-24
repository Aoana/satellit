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

	return 0;

}
