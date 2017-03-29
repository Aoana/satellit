#include "person.h"

struct person * person_init(char *name, char *image_str, int x, int y) {
	struct person *pn;
	pn = calloc(1, sizeof(struct person));
	pn->name = strdup(name);

	pn->pos = position_init(x, y, 0, 0);
	if (pn->pos == NULL) {
		printf("ERR: Unable to init position %d,%d", x, y);
		free(pn->name);
		free(pn);
		return NULL;
	}

	pn->image = loadImage(image_str);
	if (pn->image == NULL) {
		printf("ERR: Image %s not found", image_str);
		free(pn->name);
		free(pn);
		return NULL;
	}

	return pn;
}

struct person * person_init_mult(char *name_template, char *image_str,int amount) {
	int i;	
	struct person *head = NULL, *pn;

	for( i = 0; i < amount; i++) {
		pn = person_init(name_template, image_str, 0, i*100); 	
		if (pn == NULL) {
			printf("WARN: Unable to init person number %d, stopping", i);
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


int person_update(struct person *pn) {
	if (position_update(pn->pos) != 0) {
		printf("ERR: Failed to update position");
		return 1;
	}
	return 0;
}

int person_update_mult(struct person *head) {
	struct person *pn;
	DL_FOREACH(head,pn) {
		if(person_update(pn) != 0) {
			printf("ERR: Failed to update person");
			return 1;
		}
	}
	return 0;
}
