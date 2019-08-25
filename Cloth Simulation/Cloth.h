#pragma once
#include <vector>
#include <iomanip>
#include "Particle.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexBufferLayout.h"
#include "SpringConstraint.h"
class Cloth
{
public:
	Cloth(float width,float height,int numParticlesWidth,int numParticlesHeight);
	void render();
	void timeStep();
	void addForce(const vec3& direction);
	void windForce(const vec3& direction);
	~Cloth();
private:
	int index(int x, int y);
	Particle* getParticle(int x, int y);
	void makeConstraint(Particle *p1, Particle *p2);
	void drawUpdatedPosition();
	vec3 calcTriangleNormal(Particle *p1, Particle *p2, Particle *p3);
	void addWindForcesForTriangle(Particle *p1, Particle *p2, Particle *p3, const vec3 direction);
private:
	vector<float> data;
	vector<unsigned int> indices;
	vector<Particle> particles;
	vector<SpringConstraint> constraints;
	int numParticlesWidth;
	int numParticlesHeight;
};