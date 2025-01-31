#include <iostream>

#include "texture.h"

Texture2D::Texture2D() : W(0), H(0), IntFor(GL_RGB), ImgFor(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), FilMin(GL_LINEAR), FilMax(GL_LINEAR) {
	glGenTextures(1, &this->ID);
}

void Texture2D::Generate(unsigned int w, unsigned int h, unsigned char* d) {
	this->W = w;
	this->H = h;

	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->IntFor, w, h, 0, this->ImgFor, GL_UNSIGNED_BYTE, d);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->FilMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->FilMax);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const {
	glBindTexture(GL_TEXTURE_2D, this->ID);
}
