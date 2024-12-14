 #include "Cells.h"
#include "Grid.h"
#include <iostream>
int main(int argc, char const *argv[])
{
    Grid A(2,VOID,DEAD);
    std::cout<<A<<std::endl;
    A.ChangeCell(0,0,ALIVE);
    std::cout<<A<<std::endl;
    A.step();
    std::cout<<A<<std::endl;
    return 0;
}
