#include <regex>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

using std::cout;
using std::vector;
using std::regex;
using std::regex_search;
using std::smatch;
using std::string;


enum TokenType {
    NUMBER,
    MINUS,
    WHITESPACE,
    NO_MORE_TOKENS,
    LEXICAL_ERROR
};

struct Token {
    TokenType type;
    string    value;
    Token() {;}
    Token(TokenType type, string value)
        : type(type), value(value){;}
    bool operator==(const Token& other) const {
        return type == other.type && value == other.value;
    }
};

class Lexer {
private:
    string input;
    string remaining;

public:
    Lexer(string input)
        : input(input) {
        remaining = input.c_str();
    }

    Token getNextToken(){
        Token token;
        do {
            if(remaining.size() == 0) {
                token = Token(NO_MORE_TOKENS, "");
                break;
            }

            smatch match;
            if (regex_search(remaining, match, regex("^([0-9]+)"))) {
                token = Token(NUMBER, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\-)"))) {
                token = Token(MINUS, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\s)"))) {
                token = Token(WHITESPACE, match[1].str());
                remaining = remaining.substr(token.value.size());
            } else {
                token = Token(LEXICAL_ERROR, match[1].str());
            }
        } while(token.type == WHITESPACE);

        return token;
    }
    bool getNextToken(Token& token) {
        token = getNextToken();
        return token.type != LEXICAL_ERROR;
    }

    void removeToken(Token token){
        remaining = remaining.substr(token.value.size());
    }

};


// expr = factor {- factor}
// factor -> INTEGER

class ASTNode {
public:
    virtual int process() = 0;
    virtual string toString() = 0;
    virtual ~ASTNode() {;}
};

class ASTNodeSubtract : public ASTNode {
public:
    ASTNode* pLeft;
    ASTNode* pRight;

public:
    ASTNodeSubtract(ASTNode* pLeft, ASTNode* pRight)
        : pLeft(pLeft), pRight(pRight) {;}
    ~ASTNodeSubtract() {
        delete pLeft;
        delete pRight;
    }
    int process() override {
        return pLeft->process() - pRight->process();
    }
    string toString() override {
        return "(" + pLeft->toString() + " - " + pRight->toString() + ")";
    }
};

class ASTNodeNumber : public ASTNode {
private:
    int number;
public:
    ASTNodeNumber(int number)
        : number(number) {;}
    int process() override {
        return number;
    }
    string toString() override {
        return std::to_string(number);
    }
};


// expr = factor {- factor}
// factor -> INTEGER

class ASTParser {
private:

    ASTNode* expr(Lexer& lexer) {
        ASTNode* pLeft = factor(lexer);
        Token token;
        while(lexer.getNextToken(token) && token.type == MINUS) {
            lexer.removeToken(token);
            ASTNode* pRight = factor(lexer);
            pLeft = new ASTNodeSubtract(pLeft, pRight);
        }

        return pLeft;
    }

    ASTNode* factor(Lexer& lexer) {
        Token token;
        lexer.getNextToken(token);
        ASTNode* pNode;
        if (token.type == NUMBER) {
            lexer.removeToken(token);
            pNode = new ASTNodeNumber(stoi(token.value));
        } else {
            throw std::runtime_error("parse error");
        }
        return pNode;
    }

public:
    ASTParser()    {;};
    ASTNode* parse(string statement){
        Lexer lexer(statement);
        return expr(lexer);
    }
};


int main() {
    ASTParser parser;

    // Test cases with expected results
    struct TestCase {
        string statement;
        int expected;
    };

    vector<TestCase> testCases = {
        {"1-2-3", -4},           // ((1-2)-3) = (-1-3) = -4
        {"10-5-2", 3},           // ((10-5)-2) = (5-2) = 3
        {"100-50-25-10", 15},    // (((100-50)-25)-10) = ((50-25)-10) = (25-10) = 15
        {"5", 5},                // Single number
        {"20-10", 10},           // Simple subtraction
        {"1-1-1-1", -2},         // (((1-1)-1)-1) = ((0-1)-1) = (-1-1) = -2
        {"50-20-10-5-3", 12},    // ((((50-20)-10)-5)-3) = (((30-10)-5)-3) = ((20-5)-3) = (15-3) = 12
        {"7-3-2-1", 1}           // (((7-3)-2)-1) = ((4-2)-1) = (2-1) = 1
    };

    int passed = 0;
    int failed = 0;

    for(const TestCase& test : testCases) {
        ASTNode* ast = parser.parse(test.statement);
        cout << "stmt: " << test.statement << "\n";
        cout << "AST structure: " << ast->toString() << "\n";
        int result = ast->process();
        cout << "result: " << result << " (expected: " << test.expected << ")";

        if (result == test.expected) {
            cout << " ✓ PASS\n";
            passed++;
        } else {
            cout << " ✗ FAIL\n";
            failed++;
        }
        cout << "\n";

        delete ast;
    }

    cout << "==========================================\n";
    cout << "Test Summary: " << passed << " passed, " << failed << " failed\n";
    cout << "==========================================\n";

    return 0;
}