#include "demo_particles.hpp"
#include "gl_helpers.hpp"

DemoParticles::DemoParticles(const DemoInputs& inputs)
{
    mainCamera.position = { 0.f, 0.f, 2.f };


    program = gl::CreateBasicProgram(
        // Vertex shader
        R"GLSL(
        uniform mat4 projection;
        uniform mat4 view;
        uniform mat4 model;

        layout(location = 0) in vec4 vVertex;
        layout(location = 1) in vec4 vColor;

        out vec4 outColor;

        void main() 
        {
            vec4 eyePos = view * model;
            gl_Position = projection * eyePos;

	        outColor = vColor;

            float dist = length(eyePos.xyz);
	        float att = inversesqrt(0.1f*dist);
	        gl_PointSize = 2.0f * att;
        }
        )GLSL",

        // Fragment shader
        R"GLSL(
        //uniform sampler2D tex;

        in vec4 outColor;

        out vec4 vFragColor;

        void main() 
        {
	       // vFragColor = texture(tex, gl_PointCoord) * outColor;
            vFragColor = outColor;
        }
        )GLSL"
    );

    Init();

}

DemoParticles::~DemoParticles()
{}

void DemoParticles::UpdateAndRender(const DemoInputs& inputs)
{
    mainCamera.UpdateFreeFly(inputs.cameraInputs);

    static float time = 0.f;
    time += 1.f / 60.f;

    UpdateParticles(1.f / 60.f);
    RenderScene(inputs, 1.f / 60.f);
}

void DemoParticles::Init()
{
    effect = EffectFactory::Create("fountain");
    effect->Initialize(1000);
    effect->InitializeRenderer();
}

void DemoParticles::UpdateParticles(double dt)
{
    effect->Update(dt);
    effect->CpuUpdate(dt);
    effect->GpuUpdate(dt);
}

void DemoParticles::RenderScene(const DemoInputs& inputs, double dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);


    glUseProgram(program);

    mat4 projection = mat4Perspective(calc::ToRadians(60.f), inputs.windowSize.x / inputs.windowSize.y, 0.01f, 50.f);
    mat4 view = mainCamera.GetViewMatrix();
    mat4 model = mat4Translate({ 0.f, 0.f, 0.f }) * mat4RotateY(0) * mat4Scale(2.f);

    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, projection.e);
    glUniformMatrix4fv(glGetUniformLocation(program, "view")      , 1, GL_FALSE, view.e);
    glUniformMatrix4fv(glGetUniformLocation(program, "model")     , 1, GL_FALSE, model.e);


    effect->Render();

}

