
#ifndef ASTNODE_H
#define ASTNODE_H

#include <string>
#include <stdexcept>

using std::string;

// Grammar:
// expr   -> term   {+|- term}
// term   -> factor {*|/ factor}
// factor -> NUMBER | ( expr )

class ASTNode {
public:
    virtual int    process()  = 0;
    virtual string toString() = 0;
    virtual ~ASTNode() {;}
};

class ASTNodeBinaryOp : public ASTNode {
public:
    char     op;
    ASTNode* pLeft;
    ASTNode* pRight;

    ASTNodeBinaryOp(char op, ASTNode* pLeft, ASTNode* pRight)
        : op(op), pLeft(pLeft), pRight(pRight) {;}

    ~ASTNodeBinaryOp() {
        delete pLeft;
        delete pRight;
    }

    int process() override {
        int l = pLeft->process();
        int r = pRight->process();
        switch (op) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/':
                if (r == 0) throw std::runtime_error("division by zero");
                return l / r;
            default:  throw std::runtime_error("unknown operator");
        }
    }

    string toString() override {
        return "(" + pLeft->toString() + " " + op + " " + pRight->toString() + ")";
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
#endif //ASTNODE_H
