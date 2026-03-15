#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

hashMap::hashMap(bool hash1, bool coll1) { //only constructor
    h1 = hash1; //hash boolean
    c1 = coll1; //collision boolean
    numKeys = 0; //number of keys to 0
    collisionct1 = 0; //0 original collisions to start
    collisionct2 = 0; //0 secondary collisions to start
    first = ""; //first to empty string
    mapSize = 10000; //mapSize to 10000
    map = new hashNode*[mapSize]; //creates new map of size 100
    for (int i = 0; i < mapSize; i++) {
        map[i] = NULL; //initialize values to NULL
    }
}

void hashMap::addKeyValue(string k, string v) {
    int index; //create an index integer
    if (h1) {
        index = calcHash(k); //first calcHash if h1 is true
    }
    else {
        index = calcHash2(k); //second calcHash if h1 is false
    }
    int originalIndex = index;
    int i = 0;

    if (map[index] != NULL && map[index]->keyword != k) {
        collisionct1++; //collision, increase collisionct1 by 1
    }

    while (map[index] != NULL && map[index]->keyword != k) {
        i++;
        collisionct2++; //collision, increase collisionct2 by 1
        if (c1) {
            index = collHash1(originalIndex, i, k);
        }
        else {
            index = collHash2(originalIndex, i, k);
        }
    }

    if (map[index] == NULL) {
        map[index] = new hashNode(k); //new hashNode with k
        numKeys++; //increase numKeys
    }

    map[index]->addValue(v); //add value with v

    if (numKeys >= mapSize * 0.7) {
        reHash(); //rehash if 70% or over
    }
}

int hashMap::getIndex(string k) {
    int index; //create an index integer
    if (h1) {
        index = calcHash(k); //first calcHash if h1 is true
    }
    else {
        index = calcHash2(k); //second calcHash if h1 is false
    }
    int originalIndex = index;
    int i = 0; // Counter for collision handling

    while (map[index] != NULL && map[index]->keyword != k) {
        collisionct2++; //Secondary collision found, increase by 1

        // Apply collision resolution method based on c1 flag
        if (c1) {
            index = collHash1(originalIndex, ++i, k);
        }
        else {
            index = collHash2(originalIndex, ++i, k);
        }

        index %= mapSize; //staying within bounds of mapSize
    }

    return index; //return index
}

int hashMap::calcHash(string k) { //first and basic hash method
    int hashValue = 0; //initializes hashValue to 0
    for (char c: k) { //goes letter by letter
        hashValue = hashValue + static_cast<int>(c); //adds ASCII value to hashValue
    }
    return hashValue % mapSize; //standard hashValue % mapSize
}

int hashMap::calcHash2(string k) { //second hash method, works better than calcHash because more spread out
    int hashValue = 0; //initializes hashValue to 0
    int base = 997; //prime number to spread out numbers better, 997 is largest prime I know
    for (char c: k) { //goes letter by letter
        hashValue = (hashValue*base + static_cast<int>(c)) % mapSize; //multiply by base and then add ASCII value
    }
    return hashValue;
}

void hashMap::getClosestPrime() {
    int doubleSize = mapSize * 2; //double the size
    if (doubleSize % 2 == 0) {
        doubleSize = doubleSize + 1; //increase doubleSize by 1
    }
    while (!isPrime(doubleSize)) { //use helper function to see if prime
        doubleSize = doubleSize + 2; //if prime, add 2
    }
    mapSize = doubleSize; // Set mapSize to the next prime number
}

bool hashMap::isPrime(int g) { //helper method for getCLosestPrime
    if (g <= 1) { //negative numbers, 0, and 1 are composite
        return false;
    }
    if (g <= 3) { //2 and 3 are prime
        return true;
    }
    if (g % 2 == 0 || g % 3 == 0) { //if divisible by 2 or 3, composite
        return false;
    }
    for (int i = 5; i * i <= g; i += 6) {
        if (g % i == 0 || g % (i + 2) == 0) // tests if g is divisible by i or i + 2
            return false; //composite if either of these are true
    }
    return true; //prime
}

void hashMap::reHash() {
    hashNode **oldMap = map; //store old map
    int oldSize = mapSize; //store old size

    mapSize = mapSize * 2; //double map size

    map = new hashNode*[mapSize]; //new map with new size
    for (int i = 0; i < mapSize; i++) {
        map[i] = NULL; //initialize the new map to NULL.
    }

    for (int i = 0; i < oldSize; i++) { //rehash all old keys into new map
        if (oldMap[i] != NULL) {
            string key = oldMap[i]->keyword;

            //insert all values associated with the key
            for (int j = 0; j < oldMap[i]->currSize; j++) {
                string value = oldMap[i]->values[j];

                //calculate the new index and handle collisions
                int hIndex = (h1) ? calcHash(key) : calcHash2(key);
                int i = 0;

                //find the right position using the collision handling methods.
                while (map[hIndex] != NULL) {
                    if (c1) {
                        hIndex = collHash1(hIndex, ++i, key);
                    }
                    else {
                        hIndex = collHash2(hIndex, ++i, key);
                    }
                }

                //insert the key-value pair into the new map
                if (map[hIndex] == NULL) {
                    map[hIndex] = new hashNode(key);
                }
                map[hIndex]->addValue(value);
            }

            delete oldMap[i]; //delete old node for memory purposes
        }
    }

    delete[] oldMap; //delete old array for memory purposes
}

int hashMap::collHash1(int h, int i, string k) { //first collision method, used if collision booleans are false
    return (h + i) % mapSize; //linear probing
}

int hashMap::collHash2(int h, int i, string k) { //second collision methods, used if collision booleans are false
    return (h + i*i) % mapSize; //quadratic probing
}

int hashMap::findKey(string k) {
    int hIndex;
    if (h1) {
        hIndex = calcHash(k); //first calcHash if h1 is true
    }
    else {
        hIndex = calcHash2(k); //second calcHash if h1 is false
    }
    int initialIndex = hIndex; //initial index way
    int i = 0;
    hashNode* currentNode = map[hIndex]; //uses a temporary node
    while (currentNode != NULL) {
        if (currentNode->keyword == k) {
            return hIndex; //found at hIndex
        }
        if (c1) {
            hIndex = collHash1(initialIndex, ++i, k); //first collHash if c1 is true
        }
        else {
            hIndex = collHash2(initialIndex, ++i, k); //second collHash if c1 is false
        }
        if (hIndex == initialIndex) {
            break;
        }
        currentNode = map[hIndex];
    }
    return -1; //not in the array
}

void hashMap::printMap() { //printing map just to check, only purpose is testing
    for (int i = 0; i < mapSize; i++) {
        if (map[i] != NULL) {
            cout << i << map[i]->keyword << endl;
            for (int j = 0; j < map[i]->currSize; j++) {
                cout << map[i]->values[j] << endl;
                if (j < map[i]->currSize - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        else {
            cout << "[" << i << "] EMPTY\n";
        }
    }
}