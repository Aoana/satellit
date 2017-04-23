#ifndef INPUT_H
#define INPUT_H
#include "common.h"
#include "gholder.h"
#endif

#define INPUT_INCR 5

struct gholder;
void input_get_intro(struct gholder *);
void input_get_runtime(struct gholder *);
