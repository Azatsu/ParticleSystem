#include "particleGenerator.hpp"
#include <random>

#define M_PI 3.14159265358979323846

float LinearRand(float min, float max)
{
	return ((rand() % 100) / 100.f) * (max - min) + min;
}


void BoxPosGen::Generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	float4 posMin{ pos.x - maxStartPosOffset.x, pos.y - maxStartPosOffset.y, pos.z - maxStartPosOffset.z, 1.0 };
	float4 posMax{ pos.x + maxStartPosOffset.x, pos.y + maxStartPosOffset.y, pos.z + maxStartPosOffset.z, 1.0 };

	for (size_t i = startId; i < endId; ++i)
	{
		p->pos[i].x = LinearRand(posMin.x, posMax.x);
		p->pos[i].y = LinearRand(posMin.y, posMax.y);
		p->pos[i].z = LinearRand(posMin.z, posMax.z);
		p->pos[i].w = LinearRand(posMin.w, posMax.w);
	}
}

void CirclePosGen::Generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; ++i)
	{
		double ang = LinearRand(0.0, M_PI * 2.0);
		p->pos[i].x = center.x + radX * sin(ang);
		p->pos[i].y = center.y + radY * cos(ang);
		p->pos[i].z = center.z + 0.0;
		p->pos[i].w = center.w + 1.0;
	}
}

void BasicColorGen::Generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; ++i)
	{
		p->startCol[i].x = LinearRand(minStartCol.x, maxStartCol.x);
		p->startCol[i].y = LinearRand(minStartCol.y, maxStartCol.y);
		p->startCol[i].z = LinearRand(minStartCol.z, maxStartCol.z);
		p->startCol[i].w = LinearRand(minStartCol.w, maxStartCol.w);

		p->endCol[i].x = LinearRand(minEndCol.x, maxEndCol.x);
		p->endCol[i].y = LinearRand(minEndCol.y, maxEndCol.y);
		p->endCol[i].z = LinearRand(minEndCol.z, maxEndCol.z);
		p->endCol[i].w = LinearRand(minEndCol.w, maxEndCol.w);
	}
}

void BasicVelGen::Generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; ++i)
	{
		p->vel[i].x = LinearRand(minStartVel.x, maxStartVel.x);
		p->vel[i].y = LinearRand(minStartVel.y, maxStartVel.y);
		p->vel[i].z = LinearRand(minStartVel.z, maxStartVel.z);
		p->vel[i].w = LinearRand(minStartVel.w, maxStartVel.w);
	}
}

void SphereVelGen::Generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	float phi, theta, v, r;
	for (size_t i = startId; i < endId; ++i)
	{
		phi   = LinearRand(-M_PI, M_PI);
		theta = LinearRand(-M_PI, M_PI);
		v     = LinearRand(minVel, maxVel);

		r = v * sinf(phi);
		p->vel[i].z = v * cosf(phi);
		p->vel[i].x = r * cosf(theta);
		p->vel[i].y = r * sinf(theta);
	}
}

void VelFromPosGen::Generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; ++i)
	{
		float scale = static_cast<float>(LinearRand(minScale, maxScale));
		p->vel[i].x = scale * (p->pos[i].x - offset.x);
		p->vel[i].y = scale * (p->pos[i].y - offset.y);
		p->vel[i].z = scale * (p->pos[i].z - offset.z);
		p->vel[i].w = scale * (p->pos[i].w - offset.w);
	}
}

void BasicTimeGen::Generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; ++i)
	{
		p->time[i].x = p->time[i].y = LinearRand(minTime, maxTime);
		p->time[i].z = 0.f;
		p->time[i].w = 1.f / p->time[i].x;
	}
}