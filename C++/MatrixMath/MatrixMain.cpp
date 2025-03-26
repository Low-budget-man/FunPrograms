#include "Matrix.h"


int main(void){

    Matrix A;
    Matrix B(5,3);
    Matrix D = B+100;
    Matrix E;
    Matrix F(10,5);
    Matrix blank;
    E = 2+D;
    A = D+E;
    //A = F+D;
    Matrix D4 = D*4.0;
    Matrix D5 = 5.0*D;
    cout<<A<<B<<D<<E;
    cout<<blank;
    return EXIT_SUCCESS;
};