#include "Grid.h"
#define test


Grid::Grid(uint16_t size ,CellStates Gridborder ,CellStates startingstate){
    
    edge.CurrentState = Gridborder;
    universe = new Cell*[size];
    for (size_t i = 0; i < size; i++)
    {
        universe[i] = new Cell[size,startingstate];
        for (size_t j = 0; j < size; j++)
        {
            universe[i][j].CurrentState = startingstate;
            // border logic
            if (i == 0)
            {
                universe[i][j].NESWcells[3] = &edge;
            }
            if (j == 0)
            {
                universe[i][j].NESWcells[0] = &edge;
            }
            if (i == (size-1))
            {
                universe[i][j].NESWcells[1] = &edge;
            }
            if (j==(size-1))
            {
                universe[i][j].NESWcells[2] = &edge;
            }
            // now fill out rest of connections
            if (universe[i][j].NESWcells[0] == nullptr)
            {
                universe[i][j].NESWcells[0] = &universe[i][j-1];
            }
            if (universe[i][j].NESWcells[1] == nullptr)
            {
                universe[i][j].NESWcells[1] = &universe[i+1][j];
            }
            if (universe[i][j].NESWcells[2] == nullptr)
            {
                universe[i][j].NESWcells[2] = &universe[i][j+1];
            }
            if (universe[i][j].NESWcells[3] == nullptr)
            {
                universe[i][j].NESWcells[3] = &universe[i-1][j];
            }
        }
        
    }   
}

//Grid::~Grid(){
    //delete universe;
//}














#ifdef test
int main()
{
    std::cout<<"HI"<<std::endl;;
    Grid Life;
    std::cout<<"BYE"<<std::endl;;
    return 0;
}


#endif