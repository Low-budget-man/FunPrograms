
/* 
 * File:   Matrix.h
 * Author: Cooper Cantrell
 * Created on 3/23/2025
 * File does matrix math with floats 
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/
#include "Matrix.h"
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define MATRIX_TEST

/*******************************************************************************
 * PRIVATE TYPEDEFS                                                            *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTIONS/CLASSES                                                   *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTIONS FUNCTIONS                                                  *
 ******************************************************************************/
using namespace std;

Matrix::Matrix(){
    N = 0;
    M = 0;
    // I dont think clearing is needed but this is for safty
    for (uint16_t i = 0; i < Data.size(); i++)
    {
        Data[i].clear();
        Data[i].shrink_to_fit();
    }
    Data.clear();
    Data.shrink_to_fit();
     
}

Matrix::Matrix(uint16_t n,uint16_t m){
    N=n;
    M=m;
    Data.resize(n);
    for (uint16_t i = 0; i < n; i++)
    {
        Data[i].assign(m,0);
    }
    
}

Matrix::Matrix(const Matrix& Ma){
    Data = Ma.Data;
    M = Ma.M;
    N = Ma.N;
}

Matrix::~Matrix(){
    ;
}

Matrix operator+(const Matrix& mat, const MatrixType& scaler){
    Matrix out(mat);
    for (uint16_t i = 0; i < mat.Data.size(); i++)
    {
        for (uint16_t j = 0; j < mat.Data[i].size(); j++)
        {
            out.Data[i][j] +=  scaler;
        }
        
    }
    return out;
    
}

Matrix operator+(const MatrixType& scaler, const Matrix& mat){
    return  mat+scaler;
}

Matrix& Matrix::operator=(const Matrix& other){
    if(this != &other){
        this->Data = other.Data;
        this->M = other.M;
        this->N = other.N;
    }
    return *this;
}
ostream& operator<<(ostream& os, const Matrix& mat)
{
    os << "[\n";
    for (uint16_t i = 0; i < mat.N; i++)
    {
        for (uint16_t j = 0; j < mat.M; j++)
        {
            os << mat.Data[i][j] << ", ";
        }
        
        os << '\n';
    }
    
    os << "]\n";
    return os;
}
#ifdef MATRIX_TEST
//tests go here
int main(void){

    Matrix A;
    Matrix B(5,3);
    Matrix D = B+100;
    Matrix E;
    E = 2+D;
    cout<<A<<B<<D<<E;
    return EXIT_SUCCESS;
};
#endif