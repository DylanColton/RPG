#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture2D {
	public:
		unsigned int ID;
		unsigned int W, H;
		unsigned int IntFor, ImgFor;
		unsigned int Wrap_S, Wrap_T;
		unsigned int FilMin, FilMax;

		Texture2D();

		void Generate(unsigned int w, unsigned int h, unsigned char* d);

		void Bind() const;
};

#endif
