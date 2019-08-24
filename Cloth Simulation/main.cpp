#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

int width = 500;
int height = 500;
float deltaTime = 0.0f;
float lastTime = 0.0f;
float currentTime = 0.0f;

void windowResizeListener(GLFWwindow* window, int width, int height);
void mouseChangeListener(GLFWwindow* window, double mouseX, double mouseY);
void scrollListener(GLFWwindow* window, double xDiff, double yDiff);
void inputListener(GLFWwindow* window);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Window", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(window, windowResizeListener);
	glfwSetCursorPosCallback(window, mouseChangeListener);
	glfwSetScrollCallback(window, scrollListener);

	while (!glfwWindowShouldClose(window))
	{
		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		inputListener(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void windowResizeListener(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void inputListener(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}

void mouseChangeListener(GLFWwindow* window, double mouseX, double mouseY) {
}

void scrollListener(GLFWwindow* window, double xDiff, double yDiff) {
}