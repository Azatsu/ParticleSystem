#ifndef __PRTCL_UPDT_HPP__
#define __PRTCL_UPDT_HPP__

#include <vector>
#include <algorithm>

#include "../ParticleGenerator.h"

class ParticleUpdater
{
public:
	ParticleUpdater() { }
	virtual ~ParticleUpdater() { }

	virtual void Update(float dt, ParticleData* p) = 0;
};

class EulerUpdater : public ParticleUpdater
{
public:
	float4 globalAcceleration;
public:
	EulerUpdater() : globalAcceleration(0.f, 0.f, 0.f, 0.f) { }

	virtual void Update(float dt, ParticleData* p) override;
};

// collision with the floor :) todo: implement a collision model
class FloorUpdater : public ParticleUpdater
{
public:
	float floorY;
	float bounceFactor;
public:
	FloorUpdater() :floorY(0.0), bounceFactor(0.5f) { }

	virtual void Update(float dt, ParticleData* p) override;
};

class AttractorUpdater : public ParticleUpdater
{
protected:
	std::vector<float4> attractors; // .w is force
public:
	virtual void Update(float dt, ParticleData* p) override;

	size_t CollectionSize() const { return attractors.size(); }
	void Add(const float4& attr) { attractors.push_back(attr); }
	float4& Get(size_t id) { return attractors[id]; }
};

class BasicColorUpdater : public ParticleUpdater
{
public:
	virtual void Update(float dt, ParticleData* p) override;
};

class PosColorUpdater : public ParticleUpdater
{
public:
	float4 minPos;
	float4 maxPos;
public:
	PosColorUpdater() : minPos(0.f, 0.f, 0.f, 0.f), maxPos(1.f, 1.f, 1.f, 1.f) { }

	virtual void Update(float dt, ParticleData* p) override;
};

class VelColorUpdater : public ParticleUpdater
{
public:
	float4 minVel;
	float4 maxVel;
public:
	VelColorUpdater() : minVel(0.f, 0.f, 0.f, 0.f), maxVel(1.f, 1.f, 1.f, 1.f) { }

	virtual void Update(float dt, ParticleData* p) override;
};

class BasicTimeUpdater : public ParticleUpdater
{
public:
	virtual void Update(float dt, ParticleData* p) override;
};

#endif