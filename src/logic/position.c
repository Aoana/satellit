#include "position.h"

struct position * position_init(int x, int y, int vx, int vy) {
	struct position *p;
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
	p->y=p->y+5;
	/*pos->vx*/
	/*pos->vy*/
	return 0;
}

