//
// Created by wyz on 20-11-13.
//

#include "euleroperation.h"
/*
 * create a solid, a face, a outer-loop, a vertex
 */
pSolid EulerOperation::mvfs(Point p,Vertex* &v)
{
    pSolid solid=new Solid();
    pFace face=new Face();
    pLoop loop=new Loop();

    pPoint point=new Point(p);
    v=new Vertex(point);

    solid->s_face=face;
    face->f_solid=solid;
    face->f_loop=loop;
    loop->l_face=face;

    return solid;
}

/*
 * create a vertex and a edge which another vertex is given
 */
pHalfEdge EulerOperation::mev(Point p,const pVertex v,const pLoop loop)
{
    pHalfEdge he1=new HalfEdge();
    pHalfEdge he2=new HalfEdge();
    pEdge edge=new Edge();

    edge->he1=he1;
    edge->he2=he2;
    he1->he_e=he2->he_e=edge;
    he1->adj_he=he2;
    he2->adj_he=he1;

    pPoint n_point=new Point(p);
    pVertex n_vertex=new Vertex(n_point);
    he1->start_v=v;//he1: old->new vertex direction
    he1->end_v=n_vertex;
    he2->start_v=n_vertex;
    he2->end_v=v;

    he1->he_loop=he2->he_loop=loop;
    he1->next_he=he2;
    he2->prev_he=he1;
    if(loop->l_halfedge == nullptr){//loop is empty
        he2->next_he=he1;
        he1->prev_he=he2;
        loop->l_halfedge=he1;
    }
    else{
        pHalfEdge he=loop->l_halfedge;
        while(he->end_v!=v) he=he->next_he;
        he2->next_he=he->next_he;
        he->next_he->prev_he=he2;
        he->next_he=he1;
        he1->prev_he=he;
    }

    pSolid solid=loop->l_face->f_solid;
    solid->AddEdge(edge);

    return he1;
}
/*
 * create a edge with two given vertex, and a new loop and a new face
 * main loop is created by mvfs
 */
pLoop EulerOperation::mef(const pVertex v1,const pVertex v2,pLoop main_loop)
{
    pHalfEdge he1=new HalfEdge();
    pHalfEdge he2=new HalfEdge();
    pEdge edge=new Edge();

    edge->he1=he1;
    edge->he2=he2;
    he1->he_e=he2->he_e=edge;
    he1->adj_he=he2;
    he2->adj_he=he1;
    he1->start_v=he2->end_v=v1;
    he1->end_v=he2->start_v=v2;

    pLoop n_loop=new Loop();
    n_loop->l_halfedge=he2;
    main_loop->l_halfedge=he1;

    pHalfEdge m_he1,m_he2,m_he;
    m_he=main_loop->l_halfedge;
    while(m_he->start_v!=v1) m_he=m_he->next_he;
    m_he1=m_he;
    m_he=main_loop->l_halfedge;
    while(m_he->start_v!=v2) m_he=m_he->next_he;
    m_he2=m_he;

    he1->next_he=m_he2;
    he1->prev_he=m_he1->prev_he;
    he2->next_he=m_he1;
    he2->prev_he=m_he1->prev_he;
    m_he1->prev_he->next_he=he1;
    m_he1->prev_he=he2;
    m_he2->prev_he->next_he=he2;
    m_he2->prev_he=he1;

    pHalfEdge he=n_loop->l_halfedge;
    while(he->next_he!=n_loop->l_halfedge){
        he->he_loop=n_loop;
        he=he->next_he;
    }
    he=main_loop->l_halfedge;
    while(he->next_he!=main_loop->l_halfedge){
        he->he_loop=main_loop;
        he=he->next_he;
    }

    pSolid solid=main_loop->l_face->f_solid;
    pFace n_face=new Face();
    n_face->f_loop=n_loop;
    n_loop->l_face=n_face;
    n_face->f_solid=solid;
    solid->AddFace(n_face);
    solid->AddEdge(edge);
}
/*
 * delete an edge and make an inner-loop
 * in loop is not main loop, need to swap before call this function
 * v1 is on the inner-loop while v2 is on the outer-loop
 */
pLoop EulerOperation::kemr(const pVertex v1,const pVertex v2,pLoop loop)
{
    pLoop n_loop=new Loop(true);
    pHalfEdge he=loop->l_halfedge;
    while(he->start_v!=v1 || he->end_v!=v2) he=he->next_he;
    pEdge del_edge=he->he_e;
    pHalfEdge adj_he=he->adj_he;

    he->prev_he->next_he=adj_he->next_he;
    he->next_he->prev_he=adj_he->prev_he;
    adj_he->next_he->prev_he=he->prev_he;
    adj_he->prev_he->next_he=he->next_he;

    n_loop->l_halfedge=he->prev_he;
    loop->l_halfedge=he->next_he;
    auto _he=n_loop->l_halfedge;
    while(_he->next_he!=n_loop->l_halfedge){
        _he->he_loop=n_loop;
        _he=_he->next_he;
    }
    pFace face=loop->l_face;
    face->AddLoop(n_loop);

    pSolid solid=face->f_solid;
    solid->DeleteEdge(del_edge);

    return n_loop;
}
/*
 * delete a face and redefine as a hole
 * input del_face should just has one outer loop with no inner loop exist
 */
void EulerOperation::kfmrh(pFace del_face,pFace face)
{
    if(del_face->GetLoopNum()>1){
        std::cout<<"kfmrh error: delete face has more than one loop!"<<std::endl;
        return;
    }
    face->AddLoop(del_face->f_loop);

    pSolid solid=del_face->f_solid;
    solid->DeleteFace(del_face);
}
/*
 * moving a face according to the move_vec which result a solid
 * todo:考虑底面带环进行扫成后的顶面
 */
pSolid EulerOperation::sweep(pFace face,glm::vec3 move_vec)
{
    pSolid solid=face->f_solid;
    pLoop lp=face->f_loop;
    do {
        auto he=lp->l_halfedge;
        auto first_v=he->start_v;
        Point n_pos=first_v->point->GetPoint()+move_vec;
        pHalfEdge first_up_he=mev(n_pos,first_v,lp);
        pVertex  last_up_v=he->end_v;

        he=he->next_he;
        pVertex v=he->start_v;
        while(v!=first_v){
            Point n_pos=v->point->GetPoint()+move_vec;
            pHalfEdge up_he=mev(n_pos,v,lp);
            pVertex up_v=up_he->end_v;
            mef(up_v,last_up_v,lp);
            last_up_v=up_v;
            he=he->next_he;
            v=he->start_v;
        }
        mef(first_up_he->end_v,last_up_v,lp);
        lp=lp->next_l;
    }while(lp!=face->f_loop);

    return solid;
}