#include "demo.hpp"
#include <vector>
#include "camera.hpp"
#include "fountainEffect.hpp"
#include "glad/glad.h"

class DemoParticles : public Demo
{
public:
    DemoParticles(const DemoInputs& inputs);
    ~DemoParticles() override;

    void UpdateAndRender(const DemoInputs& inputs) override;
    const char* Name() const override { return "Particle System"; }

    Camera mainCamera = {};

    FountainEffect fountainFX;
    std::shared_ptr<IEffect> effect;

    void Init();
    void UpdateParticles(double dt);
    void RenderScene(const DemoInputs& inputs, double dt);

    GLuint program;
    GLuint tex;

};
