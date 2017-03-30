#include "person.h"

struct person * person_init(int id, char *image_str, int x, int y) {
	struct person *pn;
	pn = calloc(1, sizeof(struct person));
	pn->id = id;

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

struct person * person_init_mult(char *image_str,int amount) {
	int i;	
	struct person *head = NULL, *pn;

	for( i = 0; i < amount; i++) {
		pn = person_init(i, image_str, SPACE_W_MIN, SPACE_H_MIN+i*200); 	
		if (pn == NULL) {
			printf("WARN: Unable to init person id %d, going with what we have\n", i);
			return head;
		}
		DL_APPEND(head, pn);	
	}

	return head;
}

int person_destroy(struct person *pn) {
	position_destroy(pn->pos);
	cleanup(pn->image);
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

enum personReturnCode person_add(struct person *head, int id,
									char *image_str, int x, int y) {
	struct person *pn;
	pn = person_init(id, image_str, x, y); 	
	if (pn == NULL) {
		printf("WARN: Unable to init person number\n");
		return PERSON_ADD_FAILED;
	}
	DL_APPEND(head, pn);	
	return PERSON_OK;
}

enum personReturnCode person_remove(struct person *head, int id) {
	struct person *pn, *tmp;
	DL_FOREACH_SAFE(head,pn,tmp) {
		if (pn->id == id) {
			DL_DELETE(head,pn);
			person_destroy(pn);
			return PERSON_OK;
		}
    }
	return PERSON_REMOVE_FAILED;
}

enum personReturnCode person_update(struct person *pn) {
	enum positionReturnCode ret;
	if ((ret = position_update(pn->pos)) != POSITION_OK) {
		printf("WARN: Failed to update position, id=%d, ret=%d\n",pn->id, ret);
		return PERSON_UPDATE_FAILED;
	}
	return PERSON_OK;
}

enum personReturnCode person_update_mult(struct person *head) {
	enum personReturnCode ret;
	struct person *pn;
	DL_FOREACH(head,pn) {
		if((ret = person_update(pn)) != PERSON_OK) {
			printf("WARN: Failed to update person, id=%d, ret=%d, removing\n", pn->id, ret);
			if (person_remove(head, pn->id) != PERSON_OK) {
				printf("ERR: Failed to remove person, id=%d\n", pn->id);
				return PERSON_UPDATE_FAILED;	
			}
		}
	}
	return PERSON_OK;
}
