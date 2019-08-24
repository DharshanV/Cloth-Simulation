#include "Particle.h"

Particle::Particle()
{
}

Particle::Particle(const vec3& position)
{
	this->position = position;
}

const vec3& Particle::getPosition() const
{
	return position;
}

Particle::~Particle()
{
}
