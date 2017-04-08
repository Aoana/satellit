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
 
int position_update(struct planet_list *ptl, struct person *pn) {
	struct position *p = pn->pos;
	p->x=p->x + p->vx*UPDATE_FREQ_VEL;
	p->y=p->y;
	if (position_validate(p->x, p->y) != 0) {
		return POSITION_ERR_OOB;
	}

	/* Update velocity for next timestep */
	velocity_update(ptl, pn);
	if (velocity_validate(p->vx, p->vy) != 0) {
		return POSITION_ERR_VEL;
	}
	return POSITION_OK;
}

