#include "position.h"

int position_validate(int x, int y) {
	if ((x >= 0 && x < RES_WIDTH) && (y >= 0 && y < RES_HEIGHT)) {
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
	p->x=p->x+10;
	p->y=p->y;
	if (position_validate(p->x, p->y) != 0) {
		return 1;	
	}
	/*pos->vx*/
	/*pos->vy*/
	return 0;
}

