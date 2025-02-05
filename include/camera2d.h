#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Camera2D {
	public:
		glm::vec3 Pos;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        Camera2D(glm::vec3 pos=glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f))
            : Front(glm::vec3(0.0f, 0.0f, -1.0f)) {
            Pos = pos;
            WorldUp = up;
        }

        Camera2D(float posX, float posY, float posZ, float upX, float upY, float upZ)
            : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MoveSpeed(SPEED) {
            Pos = glm::vec3(posX, posY, posZ);
            WorldUp = glm::vec3(upX, upY, upZ);
        }

        glm::mat4 GetViewMatrix() const {
            return glm::lookAt(Pos, Pos + Front, Up);
        }

        void ProcessKeyboard(Camera_Movement dir, float dt) {
            float vel = MoveSpeed * dt;
        }
};

#endif
