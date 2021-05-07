#ifndef __PARTICLE_DATA_HPP__
#define __PARTICLE_DATA_HPP__

#include <memory>

#include "calc.hpp"



#pragma once
class ParticleData
{
public:
	std::unique_ptr<float4[]>  startCol;
	std::unique_ptr<float4[]>  endCol;
	std::unique_ptr<float4[]>  time;
	std::unique_ptr<float4[]>  pos;
	std::unique_ptr<float4[]>  col;
	std::unique_ptr<float4[]>  vel;
	std::unique_ptr<float4[]>  acc;
	std::unique_ptr<bool[]>    alive;

	size_t count      = 0;
	size_t countAlive = 0;

	explicit ParticleData(size_t maxCount);
	~ParticleData();

	ParticleData(const ParticleData&)            = delete;
	ParticleData& operator=(const ParticleData&) = delete;

	void SwapData(size_t a, size_t b);
	void Generate(size_t maxSize);
	void Kill(size_t ID);
	void Wake(size_t ID);
};

#endif