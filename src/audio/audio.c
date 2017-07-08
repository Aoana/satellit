#include "audio.h"

int audio_init(struct gholder *gh) {


	SDL_AudioSpec want, have;
	SDL_memset(&want, 0, sizeof(want));
	want.freq = 48000;
	want.format = AUDIO_S16;
	want.channels = 2;
	want.samples = 4096;
	want.callback = NULL;

	LOG("INFO: Opening audio dev: freq=%d, format=%s, channels=%d, samples=%d", want.freq, "AUDIO_F32", want.channels, want.samples);
	/* Open audio device */
	gh->audiodev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
	if(gh->audiodev == 0) {
		LOG("ERR: Could not open audio dev, %s", SDL_GetError());
		return 1;
	} else {
		if (have.format != want.format) {
			LOG("WARN: We didn't get Float32 audio format.");
		}
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
