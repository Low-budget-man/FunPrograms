#include "entity.h"
#include <iostream>


// constructors ----------------------------------
entity::entity(int x,int y){
    Cords[0] = x;
    Cords[1] = y;  
}

// destructors -----------------------------------
entity::~entity(){
    ;
}


// class functions
void entity::move(int x, int y){
    Cords[0] += x;
    Cords[1] += y;
}
int* entity::getPostion(){
    return Cords;
}
void entity::HPupdate(int input){
    HP += input;
    if (HP < 0)
    {
        HP = 0;
    }
}
int entity::GetHP(){
    return HP;
}