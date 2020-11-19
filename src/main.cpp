#include <iostream>
#include"renderer.h"
extern void PrintSolid(const pSolid solid);
int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::vector<pSolid> solids;
    pSolid solid=Creation::CreateCompactSolid();
    //PrintSolid(solid);
    Renderer renderer(solid);
    renderer.Render();
    return 0;
}
