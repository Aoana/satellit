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

#include "base.h"

unsigned int base_add(struct gholder *gh, int type, double x, double y) {

	gfx_image *gfx_img;
	object *base;

	if (type == 0) {
		gfx_img = gfx_image_get(gh->imgl,"gfx_base_home.png");
		LOG("INFO: Adding home base, id=%d %f %f", type, x, y);
	} else if (type == 1) {
		LOG("INFO: Adding goal base, id=%d %f %f", type, x, y);
		gfx_img = gfx_image_get(gh->imgl,"gfx_base_goal.png");
	} else {
		LOG("ERR: %s called with wrong type", __func__);
		exit(1);
	}

	if (gfx_img == NULL) {
		LOG("ERR: Unable to get image");
		return OBJECT_ADD;
	}

	base = object_init(type, gfx_img->image, x, y, 0, 0, 0, gh->sp);
	if (base == NULL) {
		LOG("ERR: Unable to init base: x=%f,y=%f", x, y);
		return OBJECT_ADD;
	}

	if (type == 0) {
		gh->hbase = base;
	} else {
		gh->gbase = base;
	}

	return OBJECT_OK;
}

