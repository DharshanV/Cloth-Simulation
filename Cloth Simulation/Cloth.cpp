#include "Cloth.h"

Cloth::Cloth(float width, float height, int numParticlesWidth, int numParticlesHeight)
{
	this->numParticlesWidth = numParticlesWidth;
	this->numParticlesHeight = numParticlesHeight;
	particles.resize(numParticlesWidth*numParticlesHeight);
	for (int x = 0; x < numParticlesWidth; x++) {
		for (int y = 0; y < numParticlesHeight; y++) {
			vec3 particlePosition(0);
			particlePosition.x = width * (x / (float)numParticlesWidth);
			particlePosition.y = -height * (y / (float)numParticlesHeight);
			particlePosition.z = 0;
			particles[index(x,y)] = Particle(particlePosition);
		}
	}

	for (int x = 0; x < numParticlesWidth - 1; x++) {
		for (int y = 0; y < numParticlesHeight - 1; y++) {
			addTriangle(data, getParticle(x, y), getParticle(x + 1, y), getParticle(x, y + 1));
			addTriangle(data, getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1));
		}
	}
}

void Cloth::render()
{
	VertexArray VAO;
	VertexBuffer VBO(&data[0], 4 * data.size());
	VertexBufferLayout layout;
	layout.push<float>(3);
	VAO.addBuffer(VBO, layout);
	glDrawArrays(GL_TRIANGLES,0, data.size() / 3);
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

void Cloth::addTriangle(vector<float>& data, Particle* p1, Particle* p2, Particle* p3)
{
	data += p1;
	data += p2;
	data += p3;
}

void Cloth::addSquare(vector<float>& data, Particle * p1, Particle * p2, Particle * p3, Particle * p4)
{
	data += p1;
	data += p2;
	data += p3;
	data += p4;
}

void Cloth::print(Particle* p) {
	const vec3 position = p->getPosition();
	cout << "("<< position.x << ", " << position.y << "),";
}

Cloth::~Cloth()
{
}

vector<float>& operator+=(vector<float>& data, const Particle* particle)
{
	const vec3 position = particle->getPosition();
	data.push_back(position.x);
	data.push_back(position.y);
	data.push_back(position.z);
	return data;
}
