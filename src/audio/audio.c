#include "audio.h"

int audio_init(struct gholder *gh) {

	/* Open audio device */
	gh->audiodev = SDL_OpenAudioDevice(NULL, 0, NULL, NULL, 0);
	if(gh->audiodev == 0) {
		LOG("ERR: Could not open audio dev, %s", SDL_GetError());
		return 1;
	}

	/* TODO Load sounds */


	return 0;

}

int audio_destroy(struct gholder *gh) {

	SDL_CloseAudioDevice(gh->audiodev);
	return 0;

}

int audio_play_sound(struct gholder *gh, char *sound) {
	return 0;
}
