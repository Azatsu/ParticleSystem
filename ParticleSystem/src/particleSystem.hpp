#ifndef __PRTRCL_SYS_HPP__
#define __PRTRCL_SYS_HPP__

#include <vector>

#include "ParticleData.h"
#include "ParticleEmitter.h"
#include "ParticleUpdater.hpp"

class ParticleSystem
{
public:
	ParticleData particles;
	ParticleData aliveParticles;

	size_t count;

	std::vector<std::shared_ptr<ParticleEmitter>> emitters;
	std::vector<std::shared_ptr<ParticleUpdater>> updaters;

public:
	explicit ParticleSystem(size_t maxCount);
	virtual ~ParticleSystem() { }

	ParticleSystem(const ParticleSystem&) = delete;
	ParticleSystem& operator=(const ParticleSystem&) = delete;

	virtual void Update(double dt);
	virtual void Reset();

	virtual size_t NumAllParticles() const { return particles.count; }
	virtual size_t NumAliveParticles() const { return particles.countAlive; }

	void AddEmitter(std::shared_ptr<ParticleEmitter> em) { emitters.push_back(em); }
	void AddUpdater(std::shared_ptr<ParticleUpdater> up) { updaters.push_back(up); }

	ParticleData* FinalData() { return &particles; }

	static size_t ComputeMemoryUsage(const ParticleSystem& p);
};

#endif