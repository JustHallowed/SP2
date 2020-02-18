#include "ParticleSystem.h"

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
				p.color = Color(p.color.R - .05f, p.color.G, p.color.B + .05f);
			}
			p.pos += p.dir * float(dt) * 25.f;
		} else if(p.life > 0 && p.life - float(dt) <= 0.f){ //If just died...
			--currAmt;
		}
		p.life -= float(dt);
	}
}