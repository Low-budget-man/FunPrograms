#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
template <typename T>
/*
A matirx as the ones seen in linear algerbra can be made with any type however all types that these matrixes become
need to be able to react to all of the math operators + - * /
*/
class Matrix
{
    private:
        std::vector <std::vector<int>> elements;
    public:
    Matrix(){
        elements[0][0] = 3; 
    }
    ~Matrix(){

    }
};
#endif 