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

struct person * person_init(int id, char *image_str, int x, int y) {
	struct person *pn;
	pn = calloc(1, sizeof(struct person));
	pn->id = id;
	pn->next = NULL;
	pn->prev = NULL;

	pn->pos = position_init(x, y, 0, 0);
	if (pn->pos == NULL) {
		printf("ERR: Unable to init position %d,%d\n", x, y);
		free(pn);
		return NULL;
	}

	pn->image = loadImage(image_str);
	if (pn->image == NULL) {
		printf("ERR: Image %s not found\n", image_str);
		free(pn);
		return NULL;
	}

	return pn;
}

enum personReturnCode person_init_mult(struct person_list *pnl, char *image_str, int amount) {
	int i;	
	struct person *pn;

	for( i = 0; i < amount; i++) {
		pn = person_init(i, image_str, SPACE_W_MIN, SPACE_H_MIN+i*200); 	
		if (pn == NULL) {
			printf("WARN: Unable to init person id %d, going with what we have\n", i);
			return PERSON_OK;
		}
		DL_APPEND(pnl->head, pn);
		pnl->n_pns++;
	}
	return PERSON_OK;
}

int person_destroy(struct person *pn) {
	position_destroy(pn->pos);
//	cleanup(pn->image);
	free(pn);
	return 0;
}

int person_destroy_mult(struct person *head) {
	struct person *pn, *tmp;
	DL_FOREACH_SAFE(head,pn,tmp) {
		DL_DELETE(head,pn);
		person_destroy(pn);
    }
	return 0;
}

enum personReturnCode person_add(struct person_list *pnl, int id,
									char *image_str, int x, int y) {
	struct person *pn;
	pn = person_init(id, image_str, x, y); 	
	if (pn == NULL) {
		printf("WARN: Unable to init person number\n");
		return PERSON_ADD_FAILED;
	}
	DL_APPEND(pnl->head, pn);
	pnl->n_pns++;
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

enum personReturnCode person_update(struct person *pn) {
	printf("INFO: Enter %s\n", __func__);
	enum positionReturnCode ret;
	if ((ret = position_update(pn->pos)) != POSITION_OK) {
		printf("WARN: Failed to update position, id=%d, ret=%d\n",pn->id, ret);
		return PERSON_UPDATE_FAILED;
	}
	return PERSON_OK;
}

enum personReturnCode person_update_mult(struct person_list *pnl) {
	enum personReturnCode ret;
	struct person *pn, *tmp;
	DL_FOREACH_SAFE(pnl->head, pn, tmp) {
		printf("DEBUG: call update for %p\n", (void *)pn);
		if((ret = person_update(pn)) != PERSON_OK) {
			printf("WARN: Failed to update person, id=%d, ret=%d, removing\n", pn->id, ret);
			if (person_remove(pnl, pn) != PERSON_OK) {
				printf("ERR: Failed to remove person, id=%d\n", pn->id);
			}
		}
		printf("INFO: Updated person %p\n", (void *)pn);
		printf("DEBUG: head %p\n", (void *)pnl->head);
	}
	return PERSON_OK;
}
