#include "person.h"

struct person * person_init(char *name, char *image_str, int x, int y) {
	struct person *pn;
	pn = calloc(1, sizeof(struct person));
	pn->name = strdup(name);
	pn->pos = position_init(x, y, 0, 0);

	pn->image = loadImage(image_str);
	if (pn->image == NULL) {
		printf("ERR: Image %s not found", image_str);
		free(pn);
		return NULL;
	}

	return pn;
}

int person_destroy(struct person *pn) {
	position_destroy(pn->pos);
	cleanup(pn->image);
	free(pn);
	return 0;
}

int person_update(struct person *pn) {
	if (position_update(pn->pos) != 0) {
		return 1;
	} else {
		return 0;
	}
}


