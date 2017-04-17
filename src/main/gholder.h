#ifndef GHOLDER_H
#define GHOLDER_H
#include "common.h"
#include "object.h"
#include "graphics.h"

typedef struct gholder {
	struct object_list *rtl;
	struct object_list *ptl;
	struct object_list *mnl;
	struct gfx_image_list *imgl;
} gholder; 

gholder * gholder_init(void);
int gholder_destroy(gholder *);
#endif

