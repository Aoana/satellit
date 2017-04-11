#include "position.h"


/* Check current resolution */
int position_validate(double x, double y) {
	if ((x >= SPACE_W_MIN && x < SPACE_W_MAX) && (y >= SPACE_H_MIN && y < SPACE_H_MAX)) {
		return 0;
	}
	return 1;
}

struct position * position_init(double x, double y, double vx, double vy) {
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
 
int position_update(struct object_list *ptl, struct object *pn) {
	struct position *p = pn->pos;
	printf("DEBUG: Start: p->x=%f, p->y=%f\n", p->x, p->y);
	printf("DEBUG: Start: p->vx=%f, p->vy=%f p->vx/UPDATE, p->vx/UPDATE = %f,%f\n", p->vx, p->vy, p->vx/UPDATE_FREQ, p->vy/UPDATE_FREQ);
	p->x = p->x + p->vx/UPDATE_FREQ;
	p->y = p->y + p->vy/UPDATE_FREQ;
	printf("DEBUG: End: p->vx=%f, p->vy=%f p->vx/UPDATE, p->vx/UPDATE = %f,%f\n", p->vx, p->vy, p->vx/UPDATE_FREQ, p->vy/UPDATE_FREQ);
	if (position_validate(p->x, p->y) != 0) {
		return POSITION_ERR_OOB;
	}
	printf("DEBUG: End: p->x=%f, p->y=%f\n", p->x, p->y);

	/* Update velocity for next timestep */
	velocity_update(ptl, pn);
	if (velocity_validate(p->vx, p->vy) != 0) {
		return POSITION_ERR_VEL;
	}
	//printf("DEBUG: Position %f,%f Velocity %f,%f\n", p->x, p->y, p->vx, p->vy);
	return POSITION_OK;
}

