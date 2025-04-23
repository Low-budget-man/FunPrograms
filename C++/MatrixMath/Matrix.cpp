
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

// Function to calculate the determinant using Laplace expansion (for smaller matrices)
MatrixType Matrix::det(void) {
    if (N != M) {
        throw runtime_error("Determinant can only be calculated for square matrices.");
    }
    if (N == 1) {
        return Data[0][0];
    }
    if (N == 2) {
        return Data[0][0] * Data[1][1] - Data[0][1] * Data[1][0];
    }
    
    MatrixType result = 0;
    for (uint16_t i = 0; i < N; ++i) {
        // Create a submatrix by removing the first row and the current column
        Matrix submatrix(N - 1, N - 1);
        for (uint16_t j = 1; j < N; ++j) {
            uint16_t colIndex = 0;
            for (uint16_t k = 0; k < N; ++k) {
                if (k == i) continue;
                submatrix.Data[j - 1][colIndex] = Data[j][k];
                ++colIndex;
            }
        }
        
        // Calculate the determinant of the submatrix and add to the result
        MatrixType cofactor = (i % 2 == 0) ? Data[0][i] : -Data[0][i];
        result += cofactor * submatrix.det();
    }
    
    return result;
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
        throw runtime_error("Matrix operator +, matrixes incompatible sizes");
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
        throw runtime_error("Matrix operator -, matrixes incompatible sizes");
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
        throw runtime_error("Matrix operator *, matrixes incompatible sizes");
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
    Matrix B({{0.8147,    0.1576,    0.6557,    0.7060,    0.4387,    0.2760,    0.7513,    0.8407,    0.3517,    0.0759},
    {0.9058,    0.9706,    0.0357,    0.0318,    0.3816,    0.6797,    0.2551,    0.2543,    0.8308,    0.0540},
    {0.1270,    0.9572,    0.8491,    0.2769,    0.7655,    0.6551,    0.5060,    0.8143,    0.5853,    0.5308},
    {0.9134,    0.4854,    0.9340,    0.0462,    0.7952,    0.1626,    0.6991,    0.2435,    0.5497,    0.7792},
    {0.6324,    0.8003,    0.6787,    0.0971,    0.1869,    0.1190,    0.8909,    0.9293,    0.9172,    0.9340},
    {0.0975,    0.1419,    0.7577,    0.8235,    0.4898,    0.4984,    0.9593,    0.3500,    0.2858,    0.1299},
    {0.2785,    0.4218,    0.7431,    0.6948,    0.4456,    0.9597,    0.5472,    0.1966,    0.7572,    0.5688},
    {0.5469,    0.9157,    0.3922,    0.3171,    0.6463,    0.3404,    0.1386,    0.2511,    0.7537,    0.4694},
    {0.9575,    0.7922,    0.6555,    0.9502,    0.7094,    0.5853,    0.1493,    0.6160,    0.3804,    0.0119},
    {0.9649,    0.9595,    0.1712,    0.0344,    0.7547,    0.2238,    0.2575,    0.4733,    0.5678,    0.3371}});
    A.det();
    std::cout<<A<<A.det()<<'\n';
    std::cout<<B<<B.det()<<'\n';
    return EXIT_SUCCESS;
    
};
#endif
