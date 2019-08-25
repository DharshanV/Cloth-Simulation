#pragma once
#include <iostream>
#include <glm/glm.hpp>
using namespace std;
using namespace glm;
#define DAMPING 0.01f
#define TIME_STEPSIZE 0.5f*0.5f
#define CONSTRAINT_ITERATIONS 15
/*
	Particle repersented by verlet intergration.
*/
class Particle
{
public:
	Particle();
	Particle(const vec3& position);
	void timeStep();
	void addForce(const vec3& force);
	void setMoveable(bool value = true);
	const vec3& getPosition()const;
	~Particle();
private:
	bool moveable;
	float mass;
	vec3 oldPosition;
	vec3 position;
	vec3 normal;
	vec3 acceleration;
};

