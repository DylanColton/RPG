#ifndef DEBUG_H
#define DEBUG_H

#include <AL/al.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Debug {
	public:
		static bool checkALErrors(const std::string& msg) {
			ALenum error = alGetError();
			if (error != AL_NO_ERROR) {
				std::cerr << "OpenAL Error (" << msg << "): " << error << std::endl;
				return false;
			}
			return true;
		}

		static void checkGLErrors() {
			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << err << std::endl;
		}
};

#endif
