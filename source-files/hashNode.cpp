#include "hashNode.hpp"
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

hashNode::hashNode() { //constructor
    keyword = ""; //initialize keyword to empty string
    valuesSize = 0; //initialize array size to 0
    currSize = 0; //number of words to 0
    values = NULL; //values to NULL
}

hashNode::hashNode(string s) { //second constructor
    keyword = s; //keyword to input s
    valuesSize = 100; //array size to 100
    currSize = 0; //number of words to 0
    values = new string[valuesSize]; //create the array of size valuesSize
}

hashNode::hashNode(string s, string v) { //third constructor
    keyword = s; //keyword to input s
    valuesSize = 100; //array size to 100
    currSize = 1; //number of words is now 1
    values = new string[valuesSize]; //create the array of size valuesSize
    values[0] = v; //set first value to v
}

void hashNode::addValue(string v) {
    if (currSize >= valuesSize) {
        dblArray(); //double array
    }
    values[currSize] = v; //add v to values
    currSize++; //increase number of words by 1

    if (currSize >= valuesSize) { //second check after increasing currSize
        dblArray(); //double array
    }
}

void hashNode::dblArray() {
    valuesSize = valuesSize * 2; //double size of values array
    string* tempValues = new string[valuesSize]; //create a temporary array to store values
    for (int i = 0; i < currSize; i++) {
        tempValues[i] = values[i]; //copy over all values
    }
    delete[] values; //deallocate old array
    values = tempValues; //set values to temporary array
}

string hashNode::getRandValue() {
    if (currSize == 0) {
        return ""; //return empty string if no values in value array
    }
    int rIndex = rand() % currSize; //gets random index from currSize
    return values[rIndex]; //returns random string
}