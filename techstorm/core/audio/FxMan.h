#pragma once

#include "Fx.h"
#include "../ui/UIText.h"
#include "../ui/UIContainer.h"
#include <stdlib.h>
#include <stdio.h>
#include <queue>

#define NUM_BUFFERS 4

class FxMan {
private:
	static inline std::map<const char*, Fx*> sources;

	std::queue<Fx*> stream;

public:

	void init() {
	}

	void playActive() {
		Fx* sound = stream.front();

		sound->isPlaying = IsSoundPlaying(sound->fxSound);

		if (!sound->isPlaying) {
			sound->play();
		}

		// if the sound is persistant, add it into the stream again. then pop the bitch
		if (sound->persistant) {
			if (!sound->isPlaying) {
				stream.push(sound);
				Logman::Log("pushing ");
			}
		}
		stream.pop();
	}

	void update() {
		Fx* sound = stream.front();

		sound->update();
	}

	// methods
	static inline Fx* get(const char* name) {
		return sources[name];
	}

	/*
	* Loads a Fx from a file.
	*
	* Note:
	*	The name put into the map IS THE FILENAME (without extension). use that to search for it.
	*/
	void loadFx(const char* path) {
		// check it's extension.
		const char* ext = GetFileExtension(path);

		if (ext == "wav") {
			loadFx(new Fx(LoadWave(path), GetFileNameWithoutExt(path)));
		}
		else if (ext == "mp3") {
		}
		else {
		}
	}

	void loadFx(Fx* fx) {
		sources[fx->name] = fx;
	}

	void addToStream(const char* sound) {
		stream.push(sources[sound]);
	}

	void addToStream(Fx* fx) {
		stream.push(fx);
	}
};
