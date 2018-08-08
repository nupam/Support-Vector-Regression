#include "Matrix.h"
#include <iostream>
#include <cstdlib>   //exit(n)
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using std::cout;


Matrix::Matrix(std::string file){
	char * s = new char[10240];
	double temp;
	std::fstream f(file.c_str());
	std::vector<std::vector<double> > data;
	
	while(f.getline(s, 10240)){
		std::vector<double> row;
		std::stringstream in(s);
		while(in >> temp) row.push_back(temp);
		data.push_back(row);
	}
	
	if(!data.size() || !data[0].size()){
		row = col = 0;
		a = NULL;
		return;
	}
	
	row = data.size(); col = data[0].size();
	a = new double*[row];
    for(int i=0; i<row; i++) a[i] = new double[col];
	
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++) 
			a[i][j] = data[i][j]; 
	}
	
	f.close();
	delete[] s;
}


Matrix::Matrix(int r, int c, double v):row(r), col(c){
	if(!r){ //empty matrix
		col = 0;
		a = NULL;
		return;
	}
    a = new double*[r];
    for(int i=0; i<r; i++){
    	a[i] = new double[c];
    	for(int j=0; j<c; j++)
    		a[i][j] = v;	
    }
}

/*
Matrix::Matrix(double** m, int r, int c):row(r), col(c){
    a = new double*[row];
    for(int i=0; i<row; i++) a[i] = new double[col];
    for(int i=0; i<row; i++) for(int j=0; j<col; j++) a[i][j] = m[i][j];
}
*/

Matrix::Matrix(const Matrix& m){
    row=m.row, col=m.col;
    a = new double*[row];
    for(int i=0; i<row; i++) a[i] = new double[col];
    for(int i=0; i<row; i++) for(int j=0; j<col; j++) a[i][j] = m(i,j);
}

Matrix::~Matrix(){
    for(int i=0; i<row; i++) delete[] a[i];
    delete[] a;
}

int Matrix::rows()const {return row;}

int Matrix::cols()const {return col;}

double& Matrix::operator()(int r, int c){
    if(r>=row || r<0 || c>=col || c<0){
        cout << "Illegal member access of " << row << "X" << col;
        cout << "\nat (" << r <<',' << c <<')' <<std::endl;
        exit(1);
    }
    return a[r][c];
}


const double& Matrix::operator()(int r, int c) const {
    if(r>=row || r<0 || c>=col || c<0){
        cout << "Illegal member access of " << row << "X" << col;
        cout << "\nat (" << r <<',' << c <<')' <<std::endl;
        exit(1);
    }
    return a[r][c];
}

void Matrix::operator=(const Matrix& m){
    if(row != m.row || col != m.col){
        for(int i=0; i<row; i++) delete[] a[i];
        delete[] a;
        
        row = m.row ; col = m.col;
        a = new double*[row];
        for(int i=0; i<row; i++)
        	a[i] = new double[col];
    }

    for(int i=0; i<row; i++)
    	for(int j=0; j<col; j++)
    		a[i][j] = m.a[i][j];
    
}

Matrix Matrix::operator*(const Matrix& m){
    if(col!=m.row){
        cout << "Matrix Multiplication not possible\n" << row << 'X' << col;
        cout << " and " << m.rows() <<'X' << m.cols() <<std::endl;
        exit(1);
    }

    Matrix p(row, m.cols());

    for(int i=0; i<row; i++){
        for(int j=0; j<m.col; j++){
            for(int k=0; k<col; k++) p(i,j) += a[i][k]*m(k,j);
        }
    }

    return p;
}

Matrix Matrix::operator+(const Matrix& m){
    if(row !=m.row || col!=m.col){
        cout << "Matrix addition not possible\n" << row << 'X' << col;
        cout << " and " << m.rows() <<'X' << m.cols() <<std::endl;
        exit(1);
    }

    Matrix p(row, col);

    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            p(i,j) = a[i][j] + m(i,j);
        }
    }

    return p;
}

Matrix Matrix::operator-(const Matrix& m){
    if(row !=m.row|| col!=m.col){
        cout << "Matrix substraction not possible\n" << row << 'X' << col;
        cout << " and " << m.rows() <<'X' << m.cols() <<std::endl;
        exit(1);
    }

    Matrix p(row, col);

    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            p(i,j) = a[i][j] - m(i,j);
        }
    }

    return p;
}

Matrix Matrix::transpose()const{
    Matrix p(cols(), rows());
    for(int i=0; i<rows(); i++){
        for(int j=0; j<cols(); j++){
            p(j,i) = operator()(i,j);
        }
    }
    return p;
}

Matrix Matrix::append(Matrix m, int c){
	if(c==-1) c = col;
    if(c>col || c<0 || m.row != row){
        cout << "Illegal append operation in " << row << "X" << col;
        cout << "\nwith " << m.rows() <<'X' << m.cols() <<std::endl;
        exit(1);
    }

    Matrix p(row,m.cols()+col);
    for(int i=0; i<row; i++){
    	for(int j=0; j<c; j++) p(i,j) = a[i][j];
    }
    for(int i=0; i<row; i++){
    	for(int l = c+m.cols(), j=c; j<l; j++) p(i,j) = m(i,j-c);
    }
    for(int i=0; i<row; i++){
    	for(int l = p.cols(), j=c+m.cols(); j<l; j++)
    		p(i,j) = a[i][j-m.cols()];
    }
    
    return p;

}


Matrix Matrix::getColumn(int c)const{
    if(c>=cols() || c<0){
        cout << "Illegal member access of " << rows() << "X" << cols();
        cout << "\nat (r" <<',' << c <<')' <<std::endl;
        exit(1);
    }
    Matrix p(rows());
    for(int i=0; i<rows(); i++) p(i) = operator()(i,c);
    return p;
}

Matrix Matrix::getRow(int r)const{
    if(r>=rows() || r<0 ){
        cout << "Illegal member access of " << rows() << 'X' << cols();
        cout << "\nat (" << r <<',' <<"C)" <<std::endl;
        exit(1);
    }
    Matrix p(1, cols());
    for(int i=0; i<col; i++) p(0,i) = operator()(r,i);
    return p;
}

Matrix Matrix::eye(int r){
    Matrix p(r,r);
    for(int i=0; i<r; i++) p(i,i)=1;
    return p;
}

Matrix Matrix::zeros(int r, int c, int v){
    Matrix p(r,c);
    if(v){
        for(int i=0; i<r; i++){
            for(int j=0; j<c; j++){
                p(i,j) = v;
            }
        }   
    }
    return p;
}

Matrix Matrix::ones(int r, int c, int v){
    return zeros(r,c,v);
}

void Matrix::show() const{
	for(int i=0; i<row; i++) {
		for(int j=0;j<col; j++){
			cout <<std::setprecision(3)<< operator()(i,j) << "  ";		
		}
		cout <<'\n';
	}
	cout <<"\tOrder: "<< row << 'X' << col<<'\n';
}

void Matrix::save(std::string file) const{
	std::ofstream f(file.c_str());
	for(int i=0; i<rows(); i++) {
		for(int j=0;j<cols(); j++){
			f << operator()(i,j)<< ' ';		
		}
		f <<'\n';
	}
	f.close();
}

Matrix Matrix::operator*(const double num){
	Matrix ans(rows(), cols());
	for(int i=0, r = rows(), c = cols(); i<r; i++) for(int j=0; j<c; j++) ans(i,j) = a[i][j]*num;
	return ans;
}

Matrix Matrix::operator-(const double num){
	Matrix ans(rows(), cols());
	for(int i=0, r = rows(), c = cols(); i<r; i++) for(int j=0; j<c; j++) ans(i,j) = a[i][j]-num;
	return ans;
}
Matrix Matrix::operator+(const double num){
	Matrix ans(rows(), cols());
	for(int i=0, r = rows(), c = cols(); i<r; i++) for(int j=0; j<c; j++) ans(i,j) = a[i][j]+num;
	return ans;
}
