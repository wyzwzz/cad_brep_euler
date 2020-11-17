//
// Created by wyz on 20-11-14.
//

#ifndef EULEROPERATION_RENDERER_H
#define EULEROPERATION_RENDERER_H
#include "shader.h"
#include "controller.h"
#include "b-rep.h"
#include<memory>
#include <vector>
class Renderer {
public:

    Renderer():solid(nullptr){
        InitGL();
    }
    Renderer(const pSolid solid):solid(solid){InitGL();}

    void SetSolid(const pSolid solid){this->solid=solid;}
    void Render();
private:
    void InitGL();
    void RenderWireFrame();
    void RenderSurface();
    void Polygon2Tri(const pFace face);
    struct Triangle{
        glm::vec3 v[3];
    };
    std::vector<Triangle> triangles;
    pSolid solid;
    GLFWwindow *window;
    std::unique_ptr<Shader> shader;

};


#endif //EULEROPERATION_RENDERER_H
