#include "Matrix.h"


int main(void){

    Matrix A({{1,1,1},{3,2,1}});
    Matrix B({{2,83},{1,3},{8,69}});
    std::cout<<A<<B<<A*B;
    return EXIT_SUCCESS;
};