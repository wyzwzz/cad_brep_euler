//
// Created by wyz on 20-11-13.
//

#ifndef EULEROPERATION_EULEROPERATION_H
#define EULEROPERATION_EULEROPERATION_H

#include"b-rep.h"
class EulerOperation {
public:
    EulerOperation()=delete;
    static pSolid mvfs(Point p,pVertex &v);
    static pHalfEdge mev(Point p,const pVertex v,const pLoop loop);
    static pLoop mef(const pVertex v1,const pVertex v2,pLoop main_loop);
    static pLoop kemr(const pVertex v1,const pVertex v2,pLoop loop);
    static void kfmrh(pFace del_face,pFace face);
    static pSolid sweep(pFace face,glm::vec3 move_vec);
};
void swap(pLoop& p1,pLoop& p2);

#endif //EULEROPERATION_EULEROPERATION_H
