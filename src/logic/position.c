#include "position.h"


/* Check current resolution */
int position_validate(int x, int y) {
	if ((x >= SPACE_W_MIN && x < SPACE_W_MAX) && (y >= SPACE_H_MIN && y < SPACE_H_MAX)) {
		return 0;
	}
	return 1;
}

struct position * position_init(int x, int y, int vx, int vy) {
	struct position *p;
	if (position_validate(x, y) != 0) {
		return NULL;	
	}
	p = calloc(1, sizeof(struct position));
	p->x = x;
	p->y = y;
	p->vx = vx;
	p->vy = vy;
	return p;
} 

int position_destroy(struct position *p) {
	free(p);
	return 0;
}
 
int position_update(struct position *p) {
	p->x=p->x+5;
	p->y=p->y;
	if (position_validate(p->x, p->y) != 0) {
		return POSITION_OOB;	
	}
	/*pos->vx*/
	/*pos->vy*/
	return POSITION_OK;
}

