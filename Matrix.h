/*
    *constructors:
    Matrix(int r=0, int c=0)---
        creates a zero initialized matrix of order rXc
    Matrix(double** m, int r, int c)---
        create a Matrix object of order rXc, as repreented by double** pointer m;
    Matrix(const Matrix& m)---
        copy contructer: creates copy of the object 
    Matrix(string File)---
    	loads the file specified by File

    operator(a)
        returns first element of row a
    operator(a, b)
        returns bth element of row a
        
    operator= ---- a=b
        makes matrix 'a' a copy of 'b'

    transpose---
        return Matrix object that is tranpose of itself.

    append(Matrix m)---
        appends matrix m to the end of itself

    append(Matrix m, int n)---
        appends matrix m before the given column specified by n

    getColumn()---
        returns a Matrix of order col X 1, containing first column
    getColumn(int n)---
        returns a Matrix of order col X 1, containing nth column

    getRow()---
        returns a Matrix of order 1 X row, containing first row
    getRow(int n)---
        returns a Matrix of order 1 X row, containing nth row
    
    static eye(int n)---
        returns identity matrix of order nXn

    static zeros(inta, int b)---
        returns zero matrix of order aXb

	static ones(inta, int b)---
        returns one-matrix of order aXb
    */

#ifndef _MATRIX_H
#define _MATRIX_H

#include <string>

class Matrix{
    int row, col;
    double** a;

public:

    Matrix(int r=1, int c=1, double v=0);
    //Matrix(double** m, int r, int c);
    Matrix(const Matrix& m);
    Matrix(std::string file);
    ~Matrix();
	
    double& operator()(int r, int c=0);
	const double& operator()(int r, int c=0) const;
    Matrix operator+ (const double);
    Matrix operator-(const double);
    Matrix operator*(const double);
    void operator=(const  Matrix& m);
    Matrix operator*(const Matrix& m);
    Matrix operator+(const Matrix& m);
    Matrix operator-(const Matrix& m);
    
    Matrix transpose()const;
    Matrix append(Matrix m, int r=-1);
    Matrix getColumn(int c=0)const;
    Matrix getRow(int r=0)const;
    

    int rows() const; //returns column count
    int cols() const;  //returns row count
    
    static Matrix eye(int r=1);
    static Matrix zeros(int r=1, int c=1, int v=0);
    static Matrix ones(int r=1, int c=1, int v=1);
    
    void save(std::string file)const;
    void show()const;
};

Matrix operator*(const double a, const Matrix& m);

#endif