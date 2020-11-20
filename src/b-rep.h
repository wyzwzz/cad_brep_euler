//
// Created by wyz on 20-11-13.
//

#ifndef EULEROPERATION_B_REP_H
#define EULEROPERATION_B_REP_H
#include<iostream>
#include<glm/glm.hpp>
class Solid;
class Face;
class Loop;
class Edge;
class HalfEdge;
class Vertex;
class Point;

using pSolid=Solid*;
using pFace=Face*;
using pLoop=Loop*;
using pEdge=Edge*;
using pHalfEdge=HalfEdge*;
using pVertex=Vertex*;
using pPoint=Point*;

//双向循环链表，当只有一个元素时，next和prev都指向自身
class Solid{
public:
    Solid():prev_s(nullptr),next_s(nullptr),s_face(nullptr),s_edge(nullptr){};
    ~Solid();
    pSolid prev_s,next_s;
    pFace s_face;//顺序无关
    pEdge s_edge;//顺序无关
public:
    uint32_t GetEdgeNum();
    uint32_t GetFaceNum();
    void AddFace(pFace face);
    void DeleteFace(pFace face);
    void AddEdge(pEdge edge);
    void DeleteEdge(pEdge edge);
    pLoop FindLoopByStartVAndEndV(pVertex start_v,pVertex end_v);
};

class Face{
public:
    Face():f_solid(nullptr),prev_f(nullptr),next_f(nullptr),f_loop(nullptr){}
    pSolid f_solid;
    pFace prev_f,next_f;
    pLoop f_loop;
    uint id;
public:
    uint32_t GetLoopNum() const;
    void AddLoop(pLoop loop);
    void DeleteLoop(pLoop loop);
    pLoop GetOuterLoop();

};

class Loop{
public:
    Loop(bool is_inner=false):l_face(nullptr),prev_l(nullptr),next_l(nullptr),l_halfedge(nullptr),is_inner_loop(is_inner){}
    pFace l_face;
    pLoop prev_l,next_l;
    pHalfEdge l_halfedge;//顺序有关
    bool is_inner_loop;
public:
    bool IsInnerLoop() const{return is_inner_loop;}
    uint32_t GetEdgeNum() const;
    void AddEdge(pVertex v0,pVertex v);
    void AddHalfEdge(pHalfEdge last_he,pHalfEdge n_he);
    void DeleteHalfEdge(pHalfEdge he);
    bool FindHalfEdge(pHalfEdge he);
    void PrintHalfEdgeInfo();
};

class Edge{
public:
    Edge():prev_e(nullptr),next_e(nullptr),he1(nullptr),he2(nullptr){}
    uint id;
    pEdge prev_e,next_e;
    pHalfEdge he1,he2;
};

class HalfEdge{
public:
    HalfEdge():he_loop(nullptr),prev_he(nullptr),next_he(nullptr),adj_he(nullptr),
    he_e(nullptr),start_v(nullptr),end_v(nullptr){}

    pLoop he_loop;
    pHalfEdge prev_he,next_he;

    pHalfEdge adj_he;
    pEdge he_e;
    pVertex start_v,end_v;
};

class Vertex{
public:
    Vertex():prev_v(nullptr),next_v(nullptr),point(nullptr){}
    Vertex(pPoint p):prev_v(nullptr),next_v(nullptr),point(p){}

    pVertex prev_v,next_v;
    pPoint point;
};

class Point{
    glm::vec3 pos;
    glm::vec3 color;
public:
     Point():pos(0),color(0){}
     Point(float x,float y,float z):pos(glm::vec3(x,y,z)),color(0){}
     Point(glm::vec3 pos,glm::vec3 color=glm::vec3(0)):pos(pos),color(color){}
     Point(const Point& p):pos(p.GetPoint()),color(p.GetColor()){}
     void SetPoint(glm::vec3 pos){
         this->pos=pos;
     }
     glm::vec3 GetPoint() const {return pos;}
     glm::vec3 GetColor() const {return color;}
     friend std::ostream &operator<<(std::ostream& os,const Point& point){
         auto p=point.GetPoint();
         os<<"("<<p.x<<","<<p.y<<","<<p.z<<")";
         return os;
     }
};




#endif //EULEROPERATION_B_REP_H
