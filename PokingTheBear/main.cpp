#include <iostream>
#include <string>
using namespace std;

enum State {
    INDIFFERENT,
    ANNOYED,
    ANGRY,
    VERY_ANGRY,
    EXTREME_ANGER,
    FINAL
};

enum Input {
    POKE,
    PET,
    FEED,
    OTHER
};

// Input -> State
void handleInput(State& currentState, Input userInput) {
    switch(currentState) {
        case INDIFFERENT:
            if(userInput == POKE) {
                currentState = ANNOYED;
                cout << "The bear growls" << endl;
            }
            else if(userInput == PET) {
                currentState = INDIFFERENT;
                cout << "The bear calms down a bit" << endl;
            }
            else if(userInput == FEED) {
                currentState = INDIFFERENT;
                cout << "The bear seems somewhat satisfied" << endl;
            }
            else if(userInput == OTHER) {
                currentState = INDIFFERENT;
                cout << "Whaat?" << endl;
            }
            break;
        case ANNOYED:
            if(userInput == POKE) {
                currentState = ANGRY;
                cout << "The bear gives you a nasty scratch" << endl;
            }
            else if(userInput == PET) {
                currentState = INDIFFERENT;
                cout << "The bear calms down a bit" << endl;
            }
            else if(userInput == FEED) {
                currentState = INDIFFERENT;
                cout << "The bear seems somewhat satisfied" << endl;
            }
            else if(userInput == OTHER) {
                currentState = ANNOYED;
                cout << "Whaat?" << endl;
            }
            break;
        case ANGRY:
            if(userInput == POKE) {
                currentState = VERY_ANGRY;
                cout << "The bear gives you a savage bite" << endl;
            }
            else if(userInput == PET) {
                currentState = ANNOYED;
                cout << "The bear calms down a bit" << endl;
            }
            else if(userInput == FEED) {
                currentState = INDIFFERENT;
                cout << "The bear seems somewhat satisfied" << endl;
            }
            else if(userInput == OTHER) {
                currentState = ANGRY;
                cout << "Whaat?" << endl;
            }
            break;
        case VERY_ANGRY:
            if(userInput == POKE) {
                currentState = EXTREME_ANGER;
                cout << "The bear gives you a severe mauling" << endl;
            }
            else if(userInput == PET) {
                currentState = ANGRY;
                cout << "The bear calms down a bit" << endl;
            }
            else if(userInput == FEED) {
                currentState = INDIFFERENT;
                cout << "The bear seems somewhat satisfied" << endl;
            }
            else if(userInput == OTHER) {
                currentState = VERY_ANGRY;
                cout << "Whaat?" << endl;
            }
            break;
        case EXTREME_ANGER:
            if(userInput == POKE) {
                currentState = FINAL;
                cout << "The bear reduces you to bits and pieces" << endl;
            }
            else if(userInput == PET) {
                currentState = VERY_ANGRY;
                cout << "The bear calms down a bit" << endl;
            }
            else if(userInput == FEED) {
                currentState = INDIFFERENT;
                cout << "The bear seems somewhat satisfied" << endl;
            }
            else if(userInput == OTHER) {
                currentState = EXTREME_ANGER;
                cout << "Whaat?" << endl;
            }
            break;
        default:
            // ignore input
            break;
    }
}

//Print State
void printState(State currentState) {
    switch(currentState) {
        case INDIFFERENT:
            cout << "Bear state: Indifferent" << endl;
            break;
        case ANNOYED:
            cout << "Bear state: Annoyed" << endl;
            break;
        case ANGRY:
            cout << "Bear state: Angry" << endl;
            break;
        case VERY_ANGRY:
            cout << "Bear state: Very Angry" << endl;
            break;
        case EXTREME_ANGER:
            cout << "Bear state: Extreme Anger" << endl;
            break;
        case FINAL:
            cout << "Bear state: Final" << endl;
            break;
    }
}

//parse string input into enum Input
Input parseInput(string input) {
    if(input == "poke") {
        return POKE;
    }
    else if(input == "pet") {
        return PET;
    }
    else if(input == "feed") {
        return FEED;
    }
    else {
        return OTHER;
    }
}
//making it case in-sensitive
string toLowerCase(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int main() {
    State currentState = INDIFFERENT;
    string input;

    while (currentState != FINAL) {

        printState(currentState);

        cout << "Enter action (poke, pet, feed, or anything else): ";
        cin >> input;
        toLowerCase(input);

        if(input == "quit" || input == "exit" || input == "q") {
            cout << "Goodbye!" << endl;

            break;
        }

        Input userInput = parseInput(input);
        handleInput(currentState, userInput);
    }
    if (currentState == FINAL) {
        cout << "GAME OVER!" << endl;
    }
    return 0;
}