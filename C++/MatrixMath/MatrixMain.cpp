#include "Matrix.h"


int main(void){

    Matrix A({{1,1,1},{3,2,1}});
    Matrix B({{2,83},{1,3},{8,69}});
    std::cout<<A<<'\n'<<B<<'\n'<<A*B<<'\n';
    Matrix Bt = B.T();
    Matrix A2 = A-2;
    Matrix AA = 2-A; 
    std::cout<<A2<<'\n'<<Bt-A<<'\n';
    return EXIT_SUCCESS;
};