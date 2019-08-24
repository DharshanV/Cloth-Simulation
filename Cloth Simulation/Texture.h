#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include <glad/glad.h>

using namespace std;

struct Image
{
	int width;
	int height;
	int nChannels;
};

class ShaderTexture
{
public:
	ShaderTexture(const char* path,bool flip = false);
	void bind(unsigned int slot = 0);
	void unbind();
	int getChannelCount() { return image.nChannels; };
	~ShaderTexture();
private:
	GLenum getImageFormat(const Image& image);
private:
	unsigned int textureID;
	Image image;
};
#endif // !TEXTURE_H