#pragma once

#include "src/ParticleData.h"

class ParticleGenerator
{
public:
	ParticleGenerator() {};
	virtual ~ParticleGenerator() {};

	virtual void Generate(double dt, ParticleData* p, size_t start, size_t end) = 0;
};

class BoxPosGen : ParticleGenerator
{
public:

	float4 pos;
	float4 maxStartPosOffset;

	BoxPosGen() : pos(0.f, 0.f, 0.f, 0.f), maxStartPosOffset(0.f, 0.f, 0.f, 0.f) {}
	BoxPosGen(const float4& _pos, const float4& _offset) :
		pos(_pos),
		maxStartPosOffset(_offset)
	{};


	virtual void Generate(double dt, ParticleData* p, size_t start, size_t end) override;
};

class CirclePosGen : ParticleGenerator
{
public:
	
	float4 center;
	float radX;
	float radY;

	CirclePosGen() : center(0.f, 0.f, 0.f, 0.f), radX(0.f), radY(0.f) {};
	CirclePosGen(const float4& _center, float _radX, float _radY) :
		center(_center),
		radX(_radX),
		radY(_radY)
	{};

	virtual void Generate(double dt, ParticleData* p, size_t start, size_t end) override;
};

class BasicColorGen : public ParticleGenerator
{
public:
	float4 minStartCol;
	float4 maxStartCol;
	float4 minEndCol;
	float4 maxEndCol;
	
	BasicColorGen() : minStartCol(0.f, 0.f, 0.f, 0.f), maxStartCol(0.f, 0.f, 0.f, 0.f),
		minEndCol(0.f, 0.f, 0.f, 0.f), maxEndCol(0.f, 0.f, 0.f, 0.f)
	{ };

	virtual void Generate(double dt, ParticleData* p, size_t startId, size_t endId) override;
};

class BasicVelGen : public ParticleGenerator
{
public:
	float4 minStartVel;
	float4 maxStartVel;
public:
	BasicVelGen() : minStartVel(0.f, 0.f, 0.f, 0.f), maxStartVel(0.f, 0.f, 0.f, 0.f) { }

	virtual void Generate(double dt, ParticleData* p, size_t startId, size_t endId) override;
};

class SphereVelGen : public ParticleGenerator
{
public:
	float minVel;
	float maxVel;
public:
	SphereVelGen() : minVel(0.0), maxVel(0.0) { }

	virtual void Generate(double dt, ParticleData* p, size_t startId, size_t endId) override;
};

class VelFromPosGen : public ParticleGenerator
{
public:
	float4 offset;
	float minScale;
	float maxScale;
public:
	VelFromPosGen() : offset(0.f, 0.f, 0.f, 0.f), minScale(0.0), maxScale(0.0) { }
	VelFromPosGen(const float4& off, double minS, double maxS)
		: offset(off)
		, minScale((float)minS)
		, maxScale((float)maxS)
	{ }

	virtual void Generate(double dt, ParticleData* p, size_t startId, size_t endId) override;
};

class BasicTimeGen : public ParticleGenerator
{
public:
	float minTime;
	float maxTime;
public:
	BasicTimeGen() : minTime(0.0), maxTime(0.0) { }

	virtual void Generate(double dt, ParticleData* p, size_t startId, size_t endId) override;
};