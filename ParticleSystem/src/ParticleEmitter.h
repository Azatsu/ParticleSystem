#ifndef __PRTCL_EMIT_HPP__
#define __PRTCL_EMIT_HPP__

#include <vector>
#include <algorithm>

#include "../particleGenerator.hpp"

class ParticleEmitter
{
protected:
	std::vector<std::shared_ptr<ParticleGenerator>> m_generators;
public:
	float emitRate{ 0.0 };
public:
	ParticleEmitter() { }
	virtual ~ParticleEmitter() { }

	virtual void Emit(double dt, ParticleData* p)
	{
		const size_t maxNewParticles = static_cast<size_t>(dt * emitRate);
		const size_t startId = p->countAlive;
		const size_t endId = std::min(startId + maxNewParticles, p->count - 1);

		for (std::shared_ptr<ParticleGenerator>& gen : m_generators)
			gen->Generate(dt, p, startId, endId);

		for (size_t i = startId; i < endId; i++)
			p->Wake(i);
	};

	void AddGenerator(std::shared_ptr<ParticleGenerator> gen) 
	{ 
		m_generators.push_back(gen); 
	}
};

#endif