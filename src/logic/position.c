#include "position.h"

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
 
enum positionReturnCode position_validate(double x, double y) {
	if ((x >= SPACE_W_MIN && x <= SPACE_W_MAX) && (y >= SPACE_H_MIN && y <= SPACE_H_MAX)) {
		return POSITION_OK;
	}
	return POSITION_ERR_OOB;
}

enum positionReturnCode position_update(object_list *objl, object *obj) {
	position *p = obj->pos;
	p->x = p->x + p->vx/UPDATE_FREQ;
	p->y = p->y + p->vy/UPDATE_FREQ;
	if (position_validate(p->x, p->y) != 0) {
		return POSITION_ERR_OOB;
	}

	/* Update velocity for next timestep */
	velocity_update(objl, obj);
	if (velocity_validate(p->vx, p->vy) != 0) {
		return POSITION_ERR_VEL;
	}
	return POSITION_OK;
}

