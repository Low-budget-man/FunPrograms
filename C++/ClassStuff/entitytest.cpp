#include <iostream>
#include <stdio.h>
#include "entity.h"

using namespace std;
class player : public entity
{
private:
    UNSIGNED_TYPE status = 0;
public:
    player();
};
player::player(){
    HPupdate(90);
}

int main(int argc, char const *argv[])
{
    player a;
    cout << a.GetHP() << endl;
    return 0;
}

switch (expression)
{
case /* constant-expression */:
    /* code */
    break;

default:
    break;
}