#include "GLFW.h"

GLFW::GLFW(unsigned int width, unsigned int height,const char* name) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	good = true;

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		good = false;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		good = false;
	}
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	this->width = width;
	this->height = height;
}

bool GLFW::close()
{
	return glfwWindowShouldClose(window);
}

bool GLFW::isGood()
{
	return good;
}

void GLFW::swapBuffers()
{
	glfwSwapBuffers(window);
}

void GLFW::getEvents()
{
	glfwPollEvents();
}

float GLFW::getAspectRatio()
{
	glfwGetWindowSize(window, &width, &height);
	return (float)width/(float)height;
}

int GLFW::getInputMode(int mode)
{
	return glfwGetInputMode(window,mode);
}

void GLFW::setMouseMovementCallBack(GLFWcursorposfun fun)
{
	glfwSetCursorPosCallback(window, fun);
}

GLFW::~GLFW() {
	cout << "GLFW TERMINATED" << endl;
	glfwTerminate();
}

void GLFW::setScrollCallBack(GLFWscrollfun fun)
{
	glfwSetScrollCallback(window, fun);
}

void GLFW::setResizeCallBack(GLFWframebuffersizefun fun)
{
	glfwSetFramebufferSizeCallback(window, fun);
}

void GLFW::setCursor(int value)
{
	glfwSetInputMode(window, GLFW_CURSOR, value);
}