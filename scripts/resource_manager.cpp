#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::map<std::string, Texture2D>	ResourceManager::Textures;
std::map<std::string, Shader>		ResourceManager::Shaders;
std::map<std::string, Sound>		ResourceManager::Music;
std::map<std::string, Sound>		ResourceManager::SFX;

Shader		&ResourceManager::LoadShader(std::string name, const char* vSF, const char* fSF, const char* gSF) {
	std::string vST = "shaders/";
	vST += std::string(vSF);
	vSF = vST.c_str();

	std::string fST = "shaders/";
	fST += std::string(fSF);
	fSF = fST.c_str();
	
	std::string gST;
	if (gSF != nullptr) {
		gST = "shaders/";
		gST += std::string(gSF);
		gSF = gST.c_str();
	}

	if (Shaders.find(name) == Shaders.end())
		Shaders[name] = loadShaderFromFile(vSF, fSF, gSF);
	return Shaders[name];
}
Shader		&ResourceManager::GetShader(std::string name) {
	if (Shaders.find(name) == Shaders.end()) {
		std::cerr << "Could not find shader " << name << ". Returning basic shader" << std::endl;
		if (Shaders.find("basic") == Shaders.end())
			Shaders["basic"] = loadShaderFromFile("shaders/basic.vs", "shaders/basic.fs", nullptr);
		return Shaders["basic"];
	}
	return Shaders[name];
}

Texture2D	&ResourceManager::LoadTexture2D(std::string name, const char* file, bool alpha) {
	std::string str = "resources/textures/";
	str += file;
	file = str.c_str();

	if (Textures.find(name) == Textures.end())
		Textures[name] = loadTexture2DFromFile(file, alpha);
	return Textures[name];
}
Texture2D	&ResourceManager::GetTexture2D(std::string name) {
	if (Textures.find(name) == Textures.end()) {
		std::cerr << "Could not find texture " << name << ". Returning empty texture." << std::endl;
		if (Textures.find("empty") == Textures.end())
			Textures["empty"] = loadTexture2DFromFile("resources/textures/empty.png", true);
		return Textures["empty"];
	}
	return Textures[name];
}

Sound		&ResourceManager::LoadMusic(std::string name, const char* file, float init_vol) {
	if (Music.find(name) == Music.end())
		Music[name] = loadSoundFromFile(file, SoundType::BGM);
	Music[name].setVolume(init_vol);
	return Music[name];
}
Sound		&ResourceManager::GetMusic(std::string name) {
	if (Music.find(name) == Music.end())
		std::cerr << "Could not find music " << name << std::endl;
	return Music[name];
}

Sound		&ResourceManager::LoadSoundEffect(std::string name, const char* file, float init_vol) {
	if (SFX.find(name) == SFX.end())
		SFX[name] = loadSoundFromFile(file, SoundType::SE);
	SFX[name].setVolume(init_vol);
	return SFX[name];
}
Sound		&ResourceManager::GetSoundEffect(std::string name){
	if (SFX.find(name) == SFX.end())
		std::cerr << "Could not find SFX " << name << std::endl;
	return SFX[name];
}

void		ResourceManager::Clear() {
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);

	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);

	for (auto iter : Music)
		iter.second.stop();

	for (auto iter : SFX)
		iter.second.stop();

	Music.clear();
	SFX.clear();
}

Shader		ResourceManager::loadShaderFromFile(const char* vSF, const char* fSF, const char* gSF) {
	std::string vC, fC, gC;
	try {
		std::ifstream sfV(vSF);
		std::ifstream sfF(fSF);
		std::stringstream vSS, fSS;

		vSS << sfV.rdbuf();
		fSS << sfF.rdbuf();

		sfV.close();
		sfF.close();

		vC = vSS.str();
		fC = fSS.str();

		if (gSF != nullptr) {
			std::ifstream sfG(gSF);
			std::stringstream gSS;
			gSS << sfG.rdbuf();
			sfG.close();
			gC = gSS.str();
		}
	} catch (std::exception e) {
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	const char* vSC = vC.c_str();
	const char* fSC = fC.c_str();
	const char* gSC = gC.c_str();

	Shader shader;
	shader.Compile(vSC, fSC, (gSF ? gSC : nullptr));
	return shader;
}

Texture2D	ResourceManager::loadTexture2DFromFile(const char* file, bool alpha) {
	Texture2D tex;
	if (alpha) {
		tex.IntFor = GL_RGBA;
		tex.ImgFor = GL_RGBA;
	}

	int w, h, c;
	unsigned char* d = stbi_load(file, &w, &h, &c, 0);
	tex.Generate(w, h, d);
	stbi_image_free(d);

	return tex;
}

Sound		ResourceManager::loadSoundFromFile(const char* file, SoundType type) {
	Sound sound;
	sound.Generate(file, type);
	return sound;
}
