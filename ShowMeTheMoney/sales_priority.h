#ifndef SALES_PRIORITY_H
#define SALES_PRIORITY_H

#include <string>

using namespace std;

class SalesLead {
public:
    string name;
    int income;

    SalesLead(string n, int i) : name(n), income(i) {}
};

// tracks insertion order
struct SalesLeadWithOrder {
    SalesLead lead;
    int sequence;

    SalesLeadWithOrder(SalesLead l, int seq) : lead(l), sequence(seq) {}
};

// custom comparator for priority queue
// returns true if "a" has lower priority than "b"
struct SalesLeadComparator {
    bool operator()(const SalesLeadWithOrder& a, const SalesLeadWithOrder& b) const {
        // If incomes are different, higher income has higher priority
        if (a.lead.income != b.lead.income) {
            return a.lead.income < b.lead.income;  // a has lower priority if income is less
        }
        // If incomes are equal, earlier insertion/lower sequence has higher priority
        return a.sequence > b.sequence;  // "a" has lower priority if sequence is greater
    }
};

#endif
