/* 
 * File:   Matrix.h
 * Author: Cooper Cantrell
 * Created on 3/23/2025
 * File does matrix math with floats 
 */
#ifndef MATRIX_H  // <- This should be changed to your own guard on both
#define MATRIX_H //    of these lines

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/
#include <iostream>
#include <stdint.h>
#include <vector>
using namespace std;

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#define MatrixType float

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC Class PROTOTYPES                                                  *
 ******************************************************************************/
class Matrix
{
private:
    vector<vector<MatrixType>> Data;
    uint16_t N,M;
public:
    // constructors and destructors
    // empty
    Matrix();
    // size filled with all 0
    Matrix(uint16_t n,uint16_t m);
    Matrix(const Matrix& Ma);
    Matrix(vector<vector<MatrixType>> input);
    ~Matrix();
    // Matrix Functions
    Matrix T(void);
    // operators
    // const addition
    // scalers
    friend Matrix operator+ (const Matrix& mat, const MatrixType& scaler);
    friend Matrix operator+(const MatrixType& scaler, const Matrix& mat);
    // matrix
    friend Matrix operator+(const Matrix& M1, const Matrix& M2);
    // subtraction 
    friend Matrix operator- (const Matrix& mat, const MatrixType& scaler);
    friend Matrix operator-(const MatrixType& scaler, const Matrix& mat);
    // matrix
    friend Matrix operator-(const Matrix& M1, const Matrix& M2);
    // mult scalers
    friend Matrix operator*(const Matrix& M1, const MatrixType scaler);
    friend Matrix operator*(const MatrixType scaler, const Matrix& M1);
    //mult matrix very important
    friend Matrix operator*(const Matrix& M1, const Matrix& M2);
    // assignment
    Matrix& operator=(const Matrix& other);
    // display
    friend ostream& operator <<(ostream& os, const Matrix& display);
};




#endif 