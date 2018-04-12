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

/**
 * @file
 * @brief Description of the object base
 */

#ifndef BASE_H
#define BASE_H
#include "object.h"
#include "gholder.h"

struct gholder;
struct object;

/**
 * @brief Add a base object.
 * @param gh Pointer to the global game holder.
 * @param type Type of base, 0 home base, 1 goal base
 * @param x Position X
 * @param y Position Y
 * @return OBJECT_OK if passed, OBJECT_ADD if failed.
 * @see objectReturnCode.
 * @see object_add.
 *
 */
unsigned int base_add(struct gholder *gh, int type, double x, double y);
#endif

