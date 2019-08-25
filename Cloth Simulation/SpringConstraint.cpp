#include "SpringConstraint.h"

SpringConstraint::SpringConstraint(Particle * p1, Particle * p2)
{
	this->p1 = p1;
	this->p2 = p2;
	restDistance = glm::length(p2 - p1);
}

void SpringConstraint::satisfyConstraint()
{
	vec3 p1_to_p2 = p2->getPosition() - p1->getPosition(); 
	float current_distance = length(p1_to_p2);
	vec3 correctionVector = p1_to_p2 * (1 - restDistance / current_distance);
	vec3 correctionVectorHalf = correctionVector * 0.5f;
	p1->offsetPosition(correctionVectorHalf);
	p2->offsetPosition(-correctionVectorHalf);
}

SpringConstraint::~SpringConstraint()
{
}
