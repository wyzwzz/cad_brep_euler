//
// Created by wyz on 20-11-13.
//
#include"b-rep.h"

uint32_t Solid::GetEdgeNum()
{
    if(s_edge== nullptr) return 0;
    auto eg=s_edge;
    uint32_t cnt=0;
    do{
        cnt++;
        eg=eg->next_e;
    }while(eg!=s_edge);

    return cnt;
}

uint32_t Solid::GetFaceNum()
{
    if(s_face == nullptr) return 0;
    auto face=s_face;
    uint32_t cnt=0;
    do{
        cnt++;
        face=face->next_f;
    }while(face!=s_face);

    return cnt;
}

void Solid::AddEdge(pEdge edge)
{
    if(!edge){
        std::cout<<"ERROR! Add edge is nullptr!"<<std::endl;
        return;
    }
    edge->id=GetEdgeNum()+1;
    if(!s_edge){
        s_edge=edge;
        //双向循环列表 只有一个元素时 prev和next都是自己
        s_edge->next_e=s_edge->prev_e=edge;
    }
    else{
        //双向循环列表 随便找个地方插入即可
        auto he1=s_edge;
        auto he2=s_edge->next_e;
        he1->next_e=edge;
        edge->prev_e=he1;
        he2->prev_e=edge;
        edge->next_e=he2;
    }

}

void Solid::DeleteEdge(pEdge edge)
{
    if(!edge){
        std::cout<<"ERROR! Delete edge is nullptr!"<<std::endl;
        return;
    }
    if(s_edge == nullptr){
        std::cout<<"ERRPR! This solid has no edges!"<<std::endl;
        return;
    }
    auto he=s_edge;
    while(he!=edge){
        he=he->next_e;
        if(he==s_edge){
            std::cout<<"ERROR! Can't find this edge in this solid's edges!"<<std::endl;
            return;
        }
    }
    if(GetEdgeNum()==1){
        delete s_edge;
        s_edge=nullptr;
    }
    else{
        auto he1=he->prev_e;
        auto he2=he->next_e;
        he1->next_e=he2;
        he2->prev_e=he1;
        if(he==s_edge)
            s_edge=he1;
        delete he;
    }
}

void Solid::AddFace(pFace face)
{
    if(!face){
        std::cout<<"ERROR! Add face is nullptr!"<<std::endl;
        return;
    }
    face->id=GetFaceNum()+1;
    if(!s_face){
        s_face=face;
        s_face->next_f=s_face->prev_f=face;
    }
    else{
        auto face1=s_face;
        auto face2=s_face->next_f;
        face1->next_f=face;
        face->prev_f=face1;
        face->next_f=face2;
        face2->prev_f=face;
    }
}

void Solid::DeleteFace(pFace face)
{
    if(!face){
        std::cout<<"ERROR! Delete face is nullptr!"<<std::endl;
        return;
    }
    if(!s_face){
        std::cout<<"ERROR! This solid's s_face is nullptr!"<<std::endl;
        return;
    }
    auto f=s_face;
    while(f!=face){
        f=f->next_f;
        if(f==s_face){
            std::cout<<"ERROR! Can't find the delete face!"<<std::endl;
            return;
        }
    }
    if(GetFaceNum()==1){
        delete s_face;
        s_face=nullptr;
    }
    else{
        auto f1=f->prev_f;
        auto f2=f->next_f;
        f1->next_f=f2;
        f2->prev_f=f1;
        if(f==s_face)
            s_face=f1;
        delete f;
    }
}

uint32_t Face::GetLoopNum() const
{
    if(!f_loop) return 0;

    uint32_t cnt=0;
    pLoop head=f_loop;
    pLoop cursor=f_loop;
    do{
        cnt++;
        cursor=cursor->next_l;
    }while (cursor!=head);
    return cnt;
}

void Face::AddLoop(pLoop loop)
{
    if(!loop){
        std::cout<<"ERROR! Add loop is nullptr!"<<std::endl;
        return;
    }
    loop->l_face=this;
    if(!f_loop){
        f_loop=loop;
        f_loop->next_l=f_loop->prev_l=loop;
    }
    else{
        auto l1=f_loop;
        auto l2=f_loop->next_l;
        l1->next_l=loop;
        loop->prev_l=l1;
        loop->next_l=l2;
        l2->prev_l=loop;
    }
}

void Face::DeleteLoop(pLoop loop)
{

}

pLoop Face::GetOuterLoop()
{
    auto lp=f_loop;
    do{
        if(!lp->is_inner_loop)
            return lp;
        lp=lp->next_l;
    }while(lp!=f_loop);
}

pLoop Solid::FindLoopByStartVAndEndV(pVertex start_v,pVertex end_v)
{
    auto edge=s_edge;
    do{
        auto he=edge->he1;
        if(he->start_v==start_v && he->end_v==end_v)
            return he->he_loop;
        he=edge->he2;
        if(he->start_v==start_v && he->end_v==end_v)
            return he->he_loop;

        edge=edge->next_e;
    }while(edge!=s_edge);
}

uint32_t Loop::GetEdgeNum() const
{
    if(!l_halfedge) return 0;
    uint32_t cnt=0;
    pHalfEdge head=l_halfedge;
    pHalfEdge cursor=l_halfedge;
    do{
        cnt++;
        cursor=cursor->next_he;
    }while (cursor!=head);
    return cnt;
}
void Loop::AddEdge(pVertex v0,pVertex v)
{

}

void Loop::AddHalfEdge(pHalfEdge last_he,pHalfEdge n_he)
{
    auto he1=last_he;
    auto he2=last_he->next_he;
    he1->next_he=n_he;
    n_he->prev_he=he1;
    n_he->next_he=he2;
    he2->prev_he=n_he;

}

void Loop::DeleteHalfEdge(pHalfEdge he)
{

}

bool Loop::FindHalfEdge(pHalfEdge he)
{
    if(!he && !l_halfedge)
        return false;
    auto cursor=l_halfedge;
    while(cursor!=he){
        cursor=cursor->next_he;
        if(cursor==l_halfedge)
            return false;
    }
    return true;
}

void Loop::PrintHalfEdgeInfo()
{
    auto he=l_halfedge;
    do {
        std::cout<<*(he->start_v->point)<<" "<<*(he->end_v->point)<<std::endl;
        he=he->next_he;
    }while (he!=l_halfedge);
}

