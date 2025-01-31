#include <vector>

const float PI = 3.14159265359f;

unsigned int cubeVAO, cubeEBO,
			 backFaceVAO, backFaceEBO,
			 frontFaceVAO, frontFaceEBO,
			 leftFaceVAO, leftFaceEBO,
			 rightFaceVAO, rightFaceEBO,
			 bottomFaceVAO, bottomFaceEBO,	
			 topFaceVAO, topFaceEBO,
			 xFaceVAO, xFaceEBO,
			 yFaceVAO, yFaceEBO,
			 zFaceVAO, zFaceEBO,
			 sphereVAO, sphereEBO, indexCount;

void renderCube() {
	if (cubeVAO == 0) {
		float verts[] = {
			// Positions             // Normals             // TexCoords
			// Back Face
			 1.0f, -1.0f, -1.0f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,  //
			-1.0f, -1.0f, -1.0f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,  //
			-1.0f,  1.0f, -1.0f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,  // 
			 1.0f,  1.0f, -1.0f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,  //
			// Front Face 
			-1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    0.0f, 0.0f,  // 
			 1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    1.0f, 0.0f,  //
			 1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    1.0f, 1.0f,  //
			-1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    0.0f, 1.0f,  //
			// Left Face
			-1.0f, -1.0f, -1.0f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,  //
			-1.0f, -1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,  //
			-1.0f,  1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,  //
			-1.0f,  1.0f, -1.0f,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,  //
			// Right Face
			 1.0f, -1.0f,  1.0f,     1.0f,  0.0f,  0.0f,    0.0f, 0.0f,  //
			 1.0f, -1.0f, -1.0f,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,  //
			 1.0f,  1.0f, -1.0f,     1.0f,  0.0f,  0.0f,    1.0f, 1.0f,  //
			 1.0f,  1.0f,  1.0f,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,  //
			// Bottom Face
			-1.0f, -1.0f,  1.0f,     0.0f, -1.0f,  0.0f,    0.0f, 0.0f,  //
			-1.0f, -1.0f, -1.0f,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,  // 
			 1.0f, -1.0f, -1.0f,     0.0f, -1.0f,  0.0f,    1.0f, 1.0f,  //
			 1.0f, -1.0f,  1.0f,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,  //
			// Top Face 
			-1.0f,  1.0f,  1.0f,     0.0f,  1.0f,  0.0f,    0.0f, 0.0f,  //
			 1.0f,  1.0f,  1.0f,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,  //
			 1.0f,  1.0f, -1.0f,     0.0f,  1.0f,  0.0f,    1.0f, 1.0f,  //
			-1.0f,  1.0f, -1.0f,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f   //
		};

		unsigned int indices[] = {
			// Back
			0, 1, 2, 0, 2, 3,
			// Front
			4, 5, 6, 4, 6, 7,
			// Left
			8, 9, 10, 8, 10, 11,
			// Right
			12, 13, 14, 12, 14, 15,
			// Bottom
			16, 17, 18, 16, 18, 19,
			// Top
			20, 21, 22, 20, 22, 23
		};

		unsigned int vbo;

		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &cubeEBO);

		if (cubeVAO == 0 || vbo == 0 || cubeEBO == 0)
			std::cout << "Not all buffers and vertex arrays are generated" << std::endl;

		glBindVertexArray(cubeVAO);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
	glBindVertexArray(cubeVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void renderBackFace() {
	if (backFaceVAO == 0) {
		float verts[] = {
			// Positions             // Normals             // TexCoords
			// Back Face
			 1.0f, -1.0f, -1.0f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,  //
			-1.0f, -1.0f, -1.0f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,  //
			-1.0f,  1.0f, -1.0f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,  // 
			 1.0f,  1.0f, -1.0f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f  //
		};

		unsigned int indices[] = {
			// Back
			0, 1, 2, 0, 2, 3
		};

		unsigned int vbo;

		glGenVertexArrays(1, &backFaceVAO);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &backFaceEBO);

		if (backFaceVAO == 0 || vbo == 0 || backFaceEBO == 0)
			std::cout << "Not all buffers and vertex arrays are generated" << std::endl;

		glBindVertexArray(backFaceVAO);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backFaceEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	glDisable(GL_CULL_FACE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backFaceEBO);
	glBindVertexArray(backFaceVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glEnable(GL_CULL_FACE);
	glBindVertexArray(0);
}

void renderFrontFace(bool noCull = true) {
	if (frontFaceVAO == 0) {
		float verts[] = {
			// Positions             // Normals             // TexCoords
			// Front Face 
			-1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    0.0f, 0.0f,  // 
			 1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    1.0f, 0.0f,  //
			 1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    1.0f, 1.0f,  //
			-1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    0.0f, 1.0f,  //
		};

		unsigned int indices[] = {
			0, 1, 2, 0, 2, 3
		};

		unsigned int vbo;

		glGenVertexArrays(1, &frontFaceVAO);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &frontFaceEBO);

		if (frontFaceVAO == 0 || vbo == 0 || frontFaceEBO == 0)
			std::cout << "Not all buffers and vertex arrays are generated" << std::endl;

		glBindVertexArray(frontFaceVAO);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, frontFaceEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	if (noCull)
		glDisable(GL_CULL_FACE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, frontFaceEBO);
	glBindVertexArray(frontFaceVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glEnable(GL_CULL_FACE);
	glBindVertexArray(0);
}

void renderLeftFace(bool noCull = true) {
	if (leftFaceVAO == 0) {
		float verts[] = {
			// Positions             // Normals             // TexCoords
			// Left Face
			-1.0f, -1.0f, -1.0f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,  //
			-1.0f, -1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,  //
			-1.0f,  1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,  //
			-1.0f,  1.0f, -1.0f,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,  //
		};

		unsigned int indices[] = {
			0, 1, 2, 0, 2, 3
		};

		unsigned int vbo;

		glGenVertexArrays(1, &leftFaceVAO);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &leftFaceEBO);

		if (leftFaceVAO == 0 || vbo == 0 || leftFaceEBO == 0)
			std::cout << "Not all buffers and vertex arrays are generated" << std::endl;

		glBindVertexArray(leftFaceVAO);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, leftFaceEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	if (noCull)
		glDisable(GL_CULL_FACE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, leftFaceEBO);
	glBindVertexArray(leftFaceVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glEnable(GL_CULL_FACE);
	glBindVertexArray(0);
}

void renderRightFace(bool noCull = true) {
	if (rightFaceVAO == 0) {
		float verts[] = {
			// Positions             // Normals             // TexCoords
			// Right Face
			 1.0f, -1.0f,  1.0f,     1.0f,  0.0f,  0.0f,    0.0f, 0.0f,  //
			 1.0f, -1.0f, -1.0f,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,  //
			 1.0f,  1.0f, -1.0f,     1.0f,  0.0f,  0.0f,    1.0f, 1.0f,  //
			 1.0f,  1.0f,  1.0f,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,  //
		};

		unsigned int indices[] = {
			0, 1, 2, 0, 2, 3,
		};

		unsigned int vbo;

		glGenVertexArrays(1, &rightFaceVAO);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &rightFaceEBO);

		if (rightFaceVAO == 0 || vbo == 0 || rightFaceEBO == 0)
			std::cout << "Not all buffers and vertex arrays are generated" << std::endl;

		glBindVertexArray(rightFaceVAO);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rightFaceEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	if (noCull)
		glDisable(GL_CULL_FACE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rightFaceEBO);
	glBindVertexArray(rightFaceVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glEnable(GL_CULL_FACE);
	glBindVertexArray(0);
}

void renderBottomFace(bool noCull = true) {
	if (bottomFaceVAO == 0) {
		float verts[] = {
			// Positions             // Normals             // TexCoords
			// Bottom Face
			-1.0f, -1.0f,  1.0f,     0.0f, -1.0f,  0.0f,    0.0f, 0.0f,  //
			-1.0f, -1.0f, -1.0f,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,  // 
			 1.0f, -1.0f, -1.0f,     0.0f, -1.0f,  0.0f,    1.0f, 1.0f,  //
			 1.0f, -1.0f,  1.0f,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,  //
		};

		unsigned int indices[] = {
			0, 1, 2, 0, 2, 3,
		};

		unsigned int vbo;

		glGenVertexArrays(1, &bottomFaceVAO);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &bottomFaceEBO);

		if (bottomFaceVAO == 0 || vbo == 0 || bottomFaceEBO == 0)
			std::cout << "Not all buffers and vertex arrays are generated" << std::endl;

		glBindVertexArray(bottomFaceVAO);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bottomFaceEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	if (noCull)
		glDisable(GL_CULL_FACE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bottomFaceEBO);
	glBindVertexArray(bottomFaceVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glEnable(GL_CULL_FACE);
	glBindVertexArray(0);
}

void renderTopFace(bool noCull = true) {
	if (topFaceVAO == 0) {
		float verts[] = {
			// Positions             // Normals             // TexCoords
			// Top Face 
			-1.0f,  1.0f,  1.0f,     0.0f,  1.0f,  0.0f,    0.0f, 0.0f,  //
			 1.0f,  1.0f,  1.0f,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,  //
			 1.0f,  1.0f, -1.0f,     0.0f,  1.0f,  0.0f,    1.0f, 1.0f,  //
			-1.0f,  1.0f, -1.0f,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f   //
		};

		unsigned int indices[] = {
			0, 1, 2, 0, 2, 3,
		};

		unsigned int vbo;

		glGenVertexArrays(1, &topFaceVAO);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &topFaceEBO);

		if (topFaceVAO == 0 || vbo == 0 || topFaceEBO == 0)
			std::cout << "Not all buffers and vertex arrays are generated" << std::endl;

		glBindVertexArray(topFaceVAO);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, topFaceEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	if (noCull)
		glDisable(GL_CULL_FACE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, topFaceEBO);
	glBindVertexArray(topFaceVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glEnable(GL_CULL_FACE);
	glBindVertexArray(0);
}

void renderXFace(bool noCull = true) {
	if (xFaceVAO == 0) {
		float verts[] = {
			// Positions             // Normals             // TexCoords
			// Right Face
			 0.0f, -1.0f,  1.0f,     1.0f,  0.0f,  0.0f,    0.0f, 0.0f,  //
			 0.0f, -1.0f, -1.0f,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,  //
			 0.0f,  1.0f, -1.0f,     1.0f,  0.0f,  0.0f,    1.0f, 1.0f,  //
			 0.0f,  1.0f,  1.0f,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,  //
		};

		unsigned int indices[] = {
			0, 1, 2, 0, 2, 3,
		};

		unsigned int vbo;

		glGenVertexArrays(1, &xFaceVAO);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &xFaceEBO);

		if (xFaceVAO == 0 || vbo == 0 || xFaceEBO == 0)
			std::cout << "Not all buffers and vertex arrays are generated" << std::endl;

		glBindVertexArray(xFaceVAO);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, xFaceEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	if (noCull)
		glDisable(GL_CULL_FACE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, xFaceEBO);
	glBindVertexArray(xFaceVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glEnable(GL_CULL_FACE);
	glBindVertexArray(0);
}

void renderYFace(bool noCull = true) {
	if (yFaceVAO == 0) {
		float verts[] = {
			// Positions             // Normals             // TexCoords
			// Top Face 
			-1.0f,  0.0f,  1.0f,     0.0f,  1.0f,  0.0f,    0.0f, 0.0f,  //
			 1.0f,  0.0f,  1.0f,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,  //
			 1.0f,  0.0f, -1.0f,     0.0f,  1.0f,  0.0f,    1.0f, 1.0f,  //
			-1.0f,  0.0f, -1.0f,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f   //
		};

		unsigned int indices[] = {
			0, 1, 2, 0, 2, 3,
		};

		unsigned int vbo;

		glGenVertexArrays(1, &yFaceVAO);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &yFaceEBO);

		if (yFaceVAO == 0 || vbo == 0 || yFaceEBO == 0)
			std::cout << "Not all buffers and vertex arrays are generated" << std::endl;

		glBindVertexArray(yFaceVAO);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, yFaceEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	//if (noCull)
	glDisable(GL_CULL_FACE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, yFaceEBO);
	glBindVertexArray(yFaceVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glEnable(GL_CULL_FACE);
	glBindVertexArray(0);
}

void renderZFace(bool noCull = true) {
	if (zFaceVAO == 0) {
		float verts[] = {
			// Positions             // Normals             // TexCoords
			// Back Face
			 1.0f, -1.0f,  0.0f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,  //
			-1.0f, -1.0f,  0.0f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,  //
			-1.0f,  1.0f,  0.0f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,  // 
			 1.0f,  1.0f,  0.0f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f  //
		};

		unsigned int indices[] = {
			// Back
			0, 1, 2, 0, 2, 3
		};

		unsigned int vbo;

		glGenVertexArrays(1, &zFaceVAO);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &zFaceEBO);

		if (zFaceVAO == 0 || vbo == 0 || zFaceEBO == 0)
			std::cout << "Not all buffers and vertex arrays are generated" << std::endl;

		glBindVertexArray(zFaceVAO);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, zFaceEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	if (noCull)
		glDisable(GL_CULL_FACE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, zFaceEBO);
	glBindVertexArray(zFaceVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glEnable(GL_CULL_FACE);
	glBindVertexArray(0);
}

void renderSphere(unsigned int res=64) {
	if (sphereVAO == 0) {
		glGenVertexArrays(1, &sphereVAO);

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &sphereEBO);

		std::vector<glm::vec3> pos;
		std::vector<glm::vec2> uv;
		std::vector<glm::vec3> norm;
		std::vector<unsigned int> indices;

		const unsigned int X_SEG = res;
		const unsigned int Y_SEG = res;
		
		for (unsigned int x = 0; x <= X_SEG; ++x) {
			for (unsigned int y = 0; y <= Y_SEG; ++y) {
				float xSeg = (float)x / (float)X_SEG;
				float ySeg = (float)y / (float)Y_SEG;
				float xPos = std::cos(xSeg * 2.0f * PI) * std::sin(ySeg * PI);
				float yPos = std::cos(ySeg * PI);
				float zPos = std::sin(xSeg * 2.0f * PI) * std::sin(ySeg * PI);

				pos.push_back(glm::vec3(xPos, yPos, zPos));
				uv.push_back(glm::vec2(xSeg, ySeg));
				norm.push_back(glm::vec3(xPos, yPos, zPos));
			}
		}

		bool oddRow = false;
		for (unsigned int y = 0; y < Y_SEG; ++y) {
			if (!oddRow) {
				for (unsigned int x = 0; x <= X_SEG; ++x) {
					indices.push_back(y * (X_SEG + 1) + x);
					indices.push_back((y + 1) * (X_SEG + 1) + x);
				}
			} else {
				for (int x = X_SEG; x >= 0; --x) {
					indices.push_back((y + 1) * (X_SEG + 1) + x);
					indices.push_back(y * (X_SEG + 1) + x);
				}
			}
			oddRow = !oddRow;
		}
		indexCount = static_cast<unsigned int>(indices.size());

		std::vector<float> data;
		for (unsigned int i = 0; i < pos.size(); ++i) {
			data.push_back(pos[i].x);
			data.push_back(pos[i].y);
			data.push_back(pos[i].z);
			if (norm.size() > 0) {
				data.push_back(norm[i].x);
				data.push_back(norm[i].y);
				data.push_back(norm[i].z);
			}
			if (uv.size() > 0) {
				data.push_back(uv[i].x);
				data.push_back(uv[i].y);
			}
		}

		glBindVertexArray(sphereVAO);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		unsigned int stride = (3+3+2) * sizeof(float);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
	glBindVertexArray(sphereVAO);
	glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
