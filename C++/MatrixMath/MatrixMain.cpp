#include "Matrix.h"


int main(void){

    Matrix A({{1,1,1},{3,2,1}});
    Matrix B({{2,83},{1,3},{8,69}});
    std::cout<<A<<'\n'<<B<<'\n'<<A*B<<'\n';
    B.T();
    std::cout<<A.T()<<'\n'<<B<<'\n';
    return EXIT_SUCCESS;
};