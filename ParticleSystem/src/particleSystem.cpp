#include "particleSystem.hpp"

ParticleSystem::ParticleSystem(size_t maxCount)
{
	count = maxCount;
	particles.Generate(maxCount);
	aliveParticles.Generate(maxCount);

	for (size_t i = 0; i < maxCount; ++i)
		particles.alive[i] = false;
}

void ParticleSystem::Update(double dt)
{
	for (auto& em : emitters)
	{
		em->Emit(dt, &particles);
	}

	for (size_t i = 0; i < count; ++i)
	{
		particles.acc[i] = float4(0.f, 0.f, 0.f, 0.f);
	}

	for (auto& up : updaters)
	{
		up->Update(dt, &particles);
	}

	//ParticleData::copyOnlyAlive(&m_particles, &m_aliveParticles);
}

void ParticleSystem::Reset()
{
	particles.countAlive = 0;
}

size_t ParticleSystem::ComputeMemoryUsage(const ParticleSystem& p)
{
	return 2 * ParticleData::ComputeMemoryUsage(p.particles);
}