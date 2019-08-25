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

	for (int x = 0; x < numParticlesWidth; x++)
	{
		for (int y = 0; y < numParticlesHeight; y++)
		{
			if (x < numParticlesWidth - 1) makeConstraint(getParticle(x, y), getParticle(x + 1, y));
			if (y < numParticlesHeight - 1) makeConstraint(getParticle(x, y), getParticle(x, y + 1));
			if (x < numParticlesWidth - 1 && y < numParticlesHeight - 1) makeConstraint(getParticle(x, y), getParticle(x + 1, y + 1));
			if (x < numParticlesWidth - 1 && y < numParticlesHeight - 1) makeConstraint(getParticle(x + 1, y), getParticle(x, y + 1));
		}
	}

	for (int x = 0; x < numParticlesWidth; x++)
	{
		for (int y = 0; y < numParticlesHeight; y++)
		{
			if (x < numParticlesWidth - 2) makeConstraint(getParticle(x, y), getParticle(x + 2, y));
			if (y < numParticlesHeight - 2) makeConstraint(getParticle(x, y), getParticle(x, y + 2));
			if (x < numParticlesWidth - 2 && y < numParticlesHeight - 2) makeConstraint(getParticle(x, y), getParticle(x + 2, y + 2));
			if (x < numParticlesWidth - 2 && y < numParticlesHeight - 2) makeConstraint(getParticle(x + 2, y), getParticle(x, y + 2));
		}
	}

	for (int x = 0; x < numParticlesWidth; x++)
	{
		Particle* particle = getParticle(x,0);
		particle->setMoveable(false);
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

void Cloth::makeConstraint(Particle* p1, Particle* p2)
{
	constraints.push_back(SpringConstraint(p1, p2));
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

vec3 Cloth::calcTriangleNormal(Particle* p1, Particle* p2, Particle* p3)
{
	const vec3& v1 = p2->getPosition() - p1->getPosition();
	const vec3& v2 = p3->getPosition() - p1->getPosition();
	return glm::cross(v1, v2);
}

void Cloth::addWindForcesForTriangle(Particle * p1, Particle * p2, Particle * p3, const vec3 direction)
{
	vec3 normal = calcTriangleNormal(p1, p2, p3);
	vec3 d = normalize(normal);
	vec3 force = normal * (dot(d, direction));
	p1->addForce(force);
	p2->addForce(force);
	p3->addForce(force);
}

void Cloth::timeStep()
{
	for (int i = 0; i < CONSTRAINT_ITERATIONS; i++)
	{
		for (SpringConstraint& spring : constraints) {
			spring.satisfyConstraint();
		}
	}

	for (Particle& particle : particles) {
		particle.timeStep();
	}
}

void Cloth::addForce(const vec3& direction)
{
	for (Particle& particle : particles) {
		particle.addForce(direction);
	}
}

void Cloth::windForce(const vec3& direction)
{
	for (int x = 0; x < numParticlesWidth - 1; x++)
	{
		for (int y = 0; y < numParticlesHeight - 1; y++)
		{
			addWindForcesForTriangle(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1), direction);
			addWindForcesForTriangle(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1), direction);
		}
	}
}

Cloth::~Cloth()
{
}