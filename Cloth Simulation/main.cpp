#include <iostream>
#include "Shader.h"
#include "Texture.h"
#include "GLFW.h"
#include "Camera.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Cloth.h"

void processInput(GLFWwindow *window);
void mouseCallBack(GLFWwindow* window, double xpos, double ypos);
void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
void resizeCallBack(GLFWwindow* window, int width, int height);

int screenWidth = 800;
int screenHeight = 600;

GLFW window(screenWidth, screenHeight, "Cloth Simulation");
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = screenWidth / 2.0f;
float lastY = screenHeight / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	if (!window.isGood()) { glfwTerminate(); return -1; }

	window.setResizeCallBack(resizeCallBack);
	window.setScrollCallBack(scrollCallBack);
	window.setMouseMovementCallBack(mouseCallBack);
	window.setCursor(GLFW_CURSOR_DISABLED);

	Shader clothShader("Shader\\shader.vert", "Shader\\shader.frag");
	ShaderTexture boxTexture("Texture\\cloth.jpg");
	Cloth cloth(10, 5, 20,20);

	clothShader.use();
	clothShader.setInt("boxShader", 0);

	while (!window.close())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window.getWindow());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 model(1.0f);
		mat4 view(camera.GetViewMatrix());
		mat4 projection = glm::perspective(45.0f, (float)screenWidth / screenHeight, .1f, 100.0f);

		clothShader.use();
		boxTexture.bind(0);
		clothShader.setMat4f("model", value_ptr(model));
		clothShader.setMat4f("view", value_ptr(view));
		clothShader.setMat4f("projection", value_ptr(projection));
		cloth.addForce(vec3(0, -0.2, 0)*.05f);
		cloth.windForce(vec3(0.5, .6, 0.2)*.05f);
		cloth.timeStep();
		cloth.render();

		window.swapBuffers();
		window.getEvents();
	}
	return 0;
}

void resizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	screenWidth = width;
	screenHeight = height;
}

void processInput(GLFWwindow* glfwwindow)
{
	if (glfwGetKey(glfwwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(glfwwindow, true);
	if (glfwGetKey(glfwwindow, GLFW_KEY_0) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(glfwwindow, GLFW_KEY_9) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(glfwwindow, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(glfwwindow, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(glfwwindow, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(glfwwindow, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(glfwwindow, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(glfwwindow, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
}

void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

void mouseCallBack(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}