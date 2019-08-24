#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H
#include <glad/glad.h>
#include <iostream>
using namespace std;
class ElementBuffer
{
public:
	ElementBuffer(const unsigned int* data, unsigned int size, GLenum type = GL_STATIC_DRAW);
	void bind() const;
	void unbind() const;

	~ElementBuffer();
private:
	unsigned int bufferID;
};

#endif // !ELEMENT_BUFFER_H
