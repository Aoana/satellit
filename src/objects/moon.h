#ifndef MOON_H
#define MOON_H
#include "object.h"
#include "gholder.h"

enum moonReturnCode {
    MOON_OK = 0,
    MOON_ADD_FAILED,
};

struct gholder;

enum moonReturnCode moon_add(struct gholder *,
	double, double, double, double, double);
#endif

