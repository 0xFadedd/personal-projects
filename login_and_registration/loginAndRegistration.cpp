#include <iostream>
#include <math.h>
#include <string>

using namespace std;

class User {
    public:
        string username;
        string password;
};


void signIn() {
    User user;
    std::hash<std::string> hash;
    std::cout << "Please enter your username";
    std::cin >> user.username;
    std::cout << "Please enter your username";
    std::cin >> user.password;
    user.password = hash(user.password);

}

void signUp() {

}

void main() {
    string input = "0";

    std::cout << "Would you like to sign up/sign in 1/2";
    std::cin >> input;

    input.compare("1") == 0 ? signUp() : signIn();
}