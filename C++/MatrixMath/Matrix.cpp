
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
//#define MATRIX_TEST

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
Matrix::Matrix(vector<vector<MatrixType>> input){
    Data = input;
    N = input.size();
    M = input[0].size();
}
Matrix::~Matrix(){
    ;
}
void Matrix::T(){
    // this is slow and not the best with memory 
    // can improve later
    Matrix Transpose(M,N);
    for (uint16_t i = 0; i < N; i++)
    {
        for (uint16_t j = 0; j < M; j++)
        {
            Transpose.Data[j][i] = Data[i][j];
        }
        
    }
    this = Transpose;
    
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
Matrix operator+(const Matrix& M1, const Matrix& M2){
    if(M1.N != M2.N || M1.M != M2.M){
        throw range_error("Matrix operator +, matrixes incompatible sizes");
    }
    Matrix out(M1);
    for (uint16_t i = 0; i < M1.N; i++)
    {
        for (uint16_t j = 0; j < M1.M; j++)
        {
            out.Data[i][j] += M2.Data[i][j];
        }
    }
    return out;
    
}
Matrix operator*(const Matrix& M1, const MatrixType scaler){
    Matrix out(M1);
    for (uint16_t i = 0; i < M1.N; i++)
    {
        for (uint16_t j = 0; j < M1.M; j++)
        {
            out.Data[i][j] *= scaler;
        }
    }
    return out;
}
Matrix operator*(const MatrixType scaler, const Matrix& M1){
    return M1 * scaler;
}

Matrix operator*(const Matrix& M1, const Matrix& M2){
    // cout << "M1 size = "<<M1.N<<", "<<M1.M<<"\nM2 size = "<<M2.N<<", "<<M2.M<<"\n";
    if(M1.M != M2.N){
        throw range_error("Matrix operator *, matrixes incompatible sizes");
    }
    uint16_t Loop = M1.M;
    Matrix out(M1.N,M2.M);
    for (uint16_t i = 0; i < out.N; i++)
    {
        for (uint16_t j = 0; j < out.M; j++)
        {
            for (size_t l = 0; l < Loop; l++)
            {
                out.Data[i][j] += M1.Data[i][l]*M2.Data[l][j];
            }
            
        }
    }
    return out;
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
    if (mat.N ==0 || mat.M == 0)
    {
        os<<"[]\n";
    }
    else{
        for (uint16_t i = 0; i < mat.N; i++)
        {
            os << '[';
            for (uint16_t j = 0; j < mat.M; j++)
            {
                os << mat.Data[i][j];
                if (j <mat.M-1)
                {
                    os<<", ";
                }
                
            }
            os << ']';
            os << '\n';
        }
    }
    return os;
}
#ifdef MATRIX_TEST
//tests go here
int main(void){

    Matrix A;
    Matrix B(5,3);
    Matrix D = B+100;
    Matrix E;
    Matrix F(10,5);
    E = 2+D;
    A = D+E;
    A = F+D;

    cout<<A<<B<<D<<E;
    return EXIT_SUCCESS;
};
#endif