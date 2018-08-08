#include "Matrix.h"
#include "Math.h"
#include <iostream>
#include <cmath>
#include <cstdlib> 



double Math::rowMean(const Matrix& m){
	double sum = Math::sum(m);
	return sum / (double)(m.cols());
}

Matrix Math::mean(const Matrix m){
	Matrix k(1,m.cols());
    for(int i=0; i<m.cols(); i++){
    	double sum = 0, n = 0;
    	for(int j=0; j<m.rows(); j++){
    		if(m(j,i)!=-1){
    			sum += m(j,i);
    			n++;
    		}
    	}
    	if(n<0.0000001) k(0,i)= 0;
    	else k(0,i)=1.0*sum/n;
	}
	return k;
}

double Math::vectorRange(const Matrix& m){
	if(!m.rows()){
		std::cout << "Empty Matrix-- Cannot find range\n";
		exit(1);
	}
	double max = m(0), min = m(0);
	for(int i=1, l=m.rows(); i<l; i++){
		if(m(i) > max) max = m(i);
		if(m(i) < min) min = m(i);
	}
	return max - min;
}


Matrix Math::range(const Matrix m){
	Matrix r(1,m.cols());
	for(int i=0, l=m.cols(); i<l; i++){
		r(0,i) = Math::vectorRange(m.getColumn(i));
	}
	return r;
}

void Math::scale(Matrix& m){
	Matrix k = Math::mean(m);
	Matrix r = Math::range(m);
	for(int i=0;i<m.rows();i++){
		for(int j=0;j<m.cols();j++){
			m(i,j) = (m(i,j) - k(0,j))/r(0,j);
		}
	}
}

double Math::sigmoid(const double& x){
	return (1.0/(1.0+pow(exp,-x)));
}

Matrix Math::sigmoid(const Matrix m){
	Matrix k(m.rows(),m.cols());
	for(int i=0;i<m.rows();i++){
		for(int j=0;j<m.cols();j++){
			k(i,j)=Math::sigmoid(m(i,j));
		}
	}
	return k;
}

Matrix Math::log(const Matrix m, double b){
	b = ::log(b);
	Matrix ans(m.rows(), m.cols());
	for(int i=0, r=m.rows(); i<r; i++){
		for(int j=0, c = m.cols(); j<c; j++){
			ans(i,j) = ::log(m(i,j))/b;
		}
	}
	return ans;
}

double Math::sum(const Matrix m){
	double sum=0;
	for(int i=0;i<m.rows();i++){
		for(int j=0;j<m.cols();j++){
			sum += m(i,j);
		}
	}
	return sum;
}

