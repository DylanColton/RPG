#ifndef SOUND_DEVICE_H
#define SOUND_DEVICE_H

#include <AL/al.h>
#include <AL/alc.h>

class SoundDevice {
	public:
		SoundDevice();
		~SoundDevice();

		static void initOpenAL();
		static void cleanupOpenAL();

		static SoundDevice& getInstance();

		static ALCdevice* GetDevice();
		static ALCcontext* GetContext();

	private:
		static ALCdevice	*device;
		static ALCcontext	*context;
};

#endif
