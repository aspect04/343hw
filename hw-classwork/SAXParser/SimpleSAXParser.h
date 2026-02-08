#pragma once
#include <string>
#include <map>

class SAXParserEventHandler {
public:    
    virtual void startElement(const std::string& name, std::map<std::string, std::string>& attributes) = 0;
    virtual void characters(const std::string& data) = 0;
    virtual void endElement(const std::string& name) = 0;
    virtual ~SAXParserEventHandler() = default;
};

void parseXML(const std::string& xml, SAXParserEventHandler& handler);