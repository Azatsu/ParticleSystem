#ifndef __PRTCL_RNDRR_HPP__
#define __PRTCL_RNDRR_HPP__

#include <memory>

class ParticleSystem;

class IParticleRenderer
{
public:
	IParticleRenderer() { }
	virtual ~IParticleRenderer() { }

	virtual void Generate(ParticleSystem* sys, bool useQuads) = 0;
	virtual void Destroy() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

class RendererFactory
{
public:
	static std::shared_ptr<IParticleRenderer> Create(const char* name);
};


#endif