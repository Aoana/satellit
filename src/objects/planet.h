#ifndef PLANET_H
#define PLANET_H
#include "object.h"

enum planetReturnCode {
    PLANET_OK = 0,
    PLANET_ADD_FAILED,
};

struct object_list;
struct gfx_image_list;

enum planetReturnCode planet_add(struct object_list *,
	struct gfx_image_list *, double, double, double);
#endif

