#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "hashMap.hpp"
#include "makeSeuss.hpp"

using namespace std;

int main(){
    srand(time(NULL)); //random number generator

    //four calls for Dr. Seuss text

    // DSOutput1.txt has results from hash method 1 and collision method 1
    makeSeuss seuss1("DrSeuss.txt", "C:\\Users\\Peter Chapman\\CLionProjects\\MakeDrSeuss\\DSOutput1.txt", true, true);

    // DSOutput2.txt has results from hash method 2 and collision method 1
    makeSeuss seuss2("DrSeuss.txt", "C:\\Users\\Peter Chapman\\CLionProjects\\MakeDrSeuss\\DSOutput2.txt", false, true);

    // DSOutput3.txt has results from hash method 1 and collision method 2
    makeSeuss seuss3("DrSeuss.txt", "C:\\Users\\Peter Chapman\\CLionProjects\\MakeDrSeuss\\DSOutput3.txt", true, false);

    // DSOutput4.txt has results from hash method 2 and collision method 2
    makeSeuss seuss4("DrSeuss.txt", "C:\\Users\\Peter Chapman\\CLionProjects\\MakeDrSeuss\\DSOutput4.txt", false, false);

    //four calls for Charles Dickens text

    // CDOutput1.txt has results from hash method 1 and collision method 1
    makeSeuss dickens1("CDickens.txt", "C:\\Users\\Peter Chapman\\CLionProjects\\MakeDrSeuss\\CDOutput1.txt", true, true);

    // CDOutput2.txt has results from hash method 2 and collision method 1
    makeSeuss dickens2("CDickens.txt", "C:\\Users\\Peter Chapman\\CLionProjects\\MakeDrSeuss\\CDOutput2.txt", false, true);

    // CDOutput3.txt has results from hash method 1 and collision method 2
    makeSeuss dickens3("CDickens.txt", "C:\\Users\\Peter Chapman\\CLionProjects\\MakeDrSeuss\\CDOutput3.txt", true, false);

    // CDOutput4.txt has results from hash method 2 and collision method 2
    makeSeuss dickens4("CDickens.txt", "C:\\Users\\Peter Chapman\\CLionProjects\\MakeDrSeuss\\CDOutput4.txt", false, false);

    return 0;
}
