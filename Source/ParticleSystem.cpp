#include "ParticleSystem.h"
#include "Camera.h"

extern Camera camera;

Particle::Particle(): distToCam(0.f), xScale(0.f), yScale(0.f), zScale(0.f), dir(Vector3(0.f, 0.f, 0.f)), pos(Vector3(0.f, 0.f, 0.f)),
accel(0.f), birthLife(0.f), life(0.f), spd(0.f), maxSpd(0.f), minSpd(0.f){} //Particle default ctor def

//ParticleEmitter method defs
ParticleEmitter::ParticleEmitter() : currAmt(0), maxAmt(200), oldest(0){}

ParticleEmitter::~ParticleEmitter(){
	for(Particle* p : particlePool){
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
	if(oldest == maxAmt){
		oldest = 0;
	}
	return oldest++; //Return oldest alive particle to be overridden and set next oldest...
}

void ParticleEmitter::InitParticles(){
	for(GLuint i = 0; i < maxAmt; ++i){ //Add particles to the pool
		particlePool.emplace_back(new Particle);
	}
}

void ParticleEmitter::SortParticles(){
	for(short i = 0; i < particlePool.size() - 1; ++i){
		for(short j = 0; j < particlePool.size() - i - 1; ++j){ //Last i elements are alr sorted 
			if(particlePool[j]->distToCam < particlePool[j + 1]->distToCam){
				Particle* temp = particlePool[j];
				particlePool[j] = particlePool[j + 1];
				particlePool[j + 1] = temp;
			}
		}
	}
}

void ParticleEmitter::UpdateParticles(double dt){
	for(GLuint i = 0; i < maxAmt; ++i){ //Update all particles
		Particle& p = *particlePool[i];
		if(p.life - float(dt) > 0.f){ //If still alive...
			if(p.xScale >= 0.5f){
				p.xScale -= 0.01f;
			}
			p.yScale = p.xScale;
			p.zScale = p.xScale;
			if(p.spd > p.minSpd && p.spd < p.maxSpd){
				p.spd += p.accel;
			}
			p.pos += p.dir * p.spd * float(dt);
			p.distToCam = Vector3(camera.pos.x - p.pos.x, camera.pos.y - p.pos.y, camera.pos.z - p.pos.z).Length();
		} else if(p.life > 0 && p.life - float(dt) <= 0.f){ //If just died...
			--currAmt;
		}
		p.life -= float(dt);
	}
}