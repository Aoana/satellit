#ifndef ROCKET_H
#define ROCKET_H
#include "object.h"
#include "gholder.h"

enum rocketReturnCode {
    ROCKET_OK = 0,
    ROCKET_ADD_FAILED,
};

struct gholder;

enum rocketReturnCode rocket_add(struct gholder *,
	double, double, double, double, double);
enum rocketReturnCode rocket_update_mult(struct gholder *);
#endif

