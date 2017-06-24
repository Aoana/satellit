#include "maps.h"

int map_load(struct gholder *gh, char *map) {

	config_t cfg;
	config_setting_t *setting;
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

	/* Load all planets in map. */
	setting = config_lookup(&cfg, "planets");
	if(setting != NULL) {

		double x, y, m;
		int i;
		config_setting_t *planet;

		for(i = 0; i < config_setting_length(setting); ++i) {

			planet = config_setting_get_elem(setting, i);

			if(config_setting_lookup_float(planet, "x", &x)
				&& config_setting_lookup_float(planet, "y", &y)
				&& config_setting_lookup_float(planet, "m", &m)) {

				if (planet_add(gh, x, y, m) != OBJECT_OK) {
					LOG("ERR: Init planet failed");
					config_destroy(&cfg);
					return 1;
				}

			} else {
				LOG("ERR: Config faulty for planet %d", i);
				config_destroy(&cfg);
				return 1;
			}

		}
	} else {
		LOG("ERR: Config faulty for planet list");
		config_destroy(&cfg);
		return 1;
	}

	/* Load all moons in map. */
	setting = config_lookup(&cfg, "moons");
	if(setting != NULL) {

		double x, y, m, vx, vy;
		int i;
		config_setting_t *moon;

		for(i = 0; i < config_setting_length(setting); ++i) {

			moon = config_setting_get_elem(setting, i);

			if(config_setting_lookup_float(moon, "x", &x)
				&& config_setting_lookup_float(moon, "y", &y)
				&& config_setting_lookup_float(moon, "m", &m)
				&& config_setting_lookup_float(moon, "vx", &vx)
				&& config_setting_lookup_float(moon, "vy", &vy)) {

				if (moon_add(gh, x, y, m, vx, vy) != OBJECT_OK) {
					LOG("ERR: Init moon failed");
					config_destroy(&cfg);
					return 1;
				}

			} else {
				LOG("ERR: Config faulty for moon %d", i);
				config_destroy(&cfg);
				return 1;
			}

		}
	} else {
		LOG("ERR: Config faulty for moon list");
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
