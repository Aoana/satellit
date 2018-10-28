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

#include "planet.h"

unsigned int planet_add(gholder *gh, double x, double y, double m) {

	struct SDL_Texture *image;
	struct gfx_image *gfx_img;
	object *planet;

	gfx_img = gfx_image_get(gh->imgl,"gfx_planet_1.png");
	if (gfx_img == NULL ) {
		LOG("ERR: Unable to get image");
		return OBJECT_ADD;
	}
	image = gfx_img->image;

	planet = object_init(gh->ptl->n_objs, image, x, y, m, 0, 0, gh->sp);
	if (planet == NULL ) {
		LOG("ERR: Unable to init planet: x=%f,y=%f", x, y);
		return OBJECT_ADD;
	}

	LOG("INFO: Adding planet, id=%d %f %f %f", gh->ptl->n_objs, x, y, m);
	if (object_list_add(gh->ptl, planet) != OBJECT_OK) {
		LOG("ERR: Unable to add planet");
		return OBJECT_ADD;
	}
	return OBJECT_OK;
}

