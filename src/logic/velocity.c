#include "velocity.h"

/* Check velocity */
int velocity_validate(int vx, int vy) {
	return 0;
}

int velocity_update(struct planet_list *ptl, struct person *pn) {
	/* TODO set velocity using gravitation */
	struct position *p = pn->pos;
	p->vx=p->vx+1;
	p->vy=p->vy;
	if (velocity_validate(p->vx, p->vy) != 0) {
		return VELOCITY_NOK;	
	}
	return VELOCITY_OK;
}

