#include "common.h"

struct position {
	int x;
	int y;
	int vx;
	int vy;
};

enum positionReturnCode {
    POSITION_OK = 0,
    POSITION_OOB,
};

int position_validate(int x, int y);
struct position * position_init(int, int, int, int);
int position_destroy(struct position *);
int position_update(struct position *);

