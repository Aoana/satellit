#include "position.h"


/* Check current resolution */
int position_validate(double x, double y) {
	if ((x >= SPACE_W_MIN && x <= SPACE_W_MAX) && (y >= SPACE_H_MIN && y <= SPACE_H_MAX)) {
		return 0;
	}
	return 1;
}

position * position_init(double x, double y, double vx, double vy) {
	position *p;
	if (position_validate(x, y) != 0) {
		return NULL;	
	}
	p = calloc(1, sizeof(position));
	p->x = x;
	p->y = y;
	p->vx = vx;
	p->vy = vy;
	return p;
} 

int position_destroy(position *p) {
	free(p);
	return 0;
}
 
int position_update(object_list *ptl, object *pn) {
	position *p = pn->pos;
	p->x = p->x + p->vx/UPDATE_FREQ;
	p->y = p->y + p->vy/UPDATE_FREQ;
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

