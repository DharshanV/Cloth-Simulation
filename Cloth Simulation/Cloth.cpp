#include "Cloth.h"

Cloth::Cloth(float width, float height, int numParticlesWidth, int numParticlesHeight)
{
	this->numParticlesWidth = numParticlesWidth;
	this->numParticlesHeight = numParticlesHeight;
	int size = numParticlesWidth * numParticlesHeight;

	particles.resize(size);
	data.resize(size * (3 + 2));
	indices.resize(6 * (numParticlesWidth - 1)*(numParticlesHeight - 1));

	int vertexPointer = 0;
	int pointer = 0;
	for (int x = 0; x < numParticlesWidth; x++) {
		for (int y = 0; y < numParticlesHeight; y++) {
			//Particle position
			vec3 position;
			position.x = (float)x / ((float)numParticlesWidth - 1) * width;
			position.y = -(float)y / ((float)numParticlesHeight - 1) * height;
			position.z = 0;
			particles[index(x, y)] = position;

			//Texture coods
			data[vertexPointer * 5 + 3] = (float)y / ((float)numParticlesHeight - 1);
			data[vertexPointer * 5 + 4] = (float)x / ((float)numParticlesWidth - 1);
			vertexPointer++;

			//indices
			if (x >= numParticlesWidth - 1 || y >= numParticlesHeight- 1) {
				continue;
			}
			int topLeft = (y*numParticlesWidth) + x;
			int topRight = topLeft + 1;
			int bottomLeft = ((y + 1)*numParticlesHeight) + x;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
}

void Cloth::render()
{
	drawUpdatedPosition();

	VertexArray VAO;
	VertexBuffer VBO(&data[0], 4 * data.size());
	ElementBuffer EBO(&indices[0], 4 * indices.size());

	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	VAO.addBuffer(VBO, layout);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	VBO.unbind();
	VAO.unbind();
}

int Cloth::index(int x, int y)
{
	return y * numParticlesWidth + x;
}

Particle* Cloth::getParticle(int x, int y)
{
	return &particles[index(x, y)];
}

void Cloth::drawUpdatedPosition()
{
	int vertexPointer = 0;
	for (int x = 0; x < numParticlesWidth; x++) {
		for (int y = 0; y < numParticlesHeight; y++) {
			const vec3& position = particles[index(x, y)].getPosition();

			data[vertexPointer * 5 + 0] = position.x;
			data[vertexPointer * 5 + 1] = position.y;
			data[vertexPointer * 5 + 2] = position.z;
			vertexPointer++;
		}
	}
}

Cloth::~Cloth()
{
}