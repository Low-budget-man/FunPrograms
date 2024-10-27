#ifndef ENTITY_H
#define ENTITY_H
#include <stdint.h>
class entity
{
private:
    int HP = 10;
    int Cords[2]; //[x,y]
public:
    // constructors ----------------------------------
    entity(int x=0,int y=0);
    // destructors -----------------------------------
    ~entity();

    // class functions
    void move(int x = 0, int y =0);
    int* getPostion(void);
    void HPupdate(int input);
    int GetHP(void);

};
   

#endif
