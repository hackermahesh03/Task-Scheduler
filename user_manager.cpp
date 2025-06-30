// user_manager.cpp
#include "user_manager.h"
#include <iostream>
using namespace std;

string getUsername() {
    string username;
    cout << "Enter your username: ";
    getline(cin, username);     // ← use getline, not cin >>
    return username;
}
