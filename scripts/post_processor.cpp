#include <iostream>

#include "post_processor.h"

PostProcessor::PostProcessor(Shader shader, unsigned int w, unsigned int h) : ppShader(shader), tex(), W(w), H(h), confuse(false), chaos(false), shake(false) {
	glGenFramebuffers(1, &this->msFBO);
	glGenFramebuffers(1, &this->FBO);
	glGenRenderbuffers(1, &this->RBO);

	glBindFramebuffer(GL_FRAMEBUFFER, this->msFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, w, h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->RBO);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::POSTPROCESSOR: Failed to initialize the Multisample Framebuffer Object" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
	this->tex.Generate(w, h, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->tex.ID, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::POSTPROCESSOR: Failed to initialize the Framebuffer Object" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	this->initRenderData();
	this->ppShader.setInt("scene", 0, true);
	float offset = 1.0f / 300.0f;
	float offsets[9][2] = {
		{ -offset,	 offset	},
		{  0.0f,	 offset	},
		{  offset,	 offset	},
		{ -offset,	 0.0f	},
		{  0.0f,	 0.0f	},
		{  offset,	 0.0f	},
		{ -offset,	-offset	},
		{  0.0f,	-offset	},
		{  offset,	-offset	}
	};
	glUniform2fv(glGetUniformLocation(this->ppShader.ID, "offsets"), 9, (float*)offsets);
	int edge_kernel[9] = {
		-1, -1, -1,
		-1,  8, -1,
		-1, -1, -1
	};
	glUniform1iv(glGetUniformLocation(this->ppShader.ID, "edge_kernel"), 9, edge_kernel);
	float blur_kernel[9] = {
		1.0f / 16.0f,	2.0f / 16.0f,	1.0f / 16.0f,
		2.0f / 16.0f,	4.0f / 16.0f,	2.0f / 16.0f,
		1.0f / 16.0f,	2.0f / 16.0f,	1.0f / 16.0f
	};
	glUniform1fv(glGetUniformLocation(this->ppShader.ID, "blur_kernel"), 9, blur_kernel);
}

void PostProcessor::BeginRender() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->msFBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void PostProcessor::EndRender() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->msFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->FBO);
	glBlitFramebuffer(0, 0, this->W, this->H, 0, 0, this->W, this->H, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::Render(float time) {
	this->ppShader.Use();
	this->ppShader.setFloat("time", time);
	this->ppShader.setBool("confuse", this->confuse);
	this->ppShader.setBool("chaos", this->chaos);
	this->ppShader.setBool("shake", this->shake);

	glActiveTexture(GL_TEXTURE0);
	this->tex.Bind();
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void PostProcessor::initRenderData() {
	unsigned int VBO;
	float verts[] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
	};
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
