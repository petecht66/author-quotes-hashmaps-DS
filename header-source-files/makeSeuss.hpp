

#ifndef MAKESEUSS_HPP
#define MAKESEUSS_HPP

#include "hashMap.hpp"
#include <iostream>
using namespace std;

class makeSeuss {
    hashMap *ht;
    string fn; // file name for input (“DrSeuss.txt”)
    string newfile; // name of output file
public:
    makeSeuss(string file,string newf,bool h1, bool c1);
    void readFile();
    void writeFile();
};

#endif MAKESEUSS_HPP