#pragma once
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"

class Particle final{
public:
	Particle(): color(Color(1.f, 1.f, 1.f)), life(0.f), dir(Vector3(0.f, 0.f, 0.f)), pos(Vector3(0.f, 0.f, 0.f)){}
	Color color;
	GLfloat life;
	Vector3 dir, pos;
};

class ParticleEmitter final{
public:
	ParticleEmitter(): currAmt(0), maxAmt(30), oldest(0){}
	~ParticleEmitter(){
		for(Particle* p: particlePool){
			if(p != 0){
				delete p;
			}
		}
	}
	GLuint currAmt, maxAmt, oldest;
	std::vector<Particle*> particlePool;
	GLuint GetIndex();
	void InitParticles(), UpdateParticles(double);
};