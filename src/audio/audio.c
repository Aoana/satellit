#include "audio.h"

int audio_init(struct gholder *gh) {

	/* Open audio device */
	gh->audiodev = SDL_OpenAudioDevice(NULL, 0, NULL, NULL, 0);
	if(gh->audiodev == 0) {
		LOG("ERR: Could not open audio dev, %s", SDL_GetError());
		return 1;
	}
	return 0;

}

int audio_destroy(struct gholder *gh) {

	SDL_CloseAudioDevice(gh->audiodev);
	return 0;

}

int audio_play_sound(struct gholder *gh, char *sound) {

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;

	SDL_LoadWAV(sound, &wavSpec, &wavBuffer, &wavLength);
	if(SDL_QueueAudio(gh->audiodev, wavBuffer, wavLength) != 0) {
		LOG("ERR: Could not queue audio %s, %s", sound, SDL_GetError());
		return 1;
	}
	SDL_PauseAudioDevice(gh->audiodev, 0);
	SDL_FreeWAV(wavBuffer);
	return 0;

}
