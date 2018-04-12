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

#include "collision.h"

enum collisionReturnCode collision_object(object *pt, object *rt) {

	double dx, dy, d, rad;
	int w, h;
	dx = pt->pos->x - rt->pos->x;
	dy = pt->pos->y - rt->pos->y;
	d = sqrt(pow(dx,2)+pow(dy,2));
	SDL_QueryTexture(pt->image, NULL, NULL, &w, &h);
	rad = (w+h)/4;
	if ( d < rad ) {
		return COLLISION_OBJ;

	}
	return COLLISION_OK;
}

enum collisionReturnCode collision_boundary(object *rt) {
	return COLLISION_OK;
}

enum collisionReturnCode collision_object_mult(object_list *ptl, object *rt) {
	object *pt;
	DL_FOREACH(ptl->head, pt) {
		if (collision_object(pt, rt) != COLLISION_OK) {
			return COLLISION_OBJ;
		}
	}
	return COLLISION_OK;
}

