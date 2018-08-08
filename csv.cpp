#include "Matrix.h"
#include "csv.h"
#include "Math.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <unordered_map>
const double epsilon = 0.0000000001;

bool isZero(std::string n){
    for(int i=0, l=n.size(); i<l; i++ )
        if(n[i]!='0' && n[i] != '.')
            return false;
    return true;
}

std::unordered_map<std::string, Matrix> read_csv(std::string file){
    std::unordered_map<std::string, Matrix> mat;
    char * s = new char[40960];
    std::fstream f(file.c_str());
    int row = 0;
    f.getline(s, 40960);
    std::string p_name, name;
    while(f.getline(s, 40960)){
        std::stringstream in(s);
        std::string num;
        p_name = name;
        std::getline(in, name, ',');

        //new state found
        if(mat.find(name)==mat.end()){
            if(p_name!=name && p_name!=std::string()){
                if(row!=115){
                    Matrix update(row, 12);
                    for(int i=0; i<row; i++){
                        for(int j=0; j<12; j++)
                            update(i,j) = mat[p_name](i,j);
                    }
                    mat[p_name] = update;
                }
            }
            mat[name] = Matrix(115, 12, -1);
            row = 0;
        }

        std::getline(in, num, ',');
        int col = 0;
        while(col < 12){
            std::getline(in, num, ',');
            if(isZero(num)) mat[name](row,col) = 0;
            else{
                double n = atof(num.c_str());
                if(n<epsilon) mat[name](row,col) = -1;
                else mat[name](row,col) = n;
            }
            col++;
        }
        row++;
    }


    //fill empty data points with column mean
    for(std::unordered_map<std::string, Matrix>::iterator it = mat.begin(); it!=mat.end(); it++){
       Matrix& m = it->second;
       Matrix mean = Math::mean(m);
       for(int i = 0, r = m.rows(); i< r; i++){
            for(int j=0, c = m.cols(); j< c; j++){
                if(m(i,j)==-1) m(i, j) = mean(0, j);
            }
       }
    }

    f.close();
    delete[] s;
    return mat;
}

/*
int main(){
    std::unordered_map<std::string, Matrix> m = read_csv("rainfall_in_india_1901-2015.csv");
    for(std::unordered_map<std::string, Matrix>::iterator it = m.begin(); it!=m.end(); it++){
        std::cout << it->first << '\n';
        it->second.show();
        std::cout << '\n';
    }
    m["ARUNACHAL PRADESH"].show();
}

*/