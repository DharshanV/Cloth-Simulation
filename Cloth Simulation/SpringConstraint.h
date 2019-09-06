#pragma once
#include "Particle.h"

class SpringConstraint
{
public:
	SpringConstraint(Particle* p1,Particle* p2);
	void satisfyConstraint();
	~SpringConstraint();
private:
	float vecLength(const vec3& v);
private:
	bool connected;
	float restDistance;
	Particle* p1;
	Particle* p2;
};

