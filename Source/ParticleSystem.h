#pragma once
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"

struct Particle final{
	Particle();
	float distToCam, xScale, yScale, zScale;
	GLfloat accel, birthLife, life, spd, maxSpd, minSpd;
	Vector3 dir, pos;
};

class ParticleEmitter final{
	friend class GhostScene;
	friend class MotorScene;
	GLuint currAmt, maxAmt, oldest;
	std::vector<Particle*> particlePool;
public:
	ParticleEmitter();
	~ParticleEmitter();
	GLuint GetIndex();
	void InitParticles(), SortParticles(), UpdateParticles(double);
};