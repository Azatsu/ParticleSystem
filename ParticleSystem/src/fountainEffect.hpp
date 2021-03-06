#ifndef __FNTN_FX_HPP__
#define __FNTN_FX_HPP__

#include "effect.hpp"
#include <memory>
#include "particleData.hpp"
#include "particleGenerator.hpp"
#include "particleRenderer.hpp"
#include "particleUpdater.hpp"
#include "particleSystem.hpp"


class FountainEffect : public IEffect
{
private:
	std::shared_ptr<IParticleRenderer> renderer;
	std::shared_ptr<ParticleSystem>    system;
	std::shared_ptr<BasicColorGen>     colGenerator;
	std::shared_ptr<EulerUpdater>      eulerUpdater;
	std::shared_ptr<FloorUpdater>      floorUpdater;
	std::shared_ptr<BoxPosGen>         posGenerator;
public:
	FountainEffect() { }
	~FountainEffect() { }

	bool Initialize(size_t numParticles) override;
	bool InitializeRenderer() override;
	void Reset() override { system->Reset(); }
	void Clean() override;
	void ShowUI() override;

	void Update(double dt) override;
	void CpuUpdate(double dt) override;
	void GpuUpdate(double dt) override;
	void Render() override;

	int NumAllParticles() override { return system->NumAllParticles(); }
	int NumAliveParticles() override { return system->NumAliveParticles(); }
};

#endif