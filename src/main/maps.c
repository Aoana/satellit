#include "maps.h"

int map_load(struct gholder *gh, char *map) {

	config_t cfg;
	config_setting_t *setting;
	const char *bgd;

	config_init(&cfg);

	/* Read the file. If there is an error, report it and exit. */
	if(config_read_file(&cfg, map) != CONFIG_TRUE) {
		LOG("ERR: Unable to read config file %s", map);
		goto error;
	}

	/* Set the background image. */
	if(config_lookup_string(&cfg, "background", &bgd)) {
		if(gholder_background_set(gh, (char *)bgd) != 0) {
			LOG("ERR: Set background %s failed", bgd);
			goto error;
		}
		LOG("INFO: Background %s set", bgd);
	} else {
		LOG("ERR: Unable to find background in config");
		goto error;
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
					goto error;
				}

			} else {
				LOG("ERR: Config faulty for planet %d", i);
				goto error;
			}

		}
	} else {
		LOG("ERR: Config faulty for planet list");
		goto error;
	}

	/* Load all moons in map. */
	setting = config_lookup(&cfg, "moons");
	if(setting != NULL) {

		double x, y, m;
		int i;
		config_setting_t *moon;

		for(i = 0; i < config_setting_length(setting); ++i) {

			moon = config_setting_get_elem(setting, i);

			if(config_setting_lookup_float(moon, "x", &x)
				&& config_setting_lookup_float(moon, "y", &y)
				&& config_setting_lookup_float(moon, "m", &m)) {

				if (moon_add(gh, x, y, m) != OBJECT_OK) {
					LOG("ERR: Init moon failed");
					goto error;
				}

			} else {
				LOG("ERR: Config faulty for moon %d", i);
				goto error;
			}

		}
	} else {
		LOG("ERR: Config faulty for moon list");
		goto error;
	}

	/* Load all bases in map. */
	setting = config_lookup(&cfg, "bases");
	if(setting != NULL) {

		double x, y;
		int i, type;
		config_setting_t *base;

		for(i = 0; i < config_setting_length(setting); ++i) {

			base = config_setting_get_elem(setting, i);

			if(config_setting_lookup_int(base, "type", &type)
				&& config_setting_lookup_float(base, "x", &x)
				&& config_setting_lookup_float(base, "y", &y)) {

				if (base_add(gh, type, x, y) != OBJECT_OK) {
					LOG("ERR: Init base failed %d %f %f", type, x, y);
					goto error;
				}

			} else {
				LOG("ERR: Config faulty for base %d", i);
				goto error;
			}

		}
	} else {
		LOG("ERR: Config faulty for base list");
		goto error;
	}

	config_destroy(&cfg);
	return 0;

error:
	config_destroy(&cfg);
	return 1;

}

int map_unload(struct gholder *gh) {

	if (object_list_clean_all(gh->ptl) != OBJECT_OK) {
		LOG("ERR: Unable remove planets from old map");
		return 1;
	}
	if (object_list_clean_all(gh->mnl) != OBJECT_OK) {
		LOG("ERR: Unable remove moons from old map");
		return 1;
	}
	if (object_list_clean_all(gh->rtl) != OBJECT_OK) {
		LOG("ERR: Unable remove old rockets from old map");
		return 1;
	}
	object_destroy(gh->hbase);
	object_destroy(gh->gbase);

	return 0;

}

int map_load_next(struct gholder *gh, int map_num) {

	char map_str[64];

	LOG("INFO: Unloading old map, number %d", gh->map_number);
	if(map_unload(gh) != 0) {
		LOG("ERR: Unloading map failed");
		return 1;
	}

	if (map_num != 0) {
		gh->map_number = map_num;
	} else {
		gh->map_number++;
	}
	sprintf(map_str, "src/main/maps/map%d", gh->map_number);

	LOG("INFO: Loading new map %s, number %d", map_str, gh->map_number);
	if(map_load(gh, map_str) != 0) {
		LOG("ERR: Loading map %s failed", map_str);
		return 1;
	}

	return 0;
}
