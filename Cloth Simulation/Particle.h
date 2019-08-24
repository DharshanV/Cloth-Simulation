#pragma once
#include <iostream>
#include <glm/glm.hpp>
using namespace std;
using namespace glm;

/*
	Particle repersented by verlet intergration.
*/
class Particle
{
public:
	Particle();
	Particle(const vec3& position);
	const vec3& getPosition()const;
	~Particle();
private:
	vec3 position;
};

