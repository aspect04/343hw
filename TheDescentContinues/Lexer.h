
#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <string>
#include <regex>

using std::string;
using std::regex;
using std::regex_search;
using std::smatch;

class Lexer {
private:
    string input;
    string remaining;

public:
    Lexer(string input)
        : input(input) {
        remaining = input.c_str();
    }

    Token getNextToken() {
        Token token;
        do {
            if (remaining.size() == 0) {
                token = Token(NO_MORE_TOKENS, "");
                break;
            }

            smatch match;
            if (regex_search(remaining, match, regex("^([0-9]+)"))) {
                token = Token(NUMBER, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\+)"))) {
                token = Token(PLUS, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\-)"))) {
                token = Token(MINUS, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\*)"))) {
                token = Token(MULTIPLY, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\/)"))) {
                token = Token(DIVIDE, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\()"))) {
                token = Token(LPAREN, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\))"))) {
                token = Token(RPAREN, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\s)"))) {
                token = Token(WHITESPACE, match[1].str());
                remaining = remaining.substr(token.value.size());
            } else {
                token = Token(LEXICAL_ERROR, remaining.substr(0, 1));
            }
        } while (token.type == WHITESPACE);

        return token;
    }

    bool getNextToken(Token& token) {
        token = getNextToken();
        if (token.type == LEXICAL_ERROR)
            throw std::runtime_error("lexical error: unexpected character '" + token.value + "'");
        return token.type != NO_MORE_TOKENS;
    }

    void removeToken(Token token) {
        remaining = remaining.substr(token.value.size());
    }
};
#endif //LEXER_H
