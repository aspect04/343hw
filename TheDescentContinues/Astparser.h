
#ifndef ASTPARSER_H
#define ASTPARSER_H

#include "ASTNode.h"
#include "Lexer.h"
#include <string>
#include <stdexcept>

using std::string;

class ASTParser {
private:

    // expr -> term {+|- term}
    ASTNode* expr(Lexer& lexer) {
        ASTNode* pLeft = term(lexer);
        Token token;
        while (lexer.getNextToken(token) && (token.type == PLUS || token.type == MINUS)) {
            char op = (token.type == PLUS) ? '+' : '-';
            lexer.removeToken(token);
            ASTNode* pRight = term(lexer);
            pLeft = new ASTNodeBinaryOp(op, pLeft, pRight);
        }
        return pLeft;
    }

    // term -> factor {*|/ factor}
    ASTNode* term(Lexer& lexer) {
        ASTNode* pLeft = factor(lexer);
        Token token;
        while (lexer.getNextToken(token) && (token.type == MULTIPLY || token.type == DIVIDE)) {
            char op = (token.type == MULTIPLY) ? '*' : '/';
            lexer.removeToken(token);
            ASTNode* pRight = factor(lexer);
            pLeft = new ASTNodeBinaryOp(op, pLeft, pRight);
        }
        return pLeft;
    }

    // factor -> NUMBER | ( expr )
    ASTNode* factor(Lexer& lexer) {
        Token token;
        lexer.getNextToken(token);

        if (token.type == NUMBER) {
            lexer.removeToken(token);
            return new ASTNodeNumber(stoi(token.value));
        } else if (token.type == LPAREN) {
            lexer.removeToken(token);
            ASTNode* pNode = expr(lexer);
            Token rparen;
            lexer.getNextToken(rparen);
            if (rparen.type != RPAREN) {
                delete pNode;
                throw std::runtime_error("parse error: expected ')'");
            }
            lexer.removeToken(rparen);
            return pNode;
        } else {
            throw std::runtime_error("parse error: expected number or '('");
        }
    }

public:
    ASTParser() {;}

    ASTNode* parse(string statement) {
        Lexer lexer(statement);
        ASTNode* pNode = expr(lexer);
        // Check that all input was consumed — any leftover token is a parse error
        Token leftover;
        if (lexer.getNextToken(leftover)) {
            delete pNode;
            throw std::runtime_error("parse error: unexpected token '" + leftover.value + "'");
        }
        return pNode;
    }
};
#endif //ASTPARSER_H
