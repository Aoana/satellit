#include "position.h"

int position_update(struct position *pos) {
	pos->x=pos->x+10;
	pos->y=pos->y;
	/*pos->vx*/
	/*pos->vy*/
	return 0;
}

