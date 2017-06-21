#include "maps.h"

int map_load(struct gholder *gh, char *map) {

	config_t cfg;
	const char *bgd;

	config_init(&cfg);

	/* Read the file. If there is an error, report it and exit. */
	if(config_read_file(&cfg, map) != CONFIG_TRUE) {
		LOG("ERR: Unable to read config file %s", map);
		config_destroy(&cfg);
		return 1;
	}

	/* Set the background image. */
	if(config_lookup_string(&cfg, "background", &bgd)) {
		if(gholder_background_set(gh, (char *)bgd) != 0) {
			LOG("ERR: Set background %s failed", bgd);
			config_destroy(&cfg);
			return 1;
		}
		LOG("INFO: Background %s set", bgd);
	} else {
		LOG("ERR: Unable to find background in config");
		config_destroy(&cfg);
		return 1;
	}

	/* Add planet 1*/
	if (planet_add(gh, (SPACE_W_MIN+SPACE_W_MAX)*0.3, (SPACE_H_MAX+SPACE_H_MIN)*0.6, pow(10,3)) != OBJECT_OK) {
		LOG("ERR: Init planet failed");
		config_destroy(&cfg);
		return 1;
	}

	/* Add moon */
	if (moon_add(gh, (SPACE_W_MIN+SPACE_W_MAX)*0.4, (SPACE_H_MAX+SPACE_H_MIN)*0.5, 1, 50, 50) != OBJECT_OK) {
		LOG("ERR: Init moon failed");
		config_destroy(&cfg);
		return 1;
	}

	/* Add home base */
	if (base_add(gh, 0, SPACE_W_MIN, (SPACE_H_MAX+SPACE_H_MIN)*0.5) != OBJECT_OK) {
		LOG("ERR: Init home base failed");
		config_destroy(&cfg);
		return 1;
	}

	/* Add goal base */
	if (base_add(gh, 1, SPACE_W_MAX, (SPACE_H_MAX+SPACE_H_MIN)*0.5) != OBJECT_OK) {
		LOG("ERR: Init goal base failed");
		config_destroy(&cfg);
		return 1;
	}

	config_destroy(&cfg);
	return 0;

}

int unload_map(struct gholder *gh) {

	return 0;

}
