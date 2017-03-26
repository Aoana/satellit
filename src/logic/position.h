#include <stdlib.h>

struct position {
	int x;
	int y;
	int vx;
	int vy;
};

struct position * position_init(int, int, int, int);
int position_destroy(struct position *);
int position_update(struct position *);

