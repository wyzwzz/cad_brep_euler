//
// Created by wyz on 20-11-18.
//

#ifndef EULEROPERATION_CREATION_H
#define EULEROPERATION_CREATION_H
#include"euleroperation.h"

class Creation {
public:
    Creation()=delete;
    static pSolid CreateSolid();
    static pSolid CreateSolidZero();
    static pSolid CreateSolidEight();
    static pSolid CreateSolidZeroUseSweep();
    static pSolid CreateCompactSolid();
};


#endif //EULEROPERATION_CREATION_H
