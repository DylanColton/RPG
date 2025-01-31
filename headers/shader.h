#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
	public:
		unsigned int ID;

		Shader() {}

		Shader &Use();

		void Compile(const char* vS, const char* fS, const char* gS=nullptr);

		void setInt		(const char* n, int v, bool use=false);
		void setBool	(const char* n, bool v, bool use=false);
		void setFloat	(const char* n, float v, bool use=false);

		void setVec2	(const char* n, float x, float y, bool use=false);
		void setVec2	(const char* n, const glm::vec2 &v, bool use=false);
		void setVec3	(const char* n, float x, float y, float z, bool use=false);
		void setVec3	(const char* n, const glm::vec3 &v, bool use=false);
		void setVec4	(const char* n, float x, float y, float z, float w, bool use=false);
		void setVec4	(const char* n, const glm::vec4 &v, bool use=false);

		void setMat2	(const char* n, const glm::mat2 &m, bool use=false);
		void setMat3	(const char* n, const glm::mat3 &m, bool use=false);
		void setMat4	(const char* n, const glm::mat4 &m, bool use=false);

	private:
		void checkCompileErrors(unsigned int obj, std::string type);
};

#endif
