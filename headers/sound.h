#ifndef SOUND_H
#define SOUND_H

#include "AL/al.h"
#include "AL/alc.h"

enum class SoundType {
	BGM,
	SE
};

class Sound {
	public:
		Sound() = default;

		Sound(const Sound&) = default;
		Sound& operator=(const Sound&) = delete;

		Sound(Sound&& other) noexcept {
			this->source = other.source;
			this->soundBuf = other.soundBuf;
			other.source = 0;
			other.soundBuf = 0;
		}

		Sound& operator=(Sound&& other) noexcept {
			if (this != &other) {
				this->source = other.source;
				this->soundBuf = other.soundBuf;
				other.source = 0;
				other.soundBuf = 0;
			}
			return *this;
		}

		~Sound();

		void Generate(const char* filename, SoundType type);
		void play(bool loop = false);
		void pause();
		void resume();
		void stop();
		void setVolume(float volume);

		void getSource();
		void getSoundBuf();

	private:
		ALuint		soundBuf	= 0;
		ALuint		source		= 0;
		SoundType	soundType;
		float 		defaultGain;

		bool loadWAV(const char* filename);
		bool loadOGG(const char* filename);
};

#endif
