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

