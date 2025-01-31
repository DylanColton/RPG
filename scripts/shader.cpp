#include "shader.h"

#include <iostream>

Shader &Shader::Use() {
	glUseProgram(this->ID);
	return *this;
}

void Shader::Compile(const char* vS, const char* fS, const char* gS) {
	unsigned int sV, sF, sG;

	// VERTEX
	sV = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sV, 1, &vS, NULL);
	glCompileShader(sV);
	checkCompileErrors(sV, "VERTEX");
	// FRAGMENT
	sF = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sF, 1, &fS, NULL);
	glCompileShader(sF);
	checkCompileErrors(sF, "FRAGMENT");
	// GEOMETRY
	if (gS != nullptr) {
		sG = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(sG, 1, &gS, NULL);
		glCompileShader(sG);
		checkCompileErrors(sG, "GEOMETRY");
	}

	this->ID = glCreateProgram();
	glAttachShader(this->ID, sV);
	glAttachShader(this->ID, sF);
	if (gS != nullptr)
		glAttachShader(this->ID, sG);
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");

	glDeleteShader(sV);
	glDeleteShader(sF);
	if (gS != nullptr)
		glDeleteShader(sG);
}

void Shader::setInt(const char* n, int v, bool use) {
	if (use)
		this->Use();
	glUniform1i(glGetUniformLocation(this->ID, n), v);
}

void Shader::setBool(const char* n, bool v, bool use) {
	if (use)
		this->Use();
	glUniform1i(glGetUniformLocation(this->ID, n), v);
}

void Shader::setFloat(const char* n, float v, bool use) {
	if (use)
		this->Use();
	glUniform1f(glGetUniformLocation(this->ID, n), v);
}

void Shader::setVec2(const char* n, float x, float y, bool use) {
	if (use)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, n), x, y);
}

void Shader::setVec2(const char* n, const glm::vec2 &v, bool use) {
	if (use)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, n), v.x, v.y);
}

void Shader::setVec3(const char* n, float x, float y, float z, bool use) {
	if (use)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, n), x, y, z);
}

void Shader::setVec3(const char* n, const glm::vec3 &v, bool use) {
	if (use)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, n), v.x, v.y, v.z);
}

void Shader::setVec4(const char* n, float x, float y, float z, float w, bool use) {
	if (use)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, n), x, y, z, w);
}

void Shader::setVec4(const char* n, const glm::vec4 &v, bool use) {
	if (use)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, n), v.x, v.y, v.z, v.w);
}

void Shader::setMat2(const char* n, const glm::mat2 &m, bool use) {
	if (use)
		this->Use();
	glUniformMatrix2fv(glGetUniformLocation(this->ID, n), 1, false, glm::value_ptr(m));
}

void Shader::setMat3(const char* n, const glm::mat3 &m, bool use) {
	if (use)
		this->Use();
	glUniformMatrix3fv(glGetUniformLocation(this->ID, n), 1, false, glm::value_ptr(m));
}

void Shader::setMat4(const char* n, const glm::mat4 &m, bool use) {
	if (use)
		this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->ID, n), 1, false, glm::value_ptr(m));
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
	}
}
