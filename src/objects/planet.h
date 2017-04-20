#ifndef PLANET_H
#define PLANET_H
#include "object.h"
#include "gholder.h"

struct gholder;

unsigned int planet_add(struct gholder *,
	double, double, double);
#endif

