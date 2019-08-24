#ifndef GLFW_H
#define GLFW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
class GLFW
{
public:
	GLFW(unsigned int width,unsigned int height, const char* name);
	bool close();
	bool isGood();
	void swapBuffers();
	void getEvents();
	~GLFW();
public:
	void setCursor(int value);
public:
	float getAspectRatio();
	int getInputMode(int mode);
	int getWidth() { return width; };
	int getHeight() { return height; };
	GLFWwindow* getWindow() { return window; };
public:
	void setMouseMovementCallBack(GLFWcursorposfun fun);
	void setScrollCallBack(GLFWscrollfun fun);
	void setResizeCallBack(GLFWframebuffersizefun fun);
private:
	GLFWwindow* window;
	bool good;
	int width;
	int height;
};
#endif // !GLFW_H