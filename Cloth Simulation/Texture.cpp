#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "..\stb_image.h"

ShaderTexture::ShaderTexture(const char* path,bool flip)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	stbi_set_flip_vertically_on_load(flip);
	unsigned char* data = stbi_load(path, &image.width, &image.height,
									&image.nChannels, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data != NULL) {
		GLenum format = getImageFormat(image);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0,
			format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
}

void ShaderTexture::bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void ShaderTexture::unbind()
{
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

ShaderTexture::~ShaderTexture()
{
	cout << "DELETED TEXTURE" << endl;
	glDeleteTextures(1, &textureID);
}

GLenum ShaderTexture::getImageFormat(const Image& image)
{
	switch (image.nChannels)
	{
	case 3: return GL_RGB;
	case 4: return GL_RGBA;
	default:
		break;
	}
	return GLenum();
}