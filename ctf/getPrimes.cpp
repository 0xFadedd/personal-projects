// C++ program to get the first prime less than N 
#include <iostream> 
#include <string>
#include <cstdlib> // for atoi
using namespace std; 

// function check whether a number is prime or not 
bool isPrime(int n) 
{ 
    // Corner case 
    if (n <= 1) 
        return false; 

    // Check from 2 to sqrt(n) 
    for (int i = 2; i * i <= n; i++) 
        if (n % i == 0) 
            return false; 

    return true; 
} 

// Function to get the first prime less than n
int firstPrimeBelowN(int n) 
{ 
    for (int i = n - 1; i >= 2; i--) 
        if (isPrime(i)) 
            return i;
    return -1; // return -1 if no prime number is found
} 

// Driver Code 
int main(int argc, char* argv[]) 
{ 
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <n>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    cout << "The first prime number less than " << n << " is " << firstPrimeBelowN(n) << endl;
} 