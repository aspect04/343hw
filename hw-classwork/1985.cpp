#include "SAXParser/SimpleSAXParser.h"
#include "SAXParser/data.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::string;
using std::map;
using std::vector;
using std::cout;

class RegionReportHandler : public SAXParserEventHandler {
private:
    vector<string> pathStack;
    map<string, int> regionPopulations;

    string buildPathUpTo(size_t depth) {
        string path;
        for (size_t i = 0; i < depth && i < pathStack.size(); i++) {
            if (i > 0) path += "/";
            path += pathStack[i];
        }
        if (depth == 1) path += "/";
        return path;
    }

    string buildPath() {
        return buildPathUpTo(pathStack.size());
    }

public:
    void startElement(const string& name, map<string, string>& attributes) override {
        if (name == "region") {
            string regionName = attributes["name"];
            pathStack.push_back(regionName);

            string fullPath = buildPath();

            if (regionPopulations.find(fullPath) == regionPopulations.end()) {
                regionPopulations[fullPath] = 0;
            }

            if (attributes.find("population") != attributes.end()) {
                int pop = std::stoi(attributes["population"]);

                for (size_t i = 1; i <= pathStack.size(); i++) {
                    string path = buildPathUpTo(i);
                    regionPopulations[path] += pop;
                }
            }
        }
    }

    void characters(const string& data) override {
        (void)data;
    }

    void endElement(const string& name) override {
        if (name == "region" && !pathStack.empty()) {
            pathStack.pop_back();
        }
    }

    void printReport() {
        for (const auto& pair : regionPopulations) {
            cout << pair.first << " : " << pair.second << "\n";
        }
    }
};

int main() {
    RegionReportHandler handler;
    parseXML(REGIONAL_DATA, handler);
    handler.printReport();
    return 0;
}
