#include <iostream>
#include <math.h>
#include <string>
#include <fstream>

using namespace std;

class User {
    public:
        std::string username;
    private:
        std::string passwordHash;

    public:
        void setPasswordHash(string hash) {
            passwordHash = hash;
        }

        string getPasswordHash() {
            return passwordHash;
        }
};

void signIn() {
    User user;
    std::hash<std::string> hash;
    std::cout << "Please enter your username";
    std::cin >> user.username;
    std::cout << "Please enter your username";
    std::string p;
    user.setPasswordHash((std::cin >> p, std::to_string(hash(p))));

    std::string filename = user.username + ".txt";
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Incorrect Username: " << filename;
        return;
    }

    std::string fileLine;
    while(getline(file, fileLine)) {
        if(user.getPasswordHash() == fileLine) {
            std::cout << "Success! You are now signed in.";
        } else {
            std::cout << "Incorrect Password, try again";
        }   
    }
}

void signUp() {
    

}

void main() {
    string input = "0";

    std::cout << "Would you like to sign up/sign in 1/2";
    std::cin >> input;

    input.compare("1") == 0 ? signUp() : signIn();
}