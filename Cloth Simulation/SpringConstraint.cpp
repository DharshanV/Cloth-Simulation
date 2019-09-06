#include "SpringConstraint.h"

SpringConstraint::SpringConstraint(Particle * p1, Particle * p2)
{
	this->p1 = p1;
	this->p2 = p2;
	restDistance = glm::length(p2->getPosition() - p1->getPosition());
	connected = true;
}

void SpringConstraint::satisfyConstraint()
{
	if (!connected) return;
	const vec3& P1 = p1->getPosition();
	const vec3& P2 = p2->getPosition();
	vec3 p1_to_p2(P2.x-P1.x,P2.y-P1.y,P2.z-P1.z); 
	float current_distance = vecLength(p1_to_p2);
	vec3 correctionVector = p1_to_p2 * (1 - restDistance / current_distance);
	vec3 correctionVectorHalf = correctionVector * 0.5f;
	p1->offsetPosition(correctionVectorHalf);
	p2->offsetPosition(-correctionVectorHalf);
}

SpringConstraint::~SpringConstraint()
{
}

float SpringConstraint::vecLength(const vec3& v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
