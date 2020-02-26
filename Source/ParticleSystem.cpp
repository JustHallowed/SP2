#include "ParticleSystem.h"

Particle::Particle(): color(Color(1.f, 1.f, 1.f)), life(0.f), dir(Vector3(0.f, 0.f, 0.f)), pos(Vector3(0.f, 0.f, 0.f)){} //Particle default ctor def

//ParticleEmitter method defs
ParticleEmitter::ParticleEmitter(): currAmt(0), maxAmt(30), oldest(0){}

ParticleEmitter::~ParticleEmitter(){
	for(Particle* p: particlePool){
		if(p != 0){
			delete p;
		}
	}
}

GLuint ParticleEmitter::GetIndex(){
	for(GLuint i = 0; i < maxAmt; ++i){ //Linear search for dead particles
		if(particlePool[i]->life <= 0.0f){
			return i;
		}
	}
	return oldest++; //Return oldest alive particle to be overridden and set next oldest...
}

void ParticleEmitter::InitParticles(){
	for(GLuint i = 0; i < maxAmt; ++i){ //Add particles to the pool
		particlePool.emplace_back(new Particle);
	}
}

void ParticleEmitter::UpdateParticles(double dt){
	for(GLuint i = 0; i < maxAmt; ++i){ //Update all particles
		Particle& p = *particlePool[i];
		if(p.life - float(dt) > 0.f){ //If still alive...
			if(p.color.R - .1f >= 0.f){
				p.color = Color(p.color.R - .02f, p.color.G, p.color.B + .02f);
			}
			p.pos += p.dir * float(dt) * 25.f;
		} else if(p.life > 0 && p.life - float(dt) <= 0.f){ //If just died...
			--currAmt;
		}
		p.life -= float(dt);
	}
}