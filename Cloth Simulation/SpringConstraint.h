#pragma once
#include "Particle.h"

class SpringConstraint
{
public:
	SpringConstraint(Particle* p1,Particle* p2);
	void satisfyConstraint();
	~SpringConstraint();
private:
	float restDistance;
	Particle* p1;
	Particle* p2;
};

