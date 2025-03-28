
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
#include <cmath>
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
Matrix::Matrix(vector<vector<MatrixType>> input){
    Data = input;
    N = input.size();
    M = input[0].size();
}
Matrix::~Matrix(){
    ;
}
Matrix Matrix::T(){
    // this is slow and not the best with memory 
    // can improve later
    Matrix out(M,N);
    for (uint16_t i = 0; i < N; i++)
    {
        for (uint16_t j = 0; j < M; j++)
        {
            out.Data[j][i] = Data[i][j];
        }
        
    }
    return out;
}
MatrixType Matrix::det(void){
    // check to see if square
    if(M != N){
        throw range_error("Matrix function det, matrix must be square");
    }
    // following code is on the work provided by 
    // https://www.geeksforgeeks.org/cpp-program-for-determinant-of-a-matrix/
    static uint16_t DetTrack = 0;
    uint16_t depth = M - DetTrack;
    DetTrack++;
    Matrix submatrix(N,M);
    MatrixType Det = 0;
    if (depth == 1)
    {
        return Data[0][0];
    }
    else if (depth == 2)
    {
        return ((Data[0][0] * Data[1][1]) - (Data[1][0] * Data[0][1]));
    }
    else
    {
        for (uint16_t x = 0; x < depth; x++)
        {
            uint16_t subi = 0;
            for (uint16_t i = 1; i < depth; i++)
            {
                uint16_t subj = 0;
                for (uint16_t j = 0; j < depth; j++)
                {
                    if (j==x)
                    {
                        continue;
                    }
                    submatrix.Data[subi][subj] = Data[i][j];
                    subj++;
                }
                subi++; 
            }
            Det = Det + (pow(-1,x)*Data[0][x]*submatrix.det());
            
        }
    }
    DetTrack = 0;
    return Det;
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
Matrix operator- (const Matrix& mat, const MatrixType& scaler){
    Matrix out(mat);
    for (uint16_t i = 0; i < mat.Data.size(); i++)
    {
        for (uint16_t j = 0; j < mat.Data[i].size(); j++)
        {
            out.Data[i][j] -=  scaler;
        }
        
    }
    return out;
    
}
Matrix operator-(const MatrixType& scaler, const Matrix& mat){
    Matrix out(mat);
    for (uint16_t i = 0; i < mat.Data.size(); i++)
    {
        for (uint16_t j = 0; j < mat.Data[i].size(); j++)
        {
            out.Data[i][j] =  scaler - out.Data[i][j];
        }
        
    }
    return out;
}
Matrix operator-(const Matrix& M1, const Matrix& M2){
    if(M1.N != M2.N || M1.M != M2.M){
        throw range_error("Matrix operator -, matrixes incompatible sizes");
    }
    Matrix out(M1);
    for (uint16_t i = 0; i < M1.N; i++)
    {
        for (uint16_t j = 0; j < M1.M; j++)
        {
            out.Data[i][j] -= M2.Data[i][j];
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

    Matrix A({{1, 0, 2, -1},
        {3, 0, 0, 5},
        {2, 1, 4, -3},
        {1, 0, 5, 0}});
    A.det();
    std::cout<<A<<A.det()<<'\n';
    return EXIT_SUCCESS;
    
};
#endif