/*
    A program that takes 3 angles a inputs and checks whether they form a valid triagle
*/

#include <iostream>
#include <math.h>

using namespace std;

// create check functions for each type of triangle

int main() {
    // print enter angle messages
    // use cin to have things entered
    //check they form a valid triangle and return the trianle type
    int angles [3] = {};

    std::cout << "----------- ----------- ----------- ----------- ----------- \n";
    std::cout << "------------- Welcome to the triangle checker ------------- \n";
    std::cout << "----------- ----------- ----------- ----------- ----------- \n";
    

    std::cout << "Please enter the first angle \n";
    std::cin >> angles[0];

    std::cout << "Please enter the second angle \n";
    std::cin >> angles[1];

    std::cout << "Please enter the third angle \n";
    std::cin >> angles[2];
    
    if(angles[0] + angles[1] + angles[2] == 180 ) {
        std::cout << "The angles " << angles[0] << ", " << angles[1] << ", " << angles[2] << ", " << " form a valid triangle! \n";
        for(int i = 0; i < 3; i++) {
            if(i<1 
                && (angles[i] != angles[i+1])
                && (angles[i+1] != angles[i+2]) 
                && (angles[i] != angles[i+2])){
                std::cout << "The triangle is a scalene \n";
                break;
            }
            else if(i<1 && angles[i] == angles[i+1] && angles[i+1] == angles[i+2]) {
                std::cout << "The triangle is a equilateral \n";
                break;
            }
            else if(i<2 && angles[i] == angles[i+1]) {
                std::cout << "The triangle is an iscosoles \n";
                
            }
            else if(angles[i] == 90) {
                std::cout << "The triangle is a right angled triangle \n";
                
            }
        }
    } else { std::cout << "Invalid angles \n"; }

    



    return 0;
}


//clang++ -std=c++14 -o triangle triangleChecker.cpp
