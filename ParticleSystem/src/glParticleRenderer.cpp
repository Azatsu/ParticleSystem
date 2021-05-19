#include "glParticleRenderer.hpp"
#include "ParticleData.h"
#include "particleSystem.hpp"

#include <assert.h>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"


void GLParticleRenderer::Generate(ParticleSystem* sys, bool)
{
	assert(sys != nullptr);

	system = sys;

	const size_t count = sys->NumAllParticles();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &bufPos);
	glBindBuffer(GL_ARRAY_BUFFER, bufPos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * count, nullptr, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, (4) * sizeof(float), (void*)((0) * sizeof(float)));

	glGenBuffers(1, &bufCol);
	glBindBuffer(GL_ARRAY_BUFFER, bufCol);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * count, nullptr, GL_STREAM_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, (4) * sizeof(float), (void*)((0) * sizeof(float)));


	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLParticleRenderer::Destroy()
{
	if (bufPos != 0)
	{
		glDeleteBuffers(1, &bufPos);
		bufPos = 0;
	}

	if (bufCol != 0)
	{
		glDeleteBuffers(1, &bufCol);
		bufCol = 0;
	}
}

void GLParticleRenderer::Update()
{
	assert(system != nullptr);
	assert(bufPos > 0 && bufCol > 0);

	const size_t count = system->NumAliveParticles();
	if (count > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, bufPos);
		float* ptr = (float*)(system->FinalData()->pos.get());
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, bufCol);
		ptr = (float*)(system->FinalData()->col.get());
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void GLParticleRenderer::Render()
{
	glBindVertexArray(vao);


	std::cout << system->particles.pos.get()->x << std::endl;
	std::cout << system->particles.pos.get()->y << std::endl;
	std::cout << system->particles.pos.get()->z << std::endl;

	const size_t count = system->NumAliveParticles();
	if (count > 0)
		glDrawArrays(GL_POINTS, 0, count);

	glBindVertexArray(0);
}
