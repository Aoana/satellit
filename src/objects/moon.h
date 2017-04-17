#ifndef MOON_H
#define MOON_H
#include "object.h"

enum moonReturnCode {
    MOON_OK = 0,
    MOON_ADD_FAILED,
};

struct gfx_image_list;

enum moonReturnCode moon_add(struct object_list *, struct gfx_image_list *,
	double, double, double, double, double);
#endif

