#include "particleRenderer.hpp"
#include "glParticleRenderer.hpp"

#include <string>


std::shared_ptr<IParticleRenderer> RendererFactory::Create(const char* name)
{
	std::string renderer{ name };

	if (renderer == "gl")
		return std::make_shared<GLParticleRenderer>();

	return nullptr;
}
