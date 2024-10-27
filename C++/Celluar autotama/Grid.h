#ifndef GRID_CLASS_H
#define GRID_CLASS_H
#include "Cells.h"
// an nxn grid of cells
class Grid
{
private:
    Cell edge;
    Cell** universe;
public:
    Grid(uint16_t size = 32,CellStates Gridborder = VOID,CellStates startingstate = EMPTY);
    //~Grid();
    // change a single cell on the grid
    bool ChangeCell(uint16_t x,uint16_t y,CellStates newstate);
    // steps the simulation 1 into the future
    void step();

};



#endif