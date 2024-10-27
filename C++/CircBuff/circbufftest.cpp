#include <iostream>
#include "circbuff.h"
int main(int argc, char const *argv[])
{
    circbuff<int> a(3);
    circbuff<int> b(7);
    circbuff<int> c;
    c = a+b;

}
