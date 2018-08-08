/*
	contains a bunch of static routines to manipulate numerical data, espicially Matrices
	
	mean(double* , double* )--
		return the mean of array between [b,e)
		
	mean(const Matrix&)--
		 returns a row matrix containing mean of each column
		 
	scale(matrix& )--
		scales the matrix around mean
		
	sigmod(const double&)--
		returns sigmoid value of the number provided
		
	sigmoid(const Matrix&)--
		returns matrix containing element wise sigmoid

	sum(const Matrix& )--
		returns sum of all elements of a matrix
		
	log(const Matrix& , double b = 10)--
		returns a matrix containg element by logarithm with base b

*/

#ifndef _MYMATH_H
#define _MYMATH_H

class Math{
	static double rowMean(const Matrix& m);
	static double vectorRange(const Matrix& m);
public:
	static constexpr double exp = 2.7182818284590;
	static double mean(double *beg, double *end);
	static Matrix mean(const Matrix m);
	static void scale(Matrix &m);
	static Matrix range(const Matrix m);
	static double sigmoid(const double& x);
	static Matrix sigmoid(const Matrix m);
	static double sum(const Matrix m);
	static Matrix log(const Matrix m, double b = 10);
};



#endif

