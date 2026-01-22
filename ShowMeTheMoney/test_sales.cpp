#include <iostream>
#include <queue>
#include <vector>
#include "sales_priority.h"

using namespace std;

void testCase1() {
    cout << "=== Test Case 1: Different incomes ===" << endl;
    priority_queue<SalesLeadWithOrder, vector<SalesLeadWithOrder>, SalesLeadComparator> pq;
    int seq = 0;

    pq.push(SalesLeadWithOrder(SalesLead("Alice", 50000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Bob", 100000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Charlie", 75000), seq++));

    cout << "Expected order: Bob (100k), Charlie (75k), Alice (50k)" << endl;
    cout << "Actual order:   ";
    while (!pq.empty()) {
        auto lead = pq.top();
        pq.pop();
        cout << lead.lead.name << " (" << lead.lead.income << ")";
        if (!pq.empty()) cout << ", ";
    }
    cout << endl << endl;
}

void testCase2() {
    cout << "=== Test Case 2: Same income, test insertion order ===" << endl;
    priority_queue<SalesLeadWithOrder, vector<SalesLeadWithOrder>, SalesLeadComparator> pq;
    int seq = 0;

    pq.push(SalesLeadWithOrder(SalesLead("Alice", 60000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Bob", 60000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Charlie", 60000), seq++));

    cout << "Expected order: Alice, Bob, Charlie (all 60k, insertion order)" << endl;
    cout << "Actual order:   ";
    while (!pq.empty()) {
        auto lead = pq.top();
        pq.pop();
        cout << lead.lead.name;
        if (!pq.empty()) cout << ", ";
    }
    cout << endl << endl;
}

void testCase3() {
    cout << "=== Test Case 3: Mixed incomes with ties ===" << endl;
    priority_queue<SalesLeadWithOrder, vector<SalesLeadWithOrder>, SalesLeadComparator> pq;
    int seq = 0;

    pq.push(SalesLeadWithOrder(SalesLead("Alice", 80000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Bob", 100000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Charlie", 80000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Diana", 120000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Eve", 80000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Frank", 100000), seq++));

    cout << "Expected order: Diana (120k), Bob (100k), Frank (100k), " << endl;
    cout << "                Alice (80k), Charlie (80k), Eve (80k)" << endl;
    cout << "Actual order:   ";
    while (!pq.empty()) {
        auto lead = pq.top();
        pq.pop();
        cout << lead.lead.name << " (" << lead.lead.income << ")";
        if (!pq.empty()) cout << ", ";
    }
    cout << endl << endl;
}

void testCase4() {
    cout << "=== Test Case 4: Single customer ===" << endl;
    priority_queue<SalesLeadWithOrder, vector<SalesLeadWithOrder>, SalesLeadComparator> pq;
    int seq = 0;

    pq.push(SalesLeadWithOrder(SalesLead("Alice", 75000), seq++));

    cout << "Expected order: Alice (75k)" << endl;
    cout << "Actual order:   ";
    while (!pq.empty()) {
        auto lead = pq.top();
        pq.pop();
        cout << lead.lead.name << " (" << lead.lead.income << ")";
    }
    cout << endl << endl;
}

void testCase5() {
    cout << "=== Test Case 5: Customers added in descending income order ===" << endl;
    priority_queue<SalesLeadWithOrder, vector<SalesLeadWithOrder>, SalesLeadComparator> pq;
    int seq = 0;

    pq.push(SalesLeadWithOrder(SalesLead("Alice", 150000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Bob", 100000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Charlie", 50000), seq++));

    cout << "Expected order: Alice (150k), Bob (100k), Charlie (50k)" << endl;
    cout << "Actual order:   ";
    while (!pq.empty()) {
        auto lead = pq.top();
        pq.pop();
        cout << lead.lead.name << " (" << lead.lead.income << ")";
        if (!pq.empty()) cout << ", ";
    }
    cout << endl << endl;
}

void testCase6() {
    cout << "=== Test Case 6: Customers added in ascending income order ===" << endl;
    priority_queue<SalesLeadWithOrder, vector<SalesLeadWithOrder>, SalesLeadComparator> pq;
    int seq = 0;

    pq.push(SalesLeadWithOrder(SalesLead("Alice", 50000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Bob", 100000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Charlie", 150000), seq++));

    cout << "Expected order: Charlie (150k), Bob (100k), Alice (50k)" << endl;
    cout << "Actual order:   ";
    while (!pq.empty()) {
        auto lead = pq.top();
        pq.pop();
        cout << lead.lead.name << " (" << lead.lead.income << ")";
        if (!pq.empty()) cout << ", ";
    }
    cout << endl << endl;
}

void testCase7() {
    cout << "=== Test Case 7: Zero and low incomes ===" << endl;
    priority_queue<SalesLeadWithOrder, vector<SalesLeadWithOrder>, SalesLeadComparator> pq;
    int seq = 0;

    pq.push(SalesLeadWithOrder(SalesLead("Alice", 0), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Bob", 1000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Charlie", 0), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Diana", 500), seq++));

    cout << "Expected order: Bob (1000), Diana (500), Alice (0), Charlie (0)" << endl;
    cout << "Actual order:   ";
    while (!pq.empty()) {
        auto lead = pq.top();
        pq.pop();
        cout << lead.lead.name << " (" << lead.lead.income << ")";
        if (!pq.empty()) cout << ", ";
    }
    cout << endl << endl;
}

void testCase8() {
    cout << "=== Test Case 8: Many customers with same income (FIFO stress test) ===" << endl;
    priority_queue<SalesLeadWithOrder, vector<SalesLeadWithOrder>, SalesLeadComparator> pq;
    int seq = 0;

    pq.push(SalesLeadWithOrder(SalesLead("First", 50000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Second", 50000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Third", 50000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Fourth", 50000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Fifth", 50000), seq++));

    cout << "Expected order: First, Second, Third, Fourth, Fifth (all 50k)" << endl;
    cout << "Actual order:   ";
    while (!pq.empty()) {
        auto lead = pq.top();
        pq.pop();
        cout << lead.lead.name;
        if (!pq.empty()) cout << ", ";
    }
    cout << endl << endl;
}

void testCase9() {
    cout << "=== Test Case 9: Alternating high/low incomes ===" << endl;
    priority_queue<SalesLeadWithOrder, vector<SalesLeadWithOrder>, SalesLeadComparator> pq;
    int seq = 0;

    pq.push(SalesLeadWithOrder(SalesLead("Low1", 30000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("High1", 200000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Low2", 30000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("High2", 200000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Mid", 100000), seq++));

    cout << "Expected order: High1 (200k), High2 (200k), Mid (100k), Low1 (30k), Low2 (30k)" << endl;
    cout << "Actual order:   ";
    while (!pq.empty()) {
        auto lead = pq.top();
        pq.pop();
        cout << lead.lead.name << " (" << lead.lead.income << ")";
        if (!pq.empty()) cout << ", ";
    }
    cout << endl << endl;
}

void testCase10() {
    cout << "=== Test Case 10: Very large income differences ===" << endl;
    priority_queue<SalesLeadWithOrder, vector<SalesLeadWithOrder>, SalesLeadComparator> pq;
    int seq = 0;

    pq.push(SalesLeadWithOrder(SalesLead("Millionaire", 1000000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Average", 50000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Billionaire", 1000000000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Poor", 10000), seq++));

    cout << "Expected order: Billionaire (1B), Millionaire (1M), Average (50k), Poor (10k)" << endl;
    cout << "Actual order:   ";
    while (!pq.empty()) {
        auto lead = pq.top();
        pq.pop();
        cout << lead.lead.name << " (" << lead.lead.income << ")";
        if (!pq.empty()) cout << ", ";
    }
    cout << endl << endl;
}

void testCase11() {
    cout << "=== Test Case 11: Two customers with same income (minimal tie) ===" << endl;
    priority_queue<SalesLeadWithOrder, vector<SalesLeadWithOrder>, SalesLeadComparator> pq;
    int seq = 0;

    pq.push(SalesLeadWithOrder(SalesLead("First", 70000), seq++));
    pq.push(SalesLeadWithOrder(SalesLead("Second", 70000), seq++));

    cout << "Expected order: First, Second (both 70k)" << endl;
    cout << "Actual order:   ";
    while (!pq.empty()) {
        auto lead = pq.top();
        pq.pop();
        cout << lead.lead.name;
        if (!pq.empty()) cout << ", ";
    }
    cout << endl << endl;
}

int main() {
    cout << "Sales Lead Priority Queue - Maximum Sales Efficiency!" << endl;
    cout << "======================================================" << endl << endl;

    testCase1();
    testCase2();
    testCase3();
    testCase4();
    testCase5();
    testCase6();
    testCase7();
    testCase8();
    testCase9();
    testCase10();
    testCase11();

    cout << "All tests completed!" << endl;

    return 0;
}
