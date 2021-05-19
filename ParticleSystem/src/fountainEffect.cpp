#include "fountainEffect.hpp"
#include "imgui.h"

#include <cmath>
#include <iostream>

bool FountainEffect::Initialize(size_t numParticles)
{
	//
	// particles
	//
	const size_t NUM_PARTICLES = numParticles == 0 ? 10000 : numParticles;
	system = std::make_shared<ParticleSystem>(NUM_PARTICLES);

	//
	// emitter:
	//
	auto particleEmitter = std::make_shared<ParticleEmitter>();
	particleEmitter->emitRate = (float)NUM_PARTICLES * 0.25f;

	// pos:
	posGenerator = std::make_shared<BoxPosGen>();
	posGenerator->pos = float4{ 0.0f, 0.0f, 0.0f, 0.0f };
	posGenerator->maxStartPosOffset = float4{ 0.0f, 0.0f, 0.0f, 0.0f};
	particleEmitter->AddGenerator(posGenerator);

	colGenerator = std::make_shared<BasicColorGen>();
	colGenerator->minStartCol = float4{ 0.7, 0.7, 0.7, 1.0 };
	colGenerator->maxStartCol = float4{ 1.0, 1.0, 1.0, 1.0 };
	colGenerator->minEndCol   = float4{ 0.5, 0.0, 0.6, 0.0 };
	colGenerator->maxEndCol   = float4{ 0.7, 0.5, 1.0, 0.0 };
	particleEmitter->AddGenerator(colGenerator);

	auto velGenerator = std::make_shared<BasicVelGen>();
	velGenerator->minStartVel = float4{ -0.05f, 0.22f, -0.05f, 0.0f };
	velGenerator->maxStartVel = float4{ 0.05f, 0.25f, 0.05f, 0.0f };
	particleEmitter->AddGenerator(velGenerator);

	auto timeGenerator = std::make_shared<BasicTimeGen>();
	timeGenerator->minTime = 3.0f;
	timeGenerator->maxTime = 4.0f;
	particleEmitter->AddGenerator(timeGenerator);
	system->AddEmitter(particleEmitter);

	auto timeUpdater = std::make_shared<BasicTimeUpdater>();
	system->AddUpdater(timeUpdater);

	auto colorUpdater = std::make_shared<BasicColorUpdater>();
	system->AddUpdater(colorUpdater);

	eulerUpdater = std::make_shared<EulerUpdater>();
	eulerUpdater->globalAcceleration = float4{ 0.0, -15.0, 0.0, 0.0 };
	system->AddUpdater(eulerUpdater);

	floorUpdater = std::make_shared<FloorUpdater>();
	system->AddUpdater(floorUpdater);


	

	return true;
}

bool FountainEffect::InitializeRenderer()
{
	renderer = RendererFactory::Create("gl");
	renderer->Generate(system.get(), false);

	return true;
}

void FountainEffect::Clean()
{
	if (renderer) renderer->Destroy();
}

void FountainEffect::ShowUI()
{
	if (posGenerator == nullptr)
		std::cout << "imp2" << std::endl;

	//if (posGenerator == nullptr)
	//	std::cout << "imp" << std::endl;
	/*if (system->emitters != nullptr)
	{
		std::cout << "oui" << std::endl;
		float minStartCol[4] = { colGenerator->minStartCol.x, colGenerator->minStartCol.y, colGenerator->minStartCol.z, colGenerator->minStartCol.w };
		ImGui::ColorEdit4("minStartColor", minStartCol);
		colGenerator->minStartCol = { minStartCol[0], minStartCol[1], minStartCol[2], minStartCol[3] };
	}*/
	//ImGui::ColorEdit4("maxStartColor", &colGenerator->maxStartCol.x);

	//ImGui::ColorEdit4("minEndColor", &colGenerator->minEndCol.x);
	//ImGui::ColorEdit4("maxEndColor", &colGenerator->maxEndCol.x);
	
	/*
	ui::AddTweakColor4f("start col min", &m_colGenerator->m_minStartCol.x, "group=effect");
	ui::AddTweakColor4f("start col max", &m_colGenerator->m_maxStartCol.x, "group=effect");
	ui::AddTweakColor4f("end col min", &m_colGenerator->m_minEndCol.x, "group=effect");
	ui::AddTweakColor4f("end col max", &m_colGenerator->m_maxEndCol.x, "group=effect");
	ui::AddTweak("gravity", &m_eulerUpdater->m_globalAcceleration.y, "group=effect min=-20 max=0 step=0.05");
	ui::AddTweak("bounce", &m_floorUpdater->m_bounceFactor, "group=effect min=0 max=1 step=0.05");
	*/
}

void FountainEffect::Update(double dt)
{
	

	static double time = 0.0;
	time += dt;

	posGenerator->pos.x = 0.1f * sin((float)time * 2.5f);
	posGenerator->pos.z = 0.1f * cos((float)time * 2.5f);
}

void FountainEffect::CpuUpdate(double dt)
{
	system->Update(dt);
}

void FountainEffect::GpuUpdate(double dt)
{
	renderer->Update();
}

void FountainEffect::Render()
{
	renderer->Render();
}