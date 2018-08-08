#include "Matrix.h"
#include "Math.h"
#include "csv.h"
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

typedef std::pair<double, Matrix> P;
double similarilty(Matrix l, Matrix x, double sigma){ //gaussian kernal
    Matrix diff = l-x;
    double p = (diff.transpose() * diff)(0)/(2*sigma*sigma);
    return pow(Math::exp,-p);
}

Matrix makeFeatureMatrix(Matrix X, double sigma=1, Matrix L = Matrix(0)){

    if(!L.rows()) L = X;

    Matrix f(X.rows(), L.rows());
    for(int i=0, r=X.rows(), c = L.rows(); i<r; i++){
        for(int j=0; j<c; j++){
            f(i,j) = similarilty(X.getRow(i).transpose(), L.getRow(j).transpose(), sigma);
        }
    }
    return f;
}


P cost(Matrix& theta, Matrix& X, Matrix& y, double lambda){
    int m = y.rows();
    double J = 0;
    Matrix h = (X*theta-y);
    Matrix h1(h.rows());

    for(int i=0; i<h.rows(); i++){
        h1(i) = h(i)*h(i);
    }
    //std::cout<<"cost matrix: ";
   // h1.show();
    J = Math::sum(h1);
    Matrix theta2 = theta * theta.transpose();
    double theta_sq_sum = theta2(0)-1;
    J += (lambda/2)*theta_sq_sum;
    J /=m;

    Matrix grad = X.transpose() * (h-y);

    for(int i=1; i<grad.rows(); i++){
        grad(i) = (grad(i) + lambda*theta(i))/m;
    }

    return std::make_pair(J, grad);
}

Matrix gradientDescent(Matrix& X, Matrix& y, Matrix theta, double lambda =1, int iters=500){
    double p_cost = cost(theta, X, y, lambda ).first;
    //std::cout << "INitial cost: ";cost(theta, X, y, lambda ).second.show();
    //std::cout <<"initia cost: " << p_cost<<  " gradientDescent called with: X:-";
    //X.show();
    //y.show();
    double alpha = 0.5;
    Matrix p_theta = theta;
    while(iters--){
        P t = cost(theta, X, y, lambda );
        if(p_cost < t.first){
            theta = p_theta;
            alpha /=2.0;
        }
        p_cost = t.first;
        p_theta = theta;
        //if(iters%250==0) std::cout << "Cost: " << t.first << ' ';
        theta = theta - t.second*alpha;
        if(iters%500==0){
            std::cout << ".";
            std::cout.flush();
        }
    }
    std::cout << '\n';
    return theta;
}

Matrix predict_rain(Matrix data){
    Matrix predicted_values(1,12);

    for(int month=0; month<12; month++){
        Matrix X(data.rows()-1, 12), y(data.rows()-1, 1);
        for(int i=0; i<data.rows()-1; i++){
            for(int j=0; j<12; j++){
                if(j==month){
                    y(i) = data(i+1,j);
                }
                X(i,j) = data(i,j);
            }
        }

        Matrix F = X;
        Matrix mean_X = Math::mean(X);
        Matrix range_X = Math::range(X);
        Matrix mean_y = Math::mean(y);
        Matrix range_y = Math::range(y);
        Math::scale(y);
        Math::scale(F);
        Matrix scaled_X = F;
        F = makeFeatureMatrix(F,0.15); //make feature matrix

        F = F.append(Matrix::ones(F.rows()),0);
        Matrix theta = gradientDescent(F, y, Matrix::zeros(F.cols()), 0.1, 5000);

        //predict the value
        Matrix test = X.getRow(X.rows()-1);
        for(int i=0, r=test.rows(), c=test.cols(); i<r; i++){
            for(int j=0; j<c; j++){
                test(i,j) = (test(i,j) - mean_X(0,j) )/range_X(0,j);
            }
        }
        test = makeFeatureMatrix(test, 0.15, scaled_X);
        test = test.append(Matrix::ones(test.rows()),0);

        Matrix ans = test*theta;
        predicted_values(0,month) = (ans(0,0)*range_y(0,0))+mean_y(0,0);
    }

    return predicted_values;
}



int main(){
	Matrix data = Matrix("training.dat");
    //std::unordered_map<std::string, Matrix> mat = read_csv("rainfall_in_india_1901-2015.csv");
    //mat["JHARKHAND"].save("training.dat");
    predict_rain(data).save("predicted.dat");
    
}

