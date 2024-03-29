#pragma once

#include "EFxType.h"

class Fx {
public:
	static inline bool mute = false;
	AudioStream* stream = nullptr;
	EFxType fxType = FX_AMBIENT;
	Sound fxSound = { 0 };
	Vector3 position = Vector3Zero();
	const char* name = "null";
	float volume = 0.0f;
	float pitch = 0.0f;

	bool isLoaded = false;
	bool persistant = false;
	bool isPlaying = false;
	bool isActive = false;

	Fx(Wave wave, Vector3 position, const char* name) {
		this->fxSound = LoadSoundFromWave(wave);
		this->position = position;
		this->name = name;
		this->isLoaded = true;
	}

	Fx(Wave wave, const char* name) {
		this->fxSound = LoadSoundFromWave(wave);
		this->position = Vector3Zero();
		this->name = name;
		this->isLoaded = true;
	}

	Fx(Sound sound, Vector3 position, const char* name) {
		this->fxSound = sound;
		this->position = Vector3Zero();
		this->name = name;
		this->isLoaded = true;

		//	manager->loadFx(this);
	}

	Fx(Sound sound, const char* name) {
		this->fxSound = sound;
		this->position = position;
		this->name = name;
		this->isLoaded = true;
	}

	void setFxType(EFxType type) {
		this->fxType = type;
	}

	void wake() {
		this->isActive = true;
	}

	void sleep() {
		this->isActive = false;
	}

	void setVolume(float vol) {
	}

	void pause() {
		PauseSound(this->fxSound);
	}

	void resume() {
		ResumeSound(this->fxSound);
	}

	void play() {
		PlaySound(this->fxSound);
		this->isPlaying = IsSoundPlaying(this->fxSound);
	}

	void update() {
		isPlayingSound();
	}

	void isPlayingSound() {
		this->isPlaying = IsSoundPlaying(this->fxSound);
	}
};
