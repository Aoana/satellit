#include "velocity.h"

/* Check velocity */
int velocity_validate(double vx, double vy) {
	return 0;
}

int velocity_update(struct object_list *ptl, struct object *pn) {

	double a_x = 0, a_y = 0;
	double f_x = 0, f_y = 0;
	double dx, dy, d;
	struct object *pt;
	struct position *p = pn->pos;

	DL_FOREACH(ptl->head, pt) {
		dx = pt->pos->x - p->x;
		dy = pt->pos->y - p->y;
		d = sqrt(pow(dx,2)+pow(dy,2));
		f_x = f_x + (GRAV_CONST*pt->mass*pn->mass*dx)/pow(d,3);
		f_y = f_y + (GRAV_CONST*pt->mass*pn->mass*dy)/pow(d,3);
		//printf("DEBUG: d=[%f,%f,%f] f=[%f,%f,%f] p=[%f,%f] pt=[%f,%f]\n", dx, dy, d, f_x, f_y, f, p->x, p->y, pt->pos->x, pt->pos->y);
	}
	a_x = f_x/pn->mass;	
	a_y = f_y/pn->mass;
	
	p->vx = p->vx + a_x/UPDATE_FREQ;
	p->vy = p->vy + a_y/UPDATE_FREQ;
	if (velocity_validate(p->vx, p->vy) != 0) {
		return VELOCITY_NOK;	
	}
	//printf("DEBUG: velocity %f,%f\n", p->vx, p->vy);
	return VELOCITY_OK;
}

