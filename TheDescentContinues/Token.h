
#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using std::string;

enum TokenType {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    WHITESPACE,
    NO_MORE_TOKENS,
    LEXICAL_ERROR
};

struct Token {
    TokenType type;
    string    value;
    Token() {;}
    Token(TokenType type, string value)
        : type(type), value(value) {;}
    bool operator==(const Token& other) const {
        return type == other.type && value == other.value;
    }
};

#endif //TOKEN_H
