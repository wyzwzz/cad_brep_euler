//
// Created by wyz on 20-11-18.
//

#include "creation.h"
void PrintSolid(const pSolid solid);
pSolid Creation::CreateSolid()
{
    pSolid solid;
    pVertex top_upper_left;
    solid=EulerOperation::mvfs(Point(-1.0,0.5,2.0),top_upper_left);
    pLoop top_loop=solid->s_face->f_loop;

    pHalfEdge top_upper_halfedge=EulerOperation::mev(Point(1.0,0.5,2.0),top_upper_left,top_loop);
    pVertex top_upper_right=top_upper_halfedge->end_v;

    pHalfEdge top_left_halfedge=EulerOperation::mev(Point(-1.0,0.5,-2.0),top_upper_left,top_loop);
    pVertex  top_bottom_left=top_left_halfedge->end_v;

    pHalfEdge top_right_halfedge=EulerOperation::mev(Point(1.0,0.5,-2.0),top_upper_right,top_loop);
    pVertex top_bottom_right=top_right_halfedge->end_v;

    pLoop down_loop=EulerOperation::mef(top_bottom_left,top_bottom_right,top_loop);
//    PrintSolid(solid);
//    std::cout<<solid->GetEdgeNum()<<std::endl;
//    std::cout<<solid->GetFaceNum()<<std::endl;
//    std::cout<<solid->s_face->next_f->GetLoopNum()<<std::endl;
    EulerOperation::sweep(down_loop->l_face,glm::vec3(0,-1,0));
//    PrintSolid(solid);
    return solid;
}

pSolid Creation::CreateSolidZero()
{
    pSolid solid;
    pVertex top_upper_left;
    solid=EulerOperation::mvfs(Point(-1.0,0.5,2.0),top_upper_left);
    pLoop top_loop=solid->s_face->f_loop;

    pHalfEdge top_upper_halfedge=EulerOperation::mev(Point(1.0,0.5,2.0),top_upper_left,top_loop);
    pVertex top_upper_right=top_upper_halfedge->end_v;

    pHalfEdge top_left_halfedge=EulerOperation::mev(Point(-1.0,0.5,-2.0),top_upper_left,top_loop);
    pVertex  top_bottom_left=top_left_halfedge->end_v;

    pHalfEdge top_right_halfedge=EulerOperation::mev(Point(1.0,0.5,-2.0),top_upper_right,top_loop);
    pVertex top_bottom_right=top_right_halfedge->end_v;

    pLoop down_loop=EulerOperation::mef(top_bottom_left,top_bottom_right,top_loop);

    pHalfEdge front_left_halfedge=EulerOperation::mev(Point(-1.0,-0.5,2.0),top_upper_left,down_loop);
    pVertex down_front_left=front_left_halfedge->end_v;

    pHalfEdge front_right_halfedge=EulerOperation::mev(Point(1.0,-0.5,2.0),top_upper_right,down_loop);
    pVertex  down_front_right=front_right_halfedge->end_v;

    pHalfEdge back_left_halfedge=EulerOperation::mev(Point(-1.0,-0.5,-2.0),top_bottom_left,down_loop);
    pVertex down_back_left=back_left_halfedge->end_v;

    pHalfEdge back_right_halfedge=EulerOperation::mev(Point(1.0,-0.5,-2.0),top_bottom_right,down_loop);
    pVertex down_back_right=back_right_halfedge->end_v;

    pLoop front_loop=EulerOperation::mef(down_front_left,down_front_right,down_loop);
    pLoop right_loop=EulerOperation::mef(down_front_right,down_back_right,down_loop);
    pLoop back_loop=EulerOperation::mef(down_back_right,down_back_left,down_loop);
    pLoop left_loop=EulerOperation::mef(down_back_left,down_front_left,down_loop);

    pHalfEdge top_bridge=EulerOperation::mev(Point(-0.5,0.5,1.5),top_upper_left,top_loop);
    pVertex top_inner_front_left=top_bridge->end_v;

    pHalfEdge top_inner_left_halfedge=EulerOperation::mev(Point(-0.5,0.5,-1.5),top_inner_front_left,top_loop);
    pVertex top_inner_back_left=top_inner_left_halfedge->end_v;

    pHalfEdge top_inner_back_halfedge=EulerOperation::mev(Point(0.5,0.5,-1.5),top_inner_back_left,top_loop);
    pVertex top_inner_back_right=top_inner_back_halfedge->end_v;

    pHalfEdge top_inner_right_halfedge=EulerOperation::mev(Point(0.5,0.5,1.5),top_inner_back_right,top_loop);
    pVertex top_inner_front_right=top_inner_right_halfedge->end_v;

    //change v1 and v2's order to return the main_loop
    pLoop down_inner_loop=EulerOperation::mef(top_inner_front_left,top_inner_front_right,top_loop);

    pLoop top_inner_loop=EulerOperation::kemr(top_upper_left,top_inner_front_left,top_loop);
    swap(top_loop,top_inner_loop);
//    top_loop->PrintHalfEdgeInfo();
//    top_inner_loop->PrintHalfEdgeInfo();
//    std::cout<<"top inner loop is inner: "<<top_inner_loop->IsInnerLoop()<<std::endl;
    pHalfEdge inner_front_left_halfedge=EulerOperation::mev(Point(-0.5,-0.5,1.5),top_inner_front_left,down_inner_loop);
    pVertex inner_bottom_front_left=inner_front_left_halfedge->end_v;

    pHalfEdge inner_front_right_halfedge=EulerOperation::mev(Point(0.5,-0.5,1.5),top_inner_front_right,down_inner_loop);
    pVertex inner_bottom_front_right=inner_front_right_halfedge->end_v;

    pHalfEdge inner_back_left_halfedge=EulerOperation::mev(Point(-0.5,-0.5,-1.5),top_inner_back_left,down_inner_loop);
    pVertex inner_bottom_back_left=inner_back_left_halfedge->end_v;

    pHalfEdge inner_back_right_halfedge=EulerOperation::mev(Point(0.5,-0.5,-1.5),top_inner_back_right,down_inner_loop);
    pVertex inner_bottom_back_right=inner_back_right_halfedge->end_v;

    pLoop inner_front_loop=EulerOperation::mef(inner_bottom_front_right,inner_bottom_front_left,down_inner_loop);
    pLoop inner_left_loop=EulerOperation::mef(inner_bottom_front_left,inner_bottom_back_left,down_inner_loop);
    pLoop inner_back_loop=EulerOperation::mef(inner_bottom_back_left,inner_bottom_back_right,down_inner_loop);
    pLoop inner_right_loop=EulerOperation::mef(inner_bottom_back_right,inner_bottom_front_right,down_inner_loop);

//    std::cout<<"face num is: "<<solid->GetFaceNum()<<std::endl;

    EulerOperation::kfmrh(down_inner_loop->l_face,down_loop->l_face);
//    std::cout<<"face num is: "<<solid->GetFaceNum()<<std::endl;
    return solid;
}

pSolid Creation::CreateSolidEight()
{
    pSolid solid;
    pVertex top_front_left;
    solid=EulerOperation::mvfs(Point(-1.0,0.5,2.0),top_front_left);
    pLoop top_loop=solid->s_face->f_loop;

    pHalfEdge top_front_halfedge=EulerOperation::mev(Point(1.0,0.5,2.0),top_front_left,top_loop);
    pVertex top_front_right=top_front_halfedge->end_v;

    pHalfEdge top_left_halfedge=EulerOperation::mev(Point(-1.0,0.5,-2.0),top_front_left,top_loop);
    pVertex  top_back_left=top_left_halfedge->end_v;

    pHalfEdge top_right_halfedge=EulerOperation::mev(Point(1.0,0.5,-2.0),top_front_right,top_loop);
    pVertex top_back_right=top_right_halfedge->end_v;

    pLoop down_loop=EulerOperation::mef(top_back_left,top_back_right,top_loop);

    pHalfEdge front_left_halfedge=EulerOperation::mev(Point(-1.0,-0.5,2.0),top_front_left,down_loop);
    pVertex down_front_left=front_left_halfedge->end_v;

    pHalfEdge front_right_halfedge=EulerOperation::mev(Point(1.0,-0.5,2.0),top_front_right,down_loop);
    pVertex  down_front_right=front_right_halfedge->end_v;

    pHalfEdge back_left_halfedge=EulerOperation::mev(Point(-1.0,-0.5,-2.0),top_back_left,down_loop);
    pVertex down_back_left=back_left_halfedge->end_v;

    pHalfEdge back_right_halfedge=EulerOperation::mev(Point(1.0,-0.5,-2.0),top_back_right,down_loop);
    pVertex down_back_right=back_right_halfedge->end_v;

    pLoop front_loop=EulerOperation::mef(down_front_left,down_front_right,down_loop);
    pLoop right_loop=EulerOperation::mef(down_front_right,down_back_right,down_loop);
    pLoop back_loop=EulerOperation::mef(down_back_right,down_back_left,down_loop);
    pLoop left_loop=EulerOperation::mef(down_back_left,down_front_left,down_loop);

    pHalfEdge top_bridge=EulerOperation::mev(Point(-0.5,0.5,1.5),top_front_left,top_loop);
    pVertex top_inner_front_left=top_bridge->end_v;

    pHalfEdge top_inner_left_halfedge=EulerOperation::mev(Point(-0.5,0.5,0.5),top_inner_front_left,top_loop);
    pVertex top_inner_back_left=top_inner_left_halfedge->end_v;

    pHalfEdge top_inner_back_halfedge=EulerOperation::mev(Point(0.5,0.5,0.5),top_inner_back_left,top_loop);
    pVertex top_inner_back_right=top_inner_back_halfedge->end_v;

    pHalfEdge top_inner_right_halfedge=EulerOperation::mev(Point(0.5,0.5,1.5),top_inner_back_right,top_loop);
    pVertex top_inner_front_right=top_inner_right_halfedge->end_v;

    //change v1 and v2's order to return the main_loop
    pLoop down_inner_loop=EulerOperation::mef(top_inner_front_left,top_inner_front_right,top_loop);

    pLoop top_inner_loop=EulerOperation::kemr(top_front_left,top_inner_front_left,top_loop);
    swap(top_loop,top_inner_loop);
//    top_loop->PrintHalfEdgeInfo();
//    top_inner_loop->PrintHalfEdgeInfo();
//    std::cout<<"top inner loop is inner: "<<top_inner_loop->IsInnerLoop()<<std::endl;
    pHalfEdge inner_front_left_halfedge=EulerOperation::mev(Point(-0.5,-0.5,1.5),top_inner_front_left,down_inner_loop);
    pVertex inner_bottom_front_left=inner_front_left_halfedge->end_v;

    pHalfEdge inner_front_right_halfedge=EulerOperation::mev(Point(0.5,-0.5,1.5),top_inner_front_right,down_inner_loop);
    pVertex inner_bottom_front_right=inner_front_right_halfedge->end_v;

    pHalfEdge inner_back_left_halfedge=EulerOperation::mev(Point(-0.5,-0.5,0.5),top_inner_back_left,down_inner_loop);
    pVertex inner_bottom_back_left=inner_back_left_halfedge->end_v;

    pHalfEdge inner_back_right_halfedge=EulerOperation::mev(Point(0.5,-0.5,0.5),top_inner_back_right,down_inner_loop);
    pVertex inner_bottom_back_right=inner_back_right_halfedge->end_v;

    pLoop inner_front_loop=EulerOperation::mef(inner_bottom_front_right,inner_bottom_front_left,down_inner_loop);
    pLoop inner_left_loop=EulerOperation::mef(inner_bottom_front_left,inner_bottom_back_left,down_inner_loop);
    pLoop inner_back_loop=EulerOperation::mef(inner_bottom_back_left,inner_bottom_back_right,down_inner_loop);
    pLoop inner_right_loop=EulerOperation::mef(inner_bottom_back_right,inner_bottom_front_right,down_inner_loop);

//    std::cout<<"face num is: "<<solid->GetFaceNum()<<std::endl;

    EulerOperation::kfmrh(down_inner_loop->l_face,down_loop->l_face);
//    std::cout<<"face num is: "<<solid->GetFaceNum()<<std::endl;

//    top_loop->PrintHalfEdgeInfo();
//    top_inner_loop->PrintHalfEdgeInfo();
//    std::cout<<"top loop is inner: "<<top_loop->IsInnerLoop()<<std::endl;

    pHalfEdge top_bridge2=EulerOperation::mev(Point(-0.5,0.5,-0.5),top_front_left,top_loop);
    pVertex top_inner_front_left2=top_bridge2->end_v;

    pHalfEdge top_inner_left_halfedge2=EulerOperation::mev(Point(-0.5,0.5,-1.5),top_inner_front_left2,top_loop);
    pVertex top_inner_back_left2=top_inner_left_halfedge2->end_v;

    pHalfEdge top_inner_back_halfedge2=EulerOperation::mev(Point(0.5,0.5,-1.5),top_inner_back_left2,top_loop);
    pVertex top_inner_back_right2=top_inner_back_halfedge2->end_v;

    pHalfEdge top_inner_right_halfedge2=EulerOperation::mev(Point(0.5,0.5,-0.5),top_inner_back_right2,top_loop);
    pVertex top_inner_front_right2=top_inner_right_halfedge2->end_v;

    //change v1 and v2's order to return the main_loop
    pLoop down_inner_loop2=EulerOperation::mef(top_inner_front_left2,top_inner_front_right2,top_loop);

    pLoop top_inner_loop2=EulerOperation::kemr(top_front_left,top_inner_front_left2,top_loop);
//    std::cout<<"top inner loop is inner: "<<top_inner_loop2->IsInnerLoop()<<std::endl;
    pHalfEdge inner_front_left_halfedge2=EulerOperation::mev(Point(-0.5,-0.5,-0.5),top_inner_front_left2,down_inner_loop2);
    pVertex inner_bottom_front_left2=inner_front_left_halfedge2->end_v;

    pHalfEdge inner_front_right_halfedge2=EulerOperation::mev(Point(0.5,-0.5,-0.5),top_inner_front_right2,down_inner_loop2);
    pVertex inner_bottom_front_right2=inner_front_right_halfedge2->end_v;

    pHalfEdge inner_back_left_halfedge2=EulerOperation::mev(Point(-0.5,-0.5,-1.5),top_inner_back_left2,down_inner_loop2);
    pVertex inner_bottom_back_left2=inner_back_left_halfedge2->end_v;

    pHalfEdge inner_back_right_halfedge2=EulerOperation::mev(Point(0.5,-0.5,-1.5),top_inner_back_right2,down_inner_loop2);
    pVertex inner_bottom_back_right2=inner_back_right_halfedge2->end_v;

    pLoop inner_front_loop2=EulerOperation::mef(inner_bottom_front_right2,inner_bottom_front_left2,down_inner_loop2);
    pLoop inner_left_loop2=EulerOperation::mef(inner_bottom_front_left2,inner_bottom_back_left2,down_inner_loop2);
    pLoop inner_back_loop2=EulerOperation::mef(inner_bottom_back_left2,inner_bottom_back_right2,down_inner_loop2);
    pLoop inner_right_loop2=EulerOperation::mef(inner_bottom_back_right2,inner_bottom_front_right2,down_inner_loop2);

//    std::cout<<"face num is: "<<solid->GetFaceNum()<<std::endl;

    EulerOperation::kfmrh(down_inner_loop2->l_face,down_loop->l_face);
//    std::cout<<"face num is: "<<solid->GetFaceNum()<<std::endl;

    return solid;
}

pSolid Creation::CreateSolidZeroUseSweep()
{
    pSolid solid;
    pVertex top_upper_left;
    solid=EulerOperation::mvfs(Point(-1.0,0.5,2.0),top_upper_left);
    pLoop top_loop=solid->s_face->f_loop;

    pHalfEdge top_upper_halfedge=EulerOperation::mev(Point(1.0,0.5,2.0),top_upper_left,top_loop);
    pVertex top_upper_right=top_upper_halfedge->end_v;

    pHalfEdge top_left_halfedge=EulerOperation::mev(Point(-1.0,0.5,-2.0),top_upper_left,top_loop);
    pVertex  top_bottom_left=top_left_halfedge->end_v;

    pHalfEdge top_right_halfedge=EulerOperation::mev(Point(1.0,0.5,-2.0),top_upper_right,top_loop);
    pVertex top_bottom_right=top_right_halfedge->end_v;

    pLoop down_loop=EulerOperation::mef(top_bottom_left,top_bottom_right,top_loop);

    pHalfEdge top_bridge=EulerOperation::mev(Point(-0.5,0.5,1.5),top_upper_left,top_loop);
    pVertex top_inner_front_left=top_bridge->end_v;

    pHalfEdge top_inner_left_halfedge=EulerOperation::mev(Point(-0.5,0.5,-1.5),top_inner_front_left,top_loop);
    pVertex top_inner_back_left=top_inner_left_halfedge->end_v;

    pHalfEdge top_inner_back_halfedge=EulerOperation::mev(Point(0.5,0.5,-1.5),top_inner_back_left,top_loop);
    pVertex top_inner_back_right=top_inner_back_halfedge->end_v;

    pHalfEdge top_inner_right_halfedge=EulerOperation::mev(Point(0.5,0.5,1.5),top_inner_back_right,top_loop);
    pVertex top_inner_front_right=top_inner_right_halfedge->end_v;

    //change v1 and v2's order to return the main_loop
    pLoop down_inner_loop=EulerOperation::mef(top_inner_front_left,top_inner_front_right,top_loop);

    pLoop top_inner_loop=EulerOperation::kemr(top_upper_left,top_inner_front_left,top_loop);
    swap(top_loop,top_inner_loop);
    EulerOperation::kfmrh(down_inner_loop->l_face,down_loop->l_face);

    EulerOperation::sweep(down_loop->l_face,glm::vec3(0.0,-1.0,0.0));
    return solid;
}



pSolid Creation::CreateCompactSolid()
{
    pSolid solid;
    pVertex v1;
    solid=EulerOperation::mvfs(Point(-10.0,3.0,10.0),v1);
    pLoop top_loop=solid->s_face->f_loop;

    pHalfEdge v1_to_v2=EulerOperation::mev(Point(-10.0,3.0,6.0),v1,top_loop);
    pVertex v2=v1_to_v2->end_v;

    pHalfEdge v2_to_v3=EulerOperation::mev(Point(-3.0,3.0,6.0),v2,top_loop);
    pVertex v3=v2_to_v3->end_v;

    pHalfEdge v3_to_t4=EulerOperation::mev(Point(-3.0,3.0,-6.0),v3,top_loop);
    pVertex v4=v3_to_t4->end_v;

    pHalfEdge v4_to_v5=EulerOperation::mev(Point(-10.0,3.0,-6.0),v4,top_loop);
    pVertex v5=v4_to_v5->end_v;

    pHalfEdge v5_to_v6=EulerOperation::mev(Point(-10.0,3.0,-10.0),v5,top_loop);
    pVertex v6=v5_to_v6->end_v;

    pHalfEdge v6_to_v7=EulerOperation::mev(Point(10.0,3.0,-10.0),v6,top_loop);
    pVertex v7=v6_to_v7->end_v;

    pHalfEdge v7_to_v8=EulerOperation::mev(Point(10.0,3.0,-6.0),v7,top_loop);
    pVertex v8=v7_to_v8->end_v;

    pHalfEdge v8_to_v9=EulerOperation::mev(Point(3.0,3.0,-6.0),v8,top_loop);
    pVertex v9=v8_to_v9->end_v;

    pHalfEdge v9_to_v10=EulerOperation::mev(Point(3.0,3.0,6.0),v9,top_loop);
    pVertex v10=v9_to_v10->end_v;

    pHalfEdge v10_to_v11=EulerOperation::mev(Point(10.0,3.0,6.0),v10,top_loop);
    pVertex v11=v10_to_v11->end_v;

    pHalfEdge v11_to_v12=EulerOperation::mev(Point(10.0,3.0,10.0),v11,top_loop);
    pVertex v12=v11_to_v12->end_v;

    pLoop down_loop=EulerOperation::mef(v12,v1,top_loop);

    pHalfEdge top_bridge=EulerOperation::mev(Point(-2.0,3.0,6.0),v1,top_loop);
    pVertex v13=top_bridge->end_v;

    pHalfEdge v13_to_v14=EulerOperation::mev(Point(-2.0,3.0,-6.0),v13,top_loop);
    pVertex v14=v13_to_v14->end_v;

    pHalfEdge v14_to_v15=EulerOperation::mev(Point(2.0,3.0,-6.0),v14,top_loop);
    pVertex v15=v14_to_v15->end_v;

    pHalfEdge v15_to_v16=EulerOperation::mev(Point(2.0,3.0,6.0),v15,top_loop);
    pVertex  v16=v15_to_v16->end_v;

    pLoop down_inner_loop=EulerOperation::mef(v13,v16,top_loop);

    pLoop top_inner_loop=EulerOperation::kemr(v1,v13,top_loop);
    swap(top_loop,top_inner_loop);
    EulerOperation::kfmrh(down_inner_loop->l_face,down_loop->l_face);

    EulerOperation::sweep(down_loop->l_face,glm::vec3(0.0,-6.0,0.0));

    pLoop back_loop=solid->FindLoopByStartVAndEndV(v7,v6);
//    back_loop->PrintHalfEdgeInfo();
    pHalfEdge bridge1=EulerOperation::mev(Point(-9.0,2.0,-10.0),v6,back_loop);
    pVertex v17=bridge1->end_v;

    pHalfEdge v17_to_v18=EulerOperation::mev(Point(-9.0,-2.0,-10.0),v17,back_loop);
    pVertex v18=v17_to_v18->end_v;

    pHalfEdge v18_to_v19=EulerOperation::mev(Point(-5.0,-2.0,-10.0),v18,back_loop);
    pVertex v19=v18_to_v19->end_v;

    pHalfEdge v19_to_v20=EulerOperation::mev(Point(-5.0,2.0,-10.0),v19,back_loop);
    pVertex v20=v19_to_v20->end_v;

    pLoop through_inner_loop=EulerOperation::mef(v17,v20,back_loop);

    pLoop back_inner_loop=EulerOperation::kemr(v6,v17,back_loop);
    swap(back_loop,back_inner_loop);

    pHalfEdge v17_to_v21=EulerOperation::mev(Point(-9.0,2.0,-6.0),v17,through_inner_loop);
    pVertex v21=v17_to_v21->end_v;

    pHalfEdge v18_to_v22=EulerOperation::mev(Point(-9.0,-2.0,-6.0),v18,through_inner_loop);
    pVertex v22=v18_to_v22->end_v;

    pHalfEdge v19_to_v23=EulerOperation::mev(Point(-5.0,-2.0,-6.0),v19,through_inner_loop);
    pVertex v23=v19_to_v23->end_v;

    pHalfEdge v20_to_v24=EulerOperation::mev(Point(-5.0,2.0,-6.0),v20,through_inner_loop);
    pVertex v24=v20_to_v24->end_v;

    pLoop through_inner_left_loop=EulerOperation::mef(v21,v22,through_inner_loop);
    pLoop through_inner_up_loop=EulerOperation::mef(v22,v23,through_inner_loop);
    pLoop through_inner_right_loop=EulerOperation::mef(v23,v24,through_inner_loop);
    pLoop through_inner_bottom_loop=EulerOperation::mef(v24,v21,through_inner_loop);
    pLoop through_front_loop1=solid->FindLoopByStartVAndEndV(v5,v4);
    EulerOperation::kfmrh(through_inner_loop->l_face,through_front_loop1->l_face);

    pHalfEdge bridge2=EulerOperation::mev(Point(5.0,2.0,-10.0),v6,back_loop);
    pVertex v25=bridge2->end_v;

    pHalfEdge v25_to_v26=EulerOperation::mev(Point(5.0,-2.0,-10.0),v25,back_loop);
    pVertex v26=v25_to_v26->end_v;

    pHalfEdge v26_to_v27=EulerOperation::mev(Point(9.0,-2.0,-10.0),v26,back_loop);
    pVertex v27=v26_to_v27->end_v;

    pHalfEdge v27_to_v28=EulerOperation::mev(Point(9.0,2.0,-10.0),v27,back_loop);
    pVertex v28=v27_to_v28->end_v;

    pLoop through_inner_loop2=EulerOperation::mef(v25,v28,back_loop);

    pLoop back_inner_loop2=EulerOperation::kemr(v6,v25,back_loop);
    swap(back_loop,back_inner_loop2);

    pHalfEdge v25_to_v29=EulerOperation::mev(Point(5.0,2.0,-6.0),v25,through_inner_loop2);
    pVertex v29=v25_to_v29->end_v;

    pHalfEdge v26_to_v30=EulerOperation::mev(Point(5.0,-2.0,-6.0),v26,through_inner_loop2);
    pVertex v30=v26_to_v30->end_v;

    pHalfEdge v27_to_v31=EulerOperation::mev(Point(9.0,-2.0,-6.0),v27,through_inner_loop2);
    pVertex v31=v27_to_v31->end_v;

    pHalfEdge v28_to_v32=EulerOperation::mev(Point(9.0,2.0,-6.0),v28,through_inner_loop2);
    pVertex v32=v28_to_v32->end_v;

    pLoop through_inner_left_loop2=EulerOperation::mef(v29,v30,through_inner_loop2);
    pLoop through_inner_up_loop2=EulerOperation::mef(v30,v31,through_inner_loop2);
    pLoop through_inner_right_loop2=EulerOperation::mef(v31,v32,through_inner_loop2);
    pLoop through_inner_bottom_loop2=EulerOperation::mef(v32,v29,through_inner_loop2);
    pLoop through_front_loop2=solid->FindLoopByStartVAndEndV(v9,v8);
    EulerOperation::kfmrh(through_inner_loop2->l_face,through_front_loop2->l_face);

    pLoop through_left_loop=solid->FindLoopByStartVAndEndV(v2,v1);
    pHalfEdge bridge3=EulerOperation::mev(Point(-10.0,2.0,9.0),v1,through_left_loop);
    pVertex v33=bridge3->end_v;

    pHalfEdge v33_to_v34=EulerOperation::mev(Point(-10.0,-2.0,9.0),v33,through_left_loop);
    pVertex v34=v33_to_v34->end_v;

    pHalfEdge v34_to_v35=EulerOperation::mev(Point(-10.0,-2.0,7.0),v34,through_left_loop);
    pVertex v35=v34_to_v35->end_v;

    pHalfEdge v35_to_v36=EulerOperation::mev(Point(-10.0,2.0,7.0),v35,through_left_loop);
    pVertex v36=v35_to_v36->end_v;

    pLoop through_right_inner_loop=EulerOperation::mef(v33,v36,through_left_loop);
    pLoop through_left_inner_loop=EulerOperation::kemr(v1,v33,through_left_loop);
    swap(through_left_loop,through_left_inner_loop);

    pHalfEdge v33_to_v37=EulerOperation::mev(Point(10.0,2.0,9.0),v33,through_right_inner_loop);
    pVertex v37=v33_to_v37->end_v;

    pHalfEdge v34_to_v38=EulerOperation::mev(Point(10.0,-2.0,9.0),v34,through_right_inner_loop);
    pVertex v38=v34_to_v38->end_v;

    pHalfEdge v35_to_v39=EulerOperation::mev(Point(10.0,-2.0,7.0),v35,through_right_inner_loop);
    pVertex v39=v35_to_v39->end_v;

    pHalfEdge v36_to_v40=EulerOperation::mev(Point(10.0,2.0,7.0),v36,through_right_inner_loop);
    pVertex v40=v36_to_v40->end_v;

    pLoop through_inner_left=EulerOperation::mef(v37,v38,through_right_inner_loop);
    pLoop through_inner_up=EulerOperation::mef(v38,v39,through_right_inner_loop);
    pLoop through_inner_right=EulerOperation::mef(v39,v40,through_right_inner_loop);
    pLoop through_inner_bottom=EulerOperation::mef(v40,v37,through_right_inner_loop);
    pLoop through_right_loop=solid->FindLoopByStartVAndEndV(v12,v11);
    EulerOperation::kfmrh(through_right_inner_loop->l_face,through_right_loop->l_face);

    return solid;
}

void PrintSolid(const pSolid solid)
{
    auto face_num=solid->GetFaceNum();
    std::cout<<"face num is: "<<face_num<<std::endl;
    auto face=solid->s_face;
    for(int i=0;i<face_num;i++,face=face->next_f){
        std::cout<<"face id is: "<<face->id<<std::endl;
        auto loop_num=face->GetLoopNum();
        auto loop=face->f_loop;
        std::cout<<"face "<<i+1<<"'s loop num is: "<<loop_num<<std::endl;
        for(int j=0;j<loop_num;j++,loop=loop->next_l){
            auto he_num=loop->GetEdgeNum();
            std::cout<<"loop "<<j+1<<"'s edge num is: "<<he_num<<std::endl;
            auto he=loop->l_halfedge;
            do{
                auto p1=he->start_v->point;
                auto p2=he->end_v->point;
                std::cout<<*p1<<" "<<*p2<<std::endl;
                he=he->next_he;
            }while(he!=loop->l_halfedge);
        }
    }
}