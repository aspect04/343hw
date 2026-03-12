#include <iostream>
#include <vector>
#include <string>
#include "ASTParser.h"

using std::cout;
using std::vector;
using std::string;

int main() {
    ASTParser parser;

    struct TestCase {
        string statement;
        int    expected;
        string description;
    };

    // ----------------------------------------------------------------
    // Happy-path tests: expect a valid result
    // ----------------------------------------------------------------
    vector<TestCase> testCases = {
        // Original subtraction tests (left-associativity)
        {"1-2-3",                -4,  "left-assoc subtraction"},
        {"10-5-2",                3,  "left-assoc subtraction"},
        {"100-50-25-10",         15,  "left-assoc subtraction chain"},
        {"5",                     5,  "single number"},
        {"20-10",                10,  "simple subtraction"},

        // Addition
        {"1+2+3",                 6,  "addition chain"},
        {"10+5-2",               13,  "add then subtract"},

        // Multiplication / division (higher precedence)
        {"2+3*4",                14,  "mul before add"},
        {"10-2*3",                4,  "mul before sub"},
        {"8/2+3",                 7,  "div before add"},
        {"6/2*3",                 9,  "left-assoc mul/div"},

        // Precedence edge case: div before sub
        {"10-6/2",                7,  "div before sub"},

        // Parentheses (highest precedence)
        {"(2+3)*4",              20,  "parens override precedence"},
        {"2*(3+4)",              14,  "parens on right"},
        {"(10-5)*2",             10,  "parens subtraction"},
        {"(2+3)*(4-1)",          15,  "parens both sides"},
        {"((2+3))*4",            20,  "double parens"},
        {"10/(2+3)",              2,  "parens in divisor"},

        // Deeply nested parentheses with mixed ops
        {"((2+3)*4)-((1+1)*3)",  14,  "nested parens mixed ops"},

        // Mixed complexity
        {"2+3*4-1",              13,  "mixed precedence"},
        {"(1+2)*(3+4)-(5*2)",   11,  "complex expression"},

        // Whitespace handling
        {"2 + 3 * 4",            14,  "whitespace between tokens"},
        {"( 2 + 3 ) * 4",        20,  "whitespace inside parens"},

        // Zero as an operand
        {"0+5",                   5,  "zero left operand"},
        {"5*0",                   0,  "zero right operand"},
        {"0*0",                   0,  "zero both operands"},

        // Multi-digit numbers
        {"99+1",                100,  "two multi-digit numbers"},
        {"123-23",              100,  "multi-digit subtraction"},

        // Result of zero (distinct from division by zero)
        {"5-5",                   0,  "result is zero"},
        {"10-5*2",                0,  "result is zero via precedence"},
    };

    int passed = 0;
    int failed = 0;

    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║         THE DESCENT 2: CYBORG ASSASSINS IN THE DEEP     ║\n";
    cout << "║              Extended Recursive Descent Parser           ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    cout << "--- Happy Path Tests ---\n\n";

    for (const TestCase& test : testCases) {
        try {
            ASTNode* ast = parser.parse(test.statement);
            int    result = ast->process();
            string astStr = ast->toString();
            delete ast;

            bool pass = (result == test.expected);
            if (pass) passed++; else failed++;

            cout << (pass ? "✓" : "✗") << " [" << test.description << "]\n";
            cout << "  expr : " << test.statement << "\n";
            cout << "  AST  : " << astStr << "\n";
            cout << "  got  : " << result
                 << "  expected: " << test.expected
                 << (pass ? "  PASS" : "  FAIL") << "\n\n";
        } catch (const std::exception& e) {
            failed++;
            cout << "✗ [" << test.description << "] UNEXPECTED EXCEPTION: " << e.what() << "\n\n";
        }
    }

    // ----------------------------------------------------------------
    // Error tests: expect an exception to be thrown
    // ----------------------------------------------------------------
    struct ErrorTestCase {
        string statement;
        string description;
        string expectedMsg; // substring expected in the exception message
    };

    vector<ErrorTestCase> errorTests = {
        {"6/0",         "division by zero",           "division by zero"},
        {"10/(5-5)",    "division by zero (expr)",    "division by zero"},
        {"(2+3*4",      "missing RPAREN",             "expected ')'"},
        {"2@3",         "lexical error",              "lexical error: unexpected character '@'"},
        {"",            "empty input",                "expected number or '('"},
        {"+5",          "leading operator",           "expected number or '('"},
        {"*3",          "leading multiply",           "expected number or '('"},
        {"5+",          "trailing operator",          "expected number or '('"},
        {"2+3)",        "extra RPAREN",               "unexpected token ')'"},
    };

    cout << "--- Error Handling Tests ---\n\n";

    for (const ErrorTestCase& test : errorTests) {
        bool pass = false;
        string caughtMsg;
        try {
            ASTNode* ast = parser.parse(test.statement);
            int result = ast->process();  // division by zero throws here
            delete ast;
            caughtMsg = "(no exception thrown, result was " + std::to_string(result) + ")";
        } catch (const std::exception& e) {
            caughtMsg = e.what();
            // Check that the exception message contains the expected substring
            pass = (caughtMsg.find(test.expectedMsg) != string::npos);
        }

        if (pass) passed++; else failed++;

        cout << (pass ? "✓" : "✗") << " [" << test.description << "]\n";
        cout << "  expr     : \"" << test.statement << "\"\n";
        cout << "  exception: " << caughtMsg
             << (pass ? "  PASS" : "  FAIL") << "\n\n";
    }

    cout << "══════════════════════════════════════════════════════════\n";
    cout << "  Test Summary: " << passed << " passed, " << failed << " failed\n";
    cout << "══════════════════════════════════════════════════════════\n";

    return 0;
}