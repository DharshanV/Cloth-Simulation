#include "Particle.h"

Particle::Particle()
{
	moveable = true;
}

Particle::Particle(const vec3& position)
{
	moveable = true;
	this->position = position;
	oldPosition = position;
	acceleration = vec3(0);
	normal = vec3(0);
	mass = 1;
}

void Particle::timeStep()
{
	if (moveable) {
		vec3 temp = position;
		position = position + (position - oldPosition)*(1.0f - DAMPING) + acceleration * TIME_STEPSIZE;
		oldPosition = temp;
		acceleration = vec3(0);
	}
}

void Particle::addForce(const vec3& force)
{
	acceleration += force / mass;
}

void Particle::setMoveable(bool value)
{
	moveable = value;
}

void Particle::offsetPosition(const vec3& offset)
{
	if (moveable) {
		position += offset;
	}
}

const vec3& Particle::getPosition() const
{
	return position;
}

Particle::~Particle()
{
}
