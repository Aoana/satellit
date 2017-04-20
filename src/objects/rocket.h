#ifndef ROCKET_H
#define ROCKET_H
#include "object.h"
#include "gholder.h"

struct gholder;
struct object;

unsigned int rocket_add(struct gholder *,
	double, double, double, double, double);
unsigned int rocket_update(struct gholder *, struct object *);
unsigned int rocket_update_mult(struct gholder *);
#endif

