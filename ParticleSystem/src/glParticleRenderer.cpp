#include "glParticleRenderer.hpp"
#include "ParticleData.h"
#include "particleSystem.hpp"

#include <assert.h>


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
	
	/*
	if (ogl_ext_ARB_vertex_attrib_binding)
	{
		glBindVertexBuffer(0, bufPos, 0, sizeof(float) * 4);
		glVertexAttribFormat(0, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(0, 0);
	}
	else
*/
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, (4) * sizeof(float), (void*)((0) * sizeof(float)));

	glGenBuffers(1, &bufCol);
	glBindBuffer(GL_ARRAY_BUFFER, bufCol);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * count, nullptr, GL_STREAM_DRAW);
	glEnableVertexAttribArray(1);
	/*
	if (ogl_ext_ARB_vertex_attrib_binding)
	{
		glBindVertexBuffer(1, bufCol, 0, sizeof(float) * 4);
		glVertexAttribFormat(1, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(1, 1);
	}
	else
	*/
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, (4) * sizeof(float), (void*)((0) * sizeof(float)));

	//glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(GLfloat)* 3);
	//glBindVertexBuffer(1, colorBufferHandle, 0, sizeof(GLfloat)* 3);

	//glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	//glVertexAttribBinding(0, 0);
	//glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	//glVertexAttribBinding(1, 1);

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

	const size_t count = system->NumAliveParticles();
	if (count > 0)
		glDrawArrays(GL_POINTS, 0, count);

	glBindVertexArray(0);
}
