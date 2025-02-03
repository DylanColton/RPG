#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "sprite_renderer.h"
#include "texture.h"
#include "shader.h"

class PostProcessor {
	public:
		Shader			ppShader;
		Texture2D		tex;
		unsigned int	W, H;
		bool			confuse, chaos, shake;
		// Post Processes:
		// 	- Screen shake
		// 	- Confuse (Instant and fade, fast and slow)
		// 	- Chaos (Instant and fade)

		PostProcessor(Shader shader, unsigned int w, unsigned int h);

		void BeginRender();

		void EndRender();

		void Render(float time);

	private:
		unsigned int msFBO, FBO;
		unsigned int RBO;
		unsigned int VAO;

		void initRenderData();
};

#endif
