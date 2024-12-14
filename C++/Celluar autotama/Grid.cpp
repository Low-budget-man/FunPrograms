#include "Grid.h"
#include "Cells.h"
#include <iostream>
//#define test

//private class functions
void Grid::Link(Cell* inp,uint16_t x, uint16_t y){
    Cell* Neighbor;
    // North
    if (y==0)
    {
        Neighbor = &edge;
    }
    else
    {
        Neighbor = &universe[x][y-1];
    }
    inp->NESWcells[0] = Neighbor;
    // East
    if (x==gridsize-1)
    {
        Neighbor = &edge;
    }
    else
    {
        Neighbor = &universe[x+1][y];
    }
    inp->NESWcells[1] = Neighbor;
    // South
    if (y==gridsize-1)
    {
        Neighbor = &edge;
    }
    else
    {
        Neighbor = &universe[x][y+1];
    }
    inp->NESWcells[2] = Neighbor;
    // West
    if (x==0)
    {
        Neighbor = &edge;
    }
    else
    {
        Neighbor = &universe[x-1][y];
    }
    inp->NESWcells[3] = Neighbor;
    } 

// Creation and deleation
Grid::Grid(uint16_t size ,CellStates Gridborder ,CellStates startingstate){
    gridsize = size;
    edge.CurrentState = Gridborder;
    universe = new Cell*[size];
    for (uint16_t i = 0; i < size; i++)
    {
        universe[i] = new Cell[size];
        for (uint16_t j = 0; j < size; j++)
        {
            universe[i][j].CurrentState = startingstate;
            Link(&universe[i][j],j,i);
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

// public class functions

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

bool Grid::ChangeCell(uint16_t x,uint16_t y,CellStates newstate){
    y = y%(gridsize);
    x = x%(gridsize);
    universe[y][x].CurrentState = newstate;
    return true;
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