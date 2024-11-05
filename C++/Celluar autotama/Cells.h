#ifndef CELLS_CLASS_H
#define CELLS_CLASS_H
#include <iostream>
// static states IE states that never will change are less than 0
typedef enum 
{
    BARRIER = -2,
    VOID = -1,
    WALL = 0,
    EMPTY,
    DEAD,
    ALIVE,
}
CellStates;

class Cell
{
private:
    CellStates CurrentState;
    CellStates NextState;
    bool Sleeping; // save time by not checking neighbors if the neighbors did not update in last check 
    Cell* NESWcells[4];
    CellStates NeighborStates[4];
    void readNeighbor();

public:
    // class constructors 
    Cell(CellStates startstate = VOID);
//    Cell();
    // Class destructor
    ~Cell();
    // class functions edit functions -------------------------------------------------------------------------
protected:
    // given a dir and a pointer cell make give this cell Neighbors
    bool addNeighbor(Cell* Neighbor, const char dir);
    // updates the cell to the next cell
    void Update(void);
    // changes next state for next update
    void Changestate(CellStates newstate);
public:
    // will be overwritten by child classes default is game of life
    // will return false if any not fully defined behavior for all Neighbor
    bool CellBehavior(void);
    // operators ----------------------------------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream& os, const Cell& cb);
    static void* operator new[] (size_t size,CellStates startstate);
    void operator delete[](void* ptr);
    // Classes that can see inside
    friend class Grid;

};


#endif