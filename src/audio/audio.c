#include "audio.h"

SDL_AudioDeviceID * audio_init() {

	SDL_AudioSpec want, have;
	SDL_AudioDeviceID *audiodev;
	SDL_memset(&want, 0, sizeof(want));
	want.freq = 44100;
	want.format = AUDIO_S16;
	want.channels = 2;
	want.samples = 4096;
	want.callback = NULL;

	audiodev = (SDL_AudioDeviceID*)calloc(1, sizeof(SDL_AudioDeviceID));

	LOG("INFO: Opening audio dev: freq=%d, format=%s, channels=%d, samples=%d", want.freq, "AUDIO_F32", want.channels, want.samples);

	/* Open audio device */
	*audiodev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
	if(*audiodev == 0) {
		LOG("ERR: Could not open audio dev, %s", SDL_GetError());
		return NULL;
	} else {
		if (have.format != want.format) {
		LOG("WARN: We didn't get Float32 audio format.");
		}
	}

	return audiodev;

}

int audio_destroy(SDL_AudioDeviceID *audiodev) {

	SDL_CloseAudioDevice(*audiodev);
	free(audiodev);
	return 0;

}

int audio_play_sound(SDL_AudioDeviceID *audiodev, char *sound) {

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;

	SDL_LoadWAV(sound, &wavSpec, &wavBuffer, &wavLength);
	if(SDL_QueueAudio(*audiodev, wavBuffer, wavLength) != 0) {
		LOG("ERR: Could not queue audio %s, %s", sound, SDL_GetError());
		return 1;
	}
	SDL_PauseAudioDevice(*audiodev, 0);
	SDL_FreeWAV(wavBuffer);
	return 0;

}
