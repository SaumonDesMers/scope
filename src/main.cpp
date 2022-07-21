#include <iostream>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include "shader.hpp"
#include "polygon.hpp"

using namespace std;

int gl_init() {

    // Initialise GLFW
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return 1;
    }

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Scope", NULL, NULL);
	if (window == NULL) {
        cout << "Failed to create window" << endl;
		// getchar();
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	GLenum res = glewInit();
	if (res != GLEW_OK && res != GLEW_ERROR_NO_GLX_DISPLAY) { // ignore error GLEW_ERROR_NO_GLX_DISPLAY
		cout << "Failed to initialize GLEW" << endl;
		// getchar();
		glfwTerminate();
		return 1;
	}
	return 0;
}

int main() {

	if (gl_init())
		return 1;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0, 0, 0.4, 0);

	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint shaderID = LoadShaders("shader/simpleShader.vertexshader", "shader/simpleShader.fragmentshader");

	Polygon poly1(
		{-1, -1, 0,
		1, -1, 0,
		0, 1, 0},

		{1, 0, 0,
		0, 1, 0,
		0, 0, 1}
	);

	do {
		glClear(GL_COLOR_BUFFER_BIT);

		poly1.draw(shaderID);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(shaderID);

	glfwTerminate();

	return 0;
}