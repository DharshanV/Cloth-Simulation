#pragma once
#include <vector>
#include <iomanip>
#include "Particle.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
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
	void print(Particle* p);
	void addTriangle(vector<float>& data, Particle* p1, Particle* p2, Particle* p3);
	void addSquare(vector<float>& data, Particle* p1, Particle* p2, Particle* p3, Particle* p4);
private:
	vector<float> data;
	vector<Particle> particles;
	int numParticlesWidth;
	int numParticlesHeight;
};

vector<float>& operator += (vector<float>& data, const Particle* particle);

