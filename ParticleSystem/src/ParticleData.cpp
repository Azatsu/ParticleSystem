#include "particleData.hpp"

ParticleData::ParticleData(size_t maxCount)
{
	Generate(maxCount);
}

void ParticleData::Generate(size_t maxSize)
{
	count      = maxSize;
	countAlive = 0;
	pos.reset(new float4[maxSize]);
	col.reset(new float4[maxSize]);
	vel.reset(new float4[maxSize]);
	acc.reset(new float4[maxSize]);
	alive.reset(new bool[maxSize]);
	time.reset(new float4[maxSize]);
	endCol.reset(new float4[maxSize]);
	startCol.reset(new float4[maxSize]);
}

void ParticleData::Kill(size_t ID)
{
	if (countAlive > 0)
	{
		alive[ID] = false;
		countAlive --;
		SwapData(ID, countAlive);
	}
}

void ParticleData::Wake(size_t ID)
{
	if (countAlive < count)
	{
		bool oldState = alive[ID];
		alive[ID] = true;
		SwapData(ID, countAlive);
		countAlive += oldState;
	}
}

void ParticleData::SwapData(size_t a, size_t b)
{
	std::swap(startCol[a], startCol[b]);
	std::swap(endCol[a], endCol[b]);
	std::swap(alive[a], alive[b]);
	std::swap(time[a], time[b]);
	std::swap(vel[a], vel[b]);
	std::swap(acc[a], acc[b]);
	std::swap(col[a], col[b]);
	std::swap(pos[a], pos[b]);
}

