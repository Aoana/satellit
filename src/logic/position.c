/*
 Copyright [2018] [Anders Markendahl]

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#include "position.h"

enum positionReturnCode position_validate(double x, double y, struct space *sp) {
	if ((x >= sp->min_x && x <= sp->max_x) && (y >= sp->min_y && y <= sp->max_y)) {
		return POSITION_OK;
	}
	return POSITION_ERR_OOB;
}

position * position_init(double x, double y, double vx, double vy, struct space *sp) {
	position *p;
	if (position_validate(x, y, sp) != 0) {
		return NULL;
	}
	p = calloc(1, sizeof(position));
	p->x = x;
	p->y = y;
	p->vx = vx;
	p->vy = vy;
	return p;
}

int position_destroy(position *p) {
	free(p);
	return 0;
}

space * position_space_init(double min_x, double max_x, double min_y, double max_y) {
	space *sp = calloc(1, sizeof(space));

	sp->min_x = min_x;
	sp->max_x = max_x;
	sp->min_y = min_y;
	sp->max_y = max_y;

	return sp;
}

int position_space_destroy(space *sp) {
	free(sp);
	return 0;
}

enum positionReturnCode position_update(position *p, struct space *sp) {

	p->x = p->x + p->vx/UPDATE_FREQ;
	p->y = p->y + p->vy/UPDATE_FREQ;

	if (position_validate(p->x, p->y, sp) != POSITION_OK) {
		return POSITION_ERR_OOB;
	}

	return POSITION_OK;

}

double position_get_angle(position *p) {

	return atan2(p->vy, p->vx)*(180/M_PI);

}
