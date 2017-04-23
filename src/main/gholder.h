#ifndef GHOLDER_H
#define GHOLDER_H
#include "common.h"
#include "object.h"
#include "graphics.h"

enum gstate {
	STATE_INTRO = 0,
	STATE_RUNTIME,
	STATE_SHUTDOWN,
};

typedef struct gholder {
	enum gstate state;
	struct object_list *rtl;
	struct object_list *ptl;
	struct object_list *mnl;
	struct gfx_image_list *imgl;
	double vx_0, vy_0;
} gholder; 

gholder * gholder_init(void);
int gholder_destroy(gholder *);
#endif

