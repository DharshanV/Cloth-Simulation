#pragma once
#include <vector>
#include <iomanip>
#include "Particle.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
class Cloth
{
public:
	Cloth(float width,float height,int numParticlesWidth,int numParticlesHeight);
	void render();
	~Cloth();
private:
	int index(int x, int y);
	Particle* getParticle(int x, int y);
	void addTriangle(vector<float>& data, Particle* p1, Particle* p2, Particle* p3);
private:
	vector<Particle> particles;
	int numParticlesWidth;
	int numParticlesHeight;
};

vector<float>& operator += (vector<float>& data, const Particle* particle);

