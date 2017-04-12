#ifndef ROCKET_H
#define ROCKET_H
#include "object.h"

enum rocketReturnCode {
    ROCKET_OK = 0,
    ROCKET_ADD_FAILED,
};

struct object_list;
struct gfx_image_list;

enum rocketReturnCode rocket_add(struct object_list *, struct gfx_image_list *,
	double, double, double, double, double);
#endif

