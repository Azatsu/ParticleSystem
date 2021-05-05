#include <vector>

#include "glad/glad.h"

#include "camera.hpp"
#include "demo.hpp"

struct FXNoiseProperty
{
    float lacunarity = 2.f;
    float gain = 0.5f;
    float offset = 1.f;
    int octaves = 6;
    float zValue = 0.f;
    float scrollSpeed = 0.f;
    bool animate = false;
};

struct Particule
{
    float initDTime = 0.f;
    float horOffset = 0.f;
    float vertOffset = 0.f;
};


class DemoFX : public Demo
{
public:
    DemoFX(const DemoInputs& inputs);
    ~DemoFX() override;

    void UpdateAndRender(const DemoInputs& inputs) override;
    const char* Name() const override { return "Noise"; }
    std::vector<Particule> particules;
private:
    GLuint vertexBuffer = 0;
    GLuint vertexArrayObject = 0;
    GLuint program = 0;
    GLuint texture = 0;
    GLuint mask = 0;

    FXNoiseProperty noiseProps = {};

    Camera mainCamera = {};
};


