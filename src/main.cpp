#include <iostream>
#include"renderer.h"
/*
 * L键用于切换线框模式和shader模式
 * -> 用于切换当前绘制的实体
 * Q和E控制相机上下
 * W和S控制相机前后
 * A和D控制相机左右
 * 鼠标控制相机朝向
 * 按Esc退出程序
 */
int main()
{
    std::vector<pSolid> solids;
    //solid 0 是一个长方体 完全使用欧拉操作生成，没有使用扫掠操作
    pSolid solid_0=Creation::CreateSolid();solids.push_back(solid_0);
    //solid 1 是一个带一个孔的长方体 完全使用欧拉操作生成，没有使用扫掠操作
    pSolid solid_1=Creation::CreateSolidZero();solids.push_back(solid_1);
    //solid 2 是一个带两个孔的长方体 完全使用欧拉操作生成，没有使用扫掠操作
    pSolid solid_2=Creation::CreateSolidEight();solids.push_back(solid_2);
    //solid 3 是一个带一个孔的长方体 使用了扫掠操作
    pSolid solid_3=Creation::CreateSolidZeroUseSweep();solids.push_back(solid_3);
    //solid 4 是一个带四个孔的多面体 综合使用了欧拉操作和扫掠操作
    pSolid solid_4=Creation::CreateCompactSolid();solids.push_back(solid_4);

    Renderer renderer(std::move(solids));
    renderer.Render();

    return 0;
}
