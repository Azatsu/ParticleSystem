
#include <cstddef>
#include <cstdio>
#include <iostream>

#include <glad/glad.h>
#include <imgui.h>

#include "types.hpp"
#include "calc.hpp"
#include "gl_helpers.hpp"
#include "demo_fx.hpp"

// Vertex format
struct Vertex
{
    float3 position;
    float4 color;
    float2 uv;
};

DemoFX::DemoFX(const DemoInputs& inputs)
{
    mainCamera.position = { 0.f, 0.f, 2.f };

    // Upload vertex buffer
    {
        // In memory
        Vertex vertices[] =
        {
            // Triangle (3 vertices)
            { { 0.5f,-0.5f, 0.f }, { 1.f, 0.f, 0.f, 1.f }, { 0.f, 0.f } },
            { {-0.5f,-0.5f, 0.f }, { 0.f, 1.f, 0.f, 1.f }, { 0.f, 0.f } },
            { { 0.0f, 0.5f, 0.f }, { 0.f, 0.f, 1.f, 1.f }, { 0.f, 0.f } },

            // Quad (6 vertices)
            { { 0.5f,-0.5f, 0.f }, { 1.f, 1.f, 1.f, 1.f }, { 1.f, 0.f } },
            { {-0.5f,-0.5f, 0.f }, { 1.f, 1.f, 1.f, 1.f }, { 0.f, 0.f } },
            { { 0.5f, 0.5f, 0.f }, { 1.f, 1.f, 1.f, 1.f }, { 1.f, 1.f } },

            { { 0.5f, 0.5f, 0.f }, { 1.f, 1.f, 1.f, 1.f }, { 1.f, 1.f } },
            { {-0.5f, 0.5f, 0.f }, { 1.f, 1.f, 1.f, 1.f }, { 0.f, 1.f } },
            { {-0.5f,-0.5f, 0.f }, { 1.f, 1.f, 1.f, 1.f }, { 0.f, 0.f } },
        };

        glGenBuffers(1, &vertexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }

    // Vertex layout
    {
        glGenVertexArrays(1, &vertexArrayObject);
        glBindVertexArray(vertexArrayObject);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, color));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, uv));
    }

    // Create program
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
            vec4 eyePos = view * model * gl_Vertex;
            gl_Position = matProjection * eyePos;

	        outColor = vColor;

            float dist = length(eyePos.xyz);
	        float att = inversesqrt(0.1f*dist);
	        gl_PointSize = 2.0f * att;
        }
        )GLSL",


        // Fragment shader
        R"GLSL(
        in vec4 vColor;

        out vec4 fragColor;

        uniform sampler2D noise;
        uniform sampler2D mask;

        uniform float scroll;    

        

        void main()
        {
            vec4 color1 = vec4(texture(noise,vec2(0, scroll*0.4)).r);
            vec4 color2 = vec4(texture(noise, ( vec2(scroll*0.9, 0))* 0.5).r);
            vec4 color3 = vec4(texture(noise, ( scroll * 0.3) * 2.0).r);
            vec4 color4 = vec4(texture(mask).rgba);

            vec4 newCol = (color1 * color2 * 2 * color3 * 2 * color4);
            //if (newCol.a < 0.1)
            //   discard;
           

            fragColor = newCol;
            
        }




        uniform sampler2D tex;

        in vec4 outColor;

        out vec4 vFragColor;

        void main() 
        {
	        vFragColor = texture(tex, gl_PointCoord) * outColor;
        }
        )GLSL"
    );

    // Create texture
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        gl::UploadImage("media/noise2.png");
        gl::SetTextureDefaultParams(false);
        
        
        glGenTextures(1, &mask);
        glBindTexture(GL_TEXTURE_2D, mask);
        gl::UploadImage("media/freezeMask.png");
        gl::SetTextureDefaultParams(false);


        for (int i = 0; i < 150; i++)
        {
            Particule part;
            part.horOffset = (std::rand() % 250) / 400.f;
            part.vertOffset = (std::rand() % 250) / 400.f;
            part.initDTime = (std::rand() % 1000) / 100.f;
            particules.push_back(part);
        }
    }
}

DemoFX::~DemoFX()
{
    // Delete OpenGL objects
    glDeleteTextures(1, &texture);
    glDeleteTextures(1, &mask);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBuffer);
}

void DemoFX::UpdateAndRender(const DemoInputs& inputs)
{
    mainCamera.UpdateFreeFly(inputs.cameraInputs);

    static float time = 0.f;
    time += 1.f / 60.f;

    static float scroll = 0.f;
    scroll += noiseProps.scrollSpeed / 5000.f;
    {
        bool update = false;
        update |= ImGui::DragFloat("speed", &noiseProps.scrollSpeed);

       
    }

    ImGui::Image((ImTextureID)(size_t)texture, { 256, 256 });

    glViewport(0, 0, (int)inputs.windowSize.x, (int)inputs.windowSize.y);

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glUseProgram(program);

    glUniform1i(glGetUniformLocation(program, "noise"), 0);
    glUniform1i(glGetUniformLocation(program, "mask"), 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mask);

    mat4 projection = mat4Perspective(calc::ToRadians(60.f), inputs.windowSize.x / inputs.windowSize.y, 0.01f, 50.f);
    mat4 view = mainCamera.GetViewMatrix();
    mat4 model = mat4Translate({ calc::Sin(time * 0.0f * calc::TAU) * 0.1f, 0.f, 0.f }) * mat4RotateY(0) * mat4Scale(2.f);

    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, projection.e);
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, view.e);
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, model.e);

    glUniform1f(glGetUniformLocation(program, "scroll"), scroll);

    glBindVertexArray(vertexArrayObject);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glDrawArrays(GL_TRIANGLES, 0, 3); // Draw triangle
    glDrawArrays(GL_TRIANGLES, 3, 6); // Draw quad
    
    {
        for (int i = 1; i <= 1  ; i++)
        {

            model = mat4Translate({ particules[i - 1].horOffset, particules[i - 1].vertOffset, 0.001f * i  }) * mat4Scale(2.f);
            glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, model.e);
            glUniform1f(glGetUniformLocation(program, "scroll"), scroll + particules[i - 1].initDTime);

            glDrawArrays(GL_TRIANGLES, 3, 6); // Draw quad
        }
    }
    
}
