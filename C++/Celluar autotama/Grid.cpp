#include "Grid.h"
#include "Cells.h"
#include <iostream>
//#define test


Grid::Grid(uint16_t size ,CellStates Gridborder ,CellStates startingstate){
    gridsize = size;
    edge.CurrentState = Gridborder;
    universe = new Cell*[size];
    for (uint16_t i = 0; i < size; i++)
    {
        universe[i] = new (startingstate) Cell[size];
        for (uint16_t j = 0; j < size; j++)
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

Grid::~Grid(){
    for (uint16_t i = 0; i < gridsize; i++)
    {
        delete[] universe[i];
    }
    delete[] universe;
}

void Grid::step(){
    //very slow update algo can speed up later
    for (uint16_t i = 0; i < gridsize; i++){
        for (uint16_t j = 0; j < gridsize; j++){
            universe[i][j].CellBehavior();
        }
    }
    for (uint16_t i = 0; i < gridsize; i++){
        for (uint16_t j = 0; j < gridsize; j++){
            universe[i][j].Update();
        }
    }
}







// operators
std::ostream &operator<<(std::ostream &os, const Grid &Gr)
{
    for (uint16_t i = 0; i < Gr.gridsize; i++)
    {
        os << "[";
        for (uint16_t j = 0; j < Gr.gridsize; j++)
        {
          os<<Gr.universe[i][j];
          if (j<Gr.gridsize-1)
          {
            os<<',';
          }
             
        }
        os << "]\n";
    }
    
    return os;
}





#ifdef test
int main()
{
    std::cout<<"HI"<<std::endl;;
    Grid Life;
    std::cout<<"BYE"<<std::endl;;
    return 0;
}


#endif