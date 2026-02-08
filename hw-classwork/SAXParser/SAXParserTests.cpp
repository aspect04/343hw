#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "SimpleSAXParser.h"

using std::string;
using std::map;
using std::pair;
using std::cout;
using std::vector;
using std::stringstream;

class TestHandler : public SAXParserEventHandler {
public:
    vector<string> tokens;

    // overrides
    void startElement(const std::string& name, map<string,string>& attributes) override {
        tokens.push_back("START:" + name);
        for(pair<string,string> attr : attributes) {
            tokens.push_back("ATTR:" + attr.first + "=" + attr.second);
        }
    };
    void characters(const std::string& data) override {
        tokens.push_back("CHARS:" + data);
    };
    virtual void endElement(const std::string& name) override {
        tokens.push_back("END:" + name);
    };
};

string fmtVector(vector<string> tokens) {
    stringstream out;
    string delim = "";
    for(string token : tokens) {
        out << delim << token;
        delim = ",";
    }
    return out.str();
}

bool testParser() {
    string xml = "<testing id=\"fish\" otherid=\"face\" >hello</testing>";
    TestHandler evtHandler;
    parseXML(xml, evtHandler);
    vector<string> expected = {"START:testing","ATTR:id=fish", "ATTR:otherid=face","CHARS:hello","END:testing"};

    cout << "Tokens: " << fmtVector(evtHandler.tokens) << "\n";
    
    if(evtHandler.tokens != expected) {
        cout << "TEST FAILED!\n";
        cout << "expected: " << fmtVector(expected) << "\n";
        cout << "actual: " << fmtVector(evtHandler.tokens) << "\n";
        return false;
    }
    return true;
}

