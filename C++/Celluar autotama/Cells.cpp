#include <iostream>
#include "Cells.h"
#define TESTING
// private data and functions

const char CellChar[] = {
    '.',
    ' ',
    'x',
    'o',

};

void Cell::readNeighbor()
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            if (NESWcells[i] == nullptr)
            {
                NeighborStates[i] = VOID;
            }
            else
            {
                std::cout<<NESWcells[i]->CurrentState;
                //NeighborStates[i] = NESWcells[i]->CurrentState;
            }
        }
    }

// public functions
// Cell::Cell()
// {
//     CurrentState = EMPTY;
//     NextState = EMPTY;
//     Sleeping = true;
//     for (uint8_t i = 0; i < 4; i++)
//     {
//         NESWcells[i] = nullptr;
//         NeighborStates[i] = VOID;
//     }
// }
Cell::Cell(CellStates start)
{
    CurrentState = start;
    NextState = start;
    Sleeping = true;
    for (uint8_t i = 0; i < 4; i++)
    {
        NESWcells[i] = nullptr;
        NeighborStates[i] = VOID;
    }
}

Cell::~Cell()
{
}

bool Cell::addNeighbor(Cell *Neighbor, const char pos)
{
    switch (pos)
    {
    case 'N':
        NESWcells[0] = Neighbor;
        break;
    case 'E':
        NESWcells[1] = Neighbor;
        break;
    case 'S':
        NESWcells[2] = Neighbor;
        break;
    case 'W':
        NESWcells[3] = Neighbor;
        break;
    default:
        return false;
    }
    return true;
}

void Cell::Update()
{
    CurrentState = NextState;
}

void Cell::Changestate(CellStates newstate)
{
    NextState = newstate;
}

bool Cell::CellBehavior(){
    readNeighbor();
    uint8_t AliveBuds = 0;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (NeighborStates[i] == ALIVE)
        {
            AliveBuds++;
        }
        
    }
    
    switch (CurrentState)
    {
    case ALIVE:
        if(AliveBuds<2 || AliveBuds > 3){
            Changestate(DEAD);
        }
        break;
    case DEAD:
        if (AliveBuds == 3)
        {
            Changestate(ALIVE);
        }
        break;
    default:
        return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const Cell &cell)
{
    if (cell.CurrentState < 0)
    {
        throw std::invalid_argument("Cannot print Immutable Cells");
    }
    
    os << CellChar[cell.CurrentState];
    return os;
}

void* Cell::operator new[](size_t size){
    return malloc(size * sizeof(Cell)+1);  
}

void Cell::operator delete[](void* ptr){
    free(ptr);
    ptr = nullptr;
}