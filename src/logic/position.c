#include "position.h"

enum positionReturnCode position_validate(double x, double y) {
	if ((x >= SPACE_W_MIN && x <= SPACE_W_MAX) && (y >= SPACE_H_MIN && y <= SPACE_H_MAX)) {
		return POSITION_OK;
	}
	return POSITION_ERR_OOB;
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
 
enum positionReturnCode position_update(position *p) {

	p->x = p->x + p->vx/UPDATE_FREQ;
	p->y = p->y + p->vy/UPDATE_FREQ;

	if (position_validate(p->x, p->y) != POSITION_OK) {
		return POSITION_ERR_OOB;
	}

	return POSITION_OK;

}

double position_get_angle(position *p) {

	return atan2(p->vy, p->vx)*(180/M_PI);

}
