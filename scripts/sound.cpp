#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "vorbis/vorbisfile.h"

#include "sound_device.h"
#include "sound.h"
#include "debug.h"

Sound::~Sound() {	
	alcMakeContextCurrent(SoundDevice::GetContext());

	if (this->source)
		alDeleteSources(1, &this->source);
	if (this->soundBuf)
		alDeleteBuffers(1, &this->soundBuf);
}

void Sound::Generate(const char* filename, SoundType type) {
	alcMakeContextCurrent(SoundDevice::GetContext());

	if (!alcGetCurrentContext())
		std::cerr << "The device and context are not live" << std::endl;

	alGenBuffers(1, &this->soundBuf);
	Debug::checkALErrors("Generation of Sound Buffer");
	if (this->soundBuf == 0)
		std::cerr << "Sound Buffer is null" << std::endl;

	alGenSources(1, &this->source);
	Debug::checkALErrors("Generation of Source");
	if (this->source == 0)
		std::cerr << "Sound Buffer is null" << std::endl;

	std::string file(filename);
	if (file.find(".wav") != std::string::npos) {
		loadWAV(filename);
	} else if (file.find(".ogg") != std::string::npos) {
		loadOGG(filename);
	} else {
		std::cerr << "Unsupported file format: " << filename << std::endl;
	}

	this->soundType = type;
	this->defaultGain = (this->soundType == SoundType::BGM) ? 0.5f : 1.0f;
	alSourcef(this->source, AL_GAIN, this->defaultGain);

	alSourcei(this->source, AL_BUFFER, this->soundBuf);
}

void Sound::play(bool loop) {
	alcMakeContextCurrent(SoundDevice::GetContext());

	alSourcei(this->source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	Debug::checkALErrors("Setting Source");
	alSourcePlay(this->source);
	Debug::checkALErrors("Playing of Source");
}

void Sound::pause() {
	alcMakeContextCurrent(SoundDevice::GetContext());

	alSourcePause(this->source);
}

void Sound::resume() {
	alcMakeContextCurrent(SoundDevice::GetContext());

	ALint state;
	alGetSourcei(this->source, AL_SOURCE_STATE, &state);
	if (state == AL_PAUSED)
		alSourcePlay(this->source);
}

void Sound::stop() {
	alcMakeContextCurrent(SoundDevice::GetContext());

	alSourceStop(this->source);
}

void Sound::setVolume(float volume) {
	alcMakeContextCurrent(SoundDevice::GetContext());

	alSourcef(this->source, AL_GAIN, volume);
}

bool Sound::loadWAV(const char* filename) {
	alcMakeContextCurrent(SoundDevice::GetContext());

	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		std::cerr << "Failed to open WAV: " << filename << std::endl;
		return false;
	}

	char riff[4];
	file.read(riff, 4);
	file.seekg(22);

	short channels;
	file.read(reinterpret_cast<char*>(&channels), 2);

	int sampleRate;
	file.read(reinterpret_cast<char*>(&sampleRate), 4);
	
	file.seekg(34);
	short bitsPerSample;
	file.read(reinterpret_cast<char*>(&bitsPerSample), 2);

	file.seekg(40);
	int dataSize;
	file.read(reinterpret_cast<char*>(&dataSize), 4);

	std::vector<char> data(dataSize);
	file.read(data.data(), dataSize);

	ALenum format = (channels == 1)
		? (bitsPerSample == 16 ? AL_FORMAT_MONO16 : AL_FORMAT_MONO8)
		: (bitsPerSample == 16 ? AL_FORMAT_STEREO16 : AL_FORMAT_STEREO8);

	alBufferData(this->soundBuf, format, data.data(), dataSize, sampleRate);

	return true;
}

bool Sound::loadOGG(const char* filename) {
	if (!alcGetCurrentContext()) {
		std::cerr << "ERROR: OpenAL context is not active in this thread" << std::endl;
		alcMakeContextCurrent(SoundDevice::GetContext());
	}

	FILE* file = fopen(filename, "rb");
	if (!file) {
		std::cerr << "Failed to open OGG file: " << filename << std::endl;
		return false;
	}

	OggVorbis_File oggFile;
	if (ov_open(file, &oggFile, nullptr, 0) < 0) {
		std::cerr << "failed to open OGG stream" << std::endl;
		fclose(file);
		return false;
	}

	vorbis_info* info = ov_info(&oggFile, -1);
	ALenum format = info->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	long sampleRate = info->rate;

	std::vector<char> bufferData;
	char tempBuffer[4096];
	int bitstream;
	long bytesRead;

	do {
		bytesRead = ov_read(&oggFile, tempBuffer, sizeof(tempBuffer), 0, 2, 1, &bitstream);

		if (bytesRead < 0) {
			std::cerr << "Error decoding OGG file" << std::endl;
			ov_clear(&oggFile);
			fclose(file);
			return false;
		}
		bufferData.insert(bufferData.end(), tempBuffer, tempBuffer+bytesRead);
	} while (bytesRead > 0);

	alBufferData(this->soundBuf, format, bufferData.data(), bufferData.size(), sampleRate);

	ov_clear(&oggFile);
	return true;
}

void Sound::getSource() {
	std::cout << this->source << std::endl;
}

void Sound::getSoundBuf() {
	std::cout << this->soundBuf << std::endl;
}
