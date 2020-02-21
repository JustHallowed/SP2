#pragma once
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"

struct Particle final{
	Particle();
	Color color;
	GLfloat life;
	Vector3 dir, pos;
};

class ParticleEmitter final{
	friend class MotorScene;
	GLuint currAmt, maxAmt, oldest;
	std::vector<Particle*> particlePool;
public:
	ParticleEmitter();
	~ParticleEmitter();
	GLuint GetIndex();
	void InitParticles(), UpdateParticles(double);
};