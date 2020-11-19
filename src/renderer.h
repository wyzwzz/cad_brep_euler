//
// Created by wyz on 20-11-14.
//

#ifndef EULEROPERATION_RENDERER_H
#define EULEROPERATION_RENDERER_H
#include "shader.h"
#include "controller.h"
#include "b-rep.h"
#include "creation.h"
#include<memory>
#include <vector>
class Renderer {
public:

    Renderer():solid(nullptr){
        InitGL();
        shader.reset(new Shader("../src/shader/vert_shader.glsl",
                                "../src/shader/frag_shader.glsl"));
    }
    Renderer(const pSolid solid):solid(solid){
        InitGL();
        shader.reset(new Shader("../src/shader/vert_shader.glsl",
                                "../src/shader/frag_shader.glsl"));
    }

    void SetSolid(const pSolid solid){this->solid=solid;}
    void Render();
private:
    void InitGL();
    void RenderWireFrame();
    void RenderSurface();
    void Polygon2Tri(const pFace face);
    void GenerateTris();
    void CreateWireVertexBuffer();
    void CreateSurfaceVertexBuffer();
    uint32 l_vao,l_vbo,l_ebo;
    uint32 s_vao,s_vbo,s_ebo;
    struct Triangle{
        glm::vec3 v[3];
    };
    std::vector<Triangle> triangles;
    pSolid solid;
    GLFWwindow *window;
    std::unique_ptr<Shader> shader;
    const uint32 SCREEN_W=1200;
    const uint32 SCREEN_H=900;
    std::array<float,6> line;
};


#endif //EULEROPERATION_RENDERER_H
