#include <iostream>
#include <string>
using namespace std;

bool whatIHeardYouSay(string input) {
    cout << "what I heard you say is: " << input << "\n";
    return input=="quit";
}
bool polight(string input) {
    if(input.find("please quit") == 0) {
        cout << "nicely said\n";
        return true;
    }
    cout << "I don't understand\n";
    return false;
}
bool custserv(string input) {
    if(input == "hangup") {
        return true;
    }
    cout << "I'm sorry. I didn't quite get that. Can you repeat it?\n";
    return false;
}

void processUserInput(bool(*func)(string)) {
    string user_input;
    while(true) {
        getline(cin, user_input);
        if (func(user_input)) break;
    }
}

int main() {
    processUserInput(whatIHeardYouSay);
    processUserInput(polight);
    processUserInput(custserv);

    processUserInput([](string input) {
        cout << "Nice work saying, " << input << "\n";
        return input == "please";
    });

    return 0;
}