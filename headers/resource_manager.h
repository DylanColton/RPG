#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "sound.h"
#include "shader.h"
#include "texture.h"

class ResourceManager {
	public:
		static std::map<std::string, Shader>	Shaders;
		static std::map<std::string, Texture2D> Textures;
		static std::map<std::string, Sound>		Music;
		static std::map<std::string, Sound>		SFX;

		static Shader		&LoadShader(std::string name, const char* vSF, const char* fSF, const char* gSF);
		static Shader		&GetShader(std::string name);

		static Texture2D	&LoadTexture2D(std::string name, const char* file, bool alpha);
		static Texture2D	&GetTexture2D(std::string name);

		static Sound		&LoadMusic(std::string name, const char* file, float init_vol);
		static Sound		&GetMusic(std::string name);

		static Sound		&LoadSoundEffect(std::string name, const char* file, float init_vol);
		static Sound		&GetSoundEffect(std::string name);

		static void			Clear();

	private:
		ResourceManager() {};
		static Shader		loadShaderFromFile(const char* vSF, const char* fSF, const char* gSF);
		static Texture2D	loadTexture2DFromFile(const char* file, bool alpha);
		static Sound		loadSoundFromFile(const char* file, SoundType type);
};

#endif
