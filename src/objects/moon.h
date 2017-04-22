#ifndef MOON_H
#define MOON_H
#include "object.h"
#include "gholder.h"

struct gholder;

unsigned int moon_add(struct gholder *,
	double, double, double, double, double);
unsigned int moon_update(gholder *, struct object *);
unsigned int moon_update_mult(gholder *);
#endif

