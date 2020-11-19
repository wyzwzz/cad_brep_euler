//
// Created by wyz on 20-11-14.
//

#include "renderer.h"
#include "poly2tri.h"


class Plane2D{
public:
    glm::vec3 o;
    glm::vec3 x;
    glm::vec3 y;
    glm::vec3 z;
    Plane2D(pFace face);
    auto Space3DToPlane2D(const glm::vec3&)->glm::vec2;
    auto Plane2DToSpace3D(const glm::vec2&)->glm::vec3;
};
inline Plane2D::Plane2D(pFace face)
{
    auto he=face->f_loop->l_halfedge;
    auto head=he;
    auto v1=he->start_v->point->GetPoint();he=he->next_he;
    auto v2=he->start_v->point->GetPoint();he=he->next_he;
    this->o=v1;
    this->x=glm::normalize(v2-v1);
    while(he!=head){
        auto v3=he->start_v->point->GetPoint();
        if(glm::length(glm::cross(v3-v1,v3-v2))>0.01f){
            this->z=glm::normalize(glm::cross(x,v3-v2));
            this->y=glm::normalize(glm::cross(z,x));
            break;
        }
    }
}
inline glm::vec2 Plane2D::Space3DToPlane2D(const glm::vec3& p)
{
    if(glm::dot(p-o,z)>0.01f)
        std::cout<<"ERROR! p is not on the plane! "<<glm::dot(p-o,z)<<std::endl;
    auto vec=p-o;
    return glm::vec2(glm::dot(vec,x),glm::dot(vec,y));
}
inline glm::vec3 Plane2D::Plane2DToSpace3D(const glm::vec2& p)
{
    return o+p.x*x+p.y*y;
}

void Renderer::InitGL()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(SCREEN_W, SCREEN_H, "Euler Operation", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return ;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,Controller::framebuffer_size_callback);
    glfwSetMouseButtonCallback(window,Controller::mouse_button_callback);
    glfwSetCursorPosCallback(window,Controller::mouse_callback);
    glfwSetScrollCallback(window,Controller::scroll_callback);
    glfwSetKeyCallback(window,Controller::keyboard_callback);
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Render()
{
    GenerateTris();
    CreateWireVertexBuffer();
    CreateSurfaceVertexBuffer();
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


        auto model=glm::mat4(1.0f);
        auto view=Controller::camera.getViewMatrix();
        glm::mat4 projection=glm::perspective(glm::radians(Controller::camera.Zoom),
                                                      (double)SCREEN_W/(double)SCREEN_H,
                                         0.1,50.0);
        auto mvp=projection*view*model;


        shader.get()->use();
        shader.get()->setMat4("MVPMatrix",mvp);
        if(Controller::IsWireFrameMode())
            RenderWireFrame();
        else
            RenderSurface();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Renderer::RenderWireFrame()
{
   // std::cout<<"Render Wire Frame"<<std::endl;

    assert(solid);
    glLineWidth(3);
    pEdge e=solid->s_edge;
//    std::cout<<"edge num is: "<<solid->GetEdgeNum()<<std::endl;
    assert(e);
    int cnt=0;
    do{
        cnt++;
        vec3 v1=e->he1->start_v->point->GetPoint();
        vec3 v2=e->he1->end_v->point->GetPoint();
//        std::cout<<e->id<<std::endl;
//        std::cout<<*(e->he1->start_v->point)<<std::endl;
//        std::cout<<*(e->he1->end_v->point)<<std::endl;
        line[0]=v1.x;line[1]=v1.y;line[2]=v1.z;
        line[3]=v2.x;line[4]=v2.y;line[5]=v2.z;
//        for(int i=0;i<6;i++)
//            std::cout<<line[i]<<std::endl;
        glNamedBufferSubData(l_vbo,0,sizeof(float)*6,line.data());
        glBindVertexArray(l_vao);
        glDrawArrays(GL_LINES,0,2);
        e=e->next_e;
    }while(e!=solid->s_edge);

}
void Renderer::CreateWireVertexBuffer()
{
    glGenVertexArrays(1,&l_vao);
    glGenBuffers(1,&l_vbo);

    glBindVertexArray(l_vao);
    glBindBuffer(GL_ARRAY_BUFFER,l_vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*6,nullptr,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Renderer::RenderSurface()
{
    glBindVertexArray(s_vao);
    glDrawArrays(GL_TRIANGLES,0,triangles.size()*3);
}
void Renderer::CreateSurfaceVertexBuffer()
{
    std::cout<<"triangles num is: "<<triangles.size()<<std::endl;
//    for(int i=0;i<triangles.size();i++){
//        std::cout<<triangles[i].v[0].x<<" "
//                <<triangles[i].v[0].y<<" "
//                <<triangles[i].v[0].z<<" "<<std::endl;
//    }
    glGenVertexArrays(1,&s_vao);
    glGenBuffers(1,&s_vbo);

    glBindVertexArray(s_vao);
    glBindBuffer(GL_ARRAY_BUFFER,s_vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*9*triangles.size(),triangles.data(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Renderer::Polygon2Tri(const pFace face)
{
    Plane2D plane(face);
    std::vector<p2t::Point*> all_points;
    std::vector<p2t::Point*> out_points;
    std::vector<p2t::Point*> in_points;

    //处理外环
    pLoop outer_lp=face->GetOuterLoop();
    pHalfEdge he=outer_lp->l_halfedge;
    do {
        glm::vec2 p=plane.Space3DToPlane2D(he->start_v->point->GetPoint());
        p2t::Point* point=new p2t::Point(p.x,p.y);
        all_points.push_back(point);
        out_points.push_back(point);
        he=he->next_he;
    }while(he!=outer_lp->l_halfedge);
    p2t::CDT cdt(std::move(out_points));
    //处理内环
    auto inner_lp=face->f_loop;
    do {
        if(!inner_lp->IsInnerLoop()){
            inner_lp=inner_lp->next_l;
            continue;
        }

        std::cout<<"processing inner loop"<<std::endl;
        inner_lp->PrintHalfEdgeInfo();
        pHalfEdge he=inner_lp->l_halfedge;
        do {
            glm::vec2 p=plane.Space3DToPlane2D(he->start_v->point->GetPoint());
            p2t::Point* point=new p2t::Point(p.x,p.y);
            in_points.push_back(point);
            all_points.push_back(point);

            he=he->next_he;
        }while(he!=inner_lp->l_halfedge);
        cdt.AddHole(std::move(in_points));
        inner_lp=inner_lp->next_l;
    }while(inner_lp!=face->f_loop);

    cdt.Triangulate();
    //二维点转回三维点 添加到三角数组中
    auto tris=cdt.GetTriangles();
    for(auto tri : tris){
        Triangle triangle;
        for(int i=0;i<3;i++){
            auto _p=tri->GetPoint(i);
            triangle.v[i]=plane.Plane2DToSpace3D(glm::vec2(_p->x,_p->y));
        }
        triangles.push_back(triangle);
    }
    for(auto p : all_points)
        delete p;
}

void Renderer::GenerateTris()
{
    triangles.clear();
    auto face=solid->s_face;
    do{
        std::cout<<"face id is: "<<face->id<<std::endl;
        Polygon2Tri(face);
        face=face->next_f;
    }while(face!=solid->s_face);
}


