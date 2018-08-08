#ifndef _CSV_H
#define _CSV_H


#include "Matrix.h"
#include <unordered_map>
#include <string>

std::unordered_map<std::string, Matrix> read_csv(std::string file);
bool isZero(std::string n);

#endif