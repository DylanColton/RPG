#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "resource_manager.h"
#include "sound_device.h"
//#include "camera2d.h"
#include "game.h"

#include "filesystem.h"

// Function Declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void printMat4(const glm::mat4& mat);

void processInput(GLFWwindow* window);

// Variable Declarations
unsigned int SCR_W = 800, SCR_H = 600;
unsigned int numSam = 1;

float cf, dt = 0;

Game RPG(SCR_W, SCR_H);

int main(int argc, char *argv[]) {
	if (!glfwInit()) {
		std::cout << "GLFW not initialized" << std::endl;
		return -1;
	}
	// Informs glfw of what major version we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// Informs glfw of what minor version we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Informs which OpenGL profile we are using
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef APPLE
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// Tells the window if it is resizeable
	glfwWindowHint(GLFW_RESIZABLE, false);
	// Sets the number of samples to take before displaying the screen
	glfwWindowHint(GLFW_SAMPLES, numSam);
	// Tells GLFW if the buffer should be double
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	
	GLFWwindow* window = glfwCreateWindow(SCR_W, SCR_H, "RPG", NULL, NULL);
	if (window == NULL) {
		std::cout << "FAILED TO CREATED GLFW WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
		glfwTerminate();
		return -1;
	} 
	
	// Turn VSync On or Off (On by default)
	//glfwSwapInterval(0);
	// Force the cursor to the center
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	// OpenGL Config
	glViewport(0, 0, SCR_W, SCR_H);
	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Sound Device
	SoundDevice::getInstance();

	RPG.Init();
	
	float lf = 0;
	while(!glfwWindowShouldClose(window)) {
		lf = cf;
		cf = static_cast<float>(glfwGetTime());
		dt = cf - lf;

		glfwPollEvents();

		// Logic
		RPG.ProcessInput(dt);
		RPG.Update(dt);

		// Rendering
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		RPG.Render();

		//std::cout << (dt > 0 ? (1/dt) : 0) << " FPS" << std::endl;

		glfwSwapBuffers(window);
	}

	RPG.Clear();
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

// Function Definition
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key >= 0 && key < 1024)
		if (action == GLFW_PRESS) {
			RPG.Keys[key] = true;
		} else if (action == GLFW_RELEASE) {
			RPG.Keys[key] = false;
		}
}

void printMat4(const glm::mat4& mat) {
	const float *p = glm::value_ptr(mat);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			std::cout << p[i*4+j] << " ";
		std::cout << std::endl;
	}

	delete p;
}
