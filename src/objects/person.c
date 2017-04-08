#include "person.h"

struct person_list * person_list_init() {
	struct person_list *pnl;
	pnl = calloc(1, sizeof(struct person_list));
	pnl->n_pns = 0;
	pnl->head = NULL;
	return pnl;
}

int person_list_destroy(struct person_list *pnl) {
	free(pnl);
	return 0;
}

struct person * person_init(int id, SDL_Surface *image, int x, int y, int m) {
	struct person *pn;
	pn = calloc(1, sizeof(struct person));
	pn->id = id;
	pn->mass = m;
	pn->next = NULL;
	pn->prev = NULL;

	pn->pos = position_init(x, y, 0, 0);
	if (pn->pos == NULL) {
		printf("ERR: Unable to init position %d,%d\n", x, y);
		free(pn);
		return NULL;
	}

	pn->image = image;

	return pn;
}

int person_destroy(struct person *pn) {
	position_destroy(pn->pos);
	free(pn);
	return 0;
}

enum personReturnCode person_add(struct person_list *pnl, int id,
	SDL_Surface *image, int x, int y, int m) {

	struct person *pn;
	pn = person_init(id, image, x, y, m);
	if (pn == NULL) {
		printf("WARN: Unable to init person number\n");
		return PERSON_ADD_FAILED;
	}
	DL_APPEND(pnl->head, pn);
	pnl->n_pns++;
	return PERSON_OK;
}

enum personReturnCode person_add_rocket(struct person_list *pnl,
	struct gfx_image_list *imgl, int x, int y, int m) {

	struct SDL_Surface *image;
	struct gfx_image *gfx_img;

	gfx_img = gfx_get_image(imgl,"gfx_ship.png");
	if (gfx_img == NULL ) {
		printf("ERR: Unable to get image\n");
		return PERSON_ADD_FAILED;
	}
	image = gfx_img->image;

	if (person_add(pnl, pnl->n_pns, image, x, y, m) != PERSON_OK) {
		printf("ERR: Unable to add rocket\n");
		return PERSON_ADD_FAILED;
	}
	return PERSON_OK;
}

enum personReturnCode person_remove(struct person_list *pnl, struct person *pn) {
	DL_DELETE(pnl->head,pn);
	if(person_destroy(pn) != PERSON_OK) {
		return PERSON_REMOVE_FAILED;
	}
	pnl->n_pns--;
	return PERSON_OK;
}

enum personReturnCode person_remove_mult(struct person_list *pnl) {
	struct person *pn, *tmp;
	DL_FOREACH_SAFE(pnl->head,pn,tmp) {
		if(person_remove(pnl, pn) != PERSON_OK) {
			return PERSON_REMOVE_FAILED;
		}
    }
	return PERSON_OK;
}

enum personReturnCode person_remove_id(struct person_list *pnl, int id) {
	struct person *pn, *tmp;
	DL_FOREACH_SAFE(pnl->head,pn,tmp) {
		if (pn->id == id) {
			DL_DELETE(pnl->head,pn);
			if(person_destroy(pn) != PERSON_OK) {
				return PERSON_REMOVE_FAILED;
			}
			return PERSON_OK;
		}
    }
	return PERSON_NOT_FOUND;
}

enum personReturnCode person_update(struct planet_list *ptl, struct person *pn) {
	enum positionReturnCode ret;
	if ((ret = position_update(ptl, pn)) != POSITION_OK) {
		printf("WARN: Failed to update position, id=%d, ret=%d\n",pn->id, ret);
		return PERSON_UPDATE_FAILED;
	}
	return PERSON_OK;
}

enum personReturnCode person_update_mult(struct planet_list *ptl, struct person_list *pnl) {
       enum personReturnCode ret;
       struct person *pn, *tmp;
       DL_FOREACH_SAFE(pnl->head, pn, tmp) {
               if((ret = person_update(ptl, pn)) != PERSON_OK) {
                       printf("WARN: Failed to update person, id=%d, ret=%d, removing\n", pn->id, ret);
                       if (person_remove(pnl, pn) != PERSON_OK) {
                               printf("ERR: Failed to remove person, id=%d\n", pn->id);
                       }
               }
       }
       return PERSON_OK;
}

