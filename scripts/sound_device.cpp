#include <iostream>
#include <string>

#include "sound_device.h"
#include "debug.h"

ALCdevice*	SoundDevice::device		= nullptr;
ALCcontext*	SoundDevice::context	= nullptr;

SoundDevice::SoundDevice() {
	initOpenAL();
}

SoundDevice::~SoundDevice() {
	cleanupOpenAL();
}

void SoundDevice::initOpenAL() {
	if (!device) {
		device = alcOpenDevice(nullptr);
		if (!device) {
			std::cerr << "ERROR: Failed to open OpenAL device" << std::endl;
			return;
		}
	}
	if (!context) {
		context = alcCreateContext(device, nullptr);
		if (!context || !alcMakeContextCurrent(context)) {
			std::cerr << "ERROR: Failed to create OpenAL context!" << std::endl;
			alcCloseDevice(device);
			return;
		}
	}

	if (!alcMakeContextCurrent(context)) {
		std::cerr << "ERROR: Failed to set OpenAL context as current!" << std::endl;
		alcDestroyContext(context);
		alcCloseDevice(device);
		return;
	}
}

void SoundDevice::cleanupOpenAL() {
	if (context) {
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(context);
		context = nullptr;
	}

	if (device) {
		alcCloseDevice(device);
		device = nullptr;
	}
}

SoundDevice& SoundDevice::getInstance() {
	static SoundDevice instance;
	return instance;
}

ALCdevice* SoundDevice::GetDevice() {
	return device;
}

ALCcontext* SoundDevice::GetContext() {
	return context;
}
