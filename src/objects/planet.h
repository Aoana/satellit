#ifndef PLANET_H
#define PLANET_H
#include "object.h"
#include "gholder.h"

enum planetReturnCode {
    PLANET_OK = 0,
    PLANET_ADD_FAILED,
};

struct gholder;

enum planetReturnCode planet_add(struct gholder *,
	double, double, double);
#endif

