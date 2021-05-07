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