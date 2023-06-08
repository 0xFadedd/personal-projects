#include <iostream>
#include <string>
#include <fstream>
#include <functional>

class User {
    std::string username;
    std::string passwordHash;
public:
    void inputUserData() {
        std::cout << "Please enter your username \n";
        std::cin >> username;
        std::cout << "Please enter your password \n";
        std::string password;
        std::cin >> password;
        passwordHash = std::to_string(std::hash<std::string>{}(password));
    }

    bool validateUser() {
        std::ifstream file(username + ".txt");

        if (!file) {
            std::cerr << "Incorrect Username: " << username << "\n";
            return false;
        }

        std::string fileLine;
        while(getline(file, fileLine)) {
            if(passwordHash == fileLine) {
                std::cout << "Success! You are now signed in. \n";
                return true;
            }
        }
        std::cerr << "Incorrect Password, try again \n";
        return false;
    }

    void registerUser() {
        std::ofstream newUserFile(username + ".txt");
        if (newUserFile) {
            newUserFile << username << '\n' << passwordHash; 
        } else {
            std::cerr << "Failed to create user file. \n";
        }
    }
};

void signIn() {
    while (true) {
        User user;
        user.inputUserData();
        if (user.validateUser()) {
            break;
        }
    }
}

void signUp() {
    User newUser;
    newUser.inputUserData();
    newUser.registerUser();
}

int main() {
    while (true) {
        std::cout << "Would you like to sign up/sign in (1/2)\n";
        std::string input;
        std::cin >> input;
        if (input == "1") {
            signUp();
            break;
        } else if (input == "2") {
            signIn();
            break;
        } else {
            std::cout << "Invalid input. Please enter either 1 or 2.\n";
        }
    }
    return 0;
}
