
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "SimpleSAXParser.h"


////////////////////////////////////////////////////////////////////////
// This SAX parsing code was mostly written by ChatGPT
// It works well enough for this exercise, but it is very buggy.  
// For example, it doesn't handle spaces in attributes correctly.
/////////////////////////////////////////////////////////////////////// 

static bool isWhitespace(const std::string& str) {
    for (char c : str) {
        if (!std::isspace(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

static std::string trim(const std::string& str) {
    const char* whitespace = " \t\n\r";
    size_t start = str.find_first_not_of(whitespace);
    size_t end = str.find_last_not_of(whitespace);
    return (start == std::string::npos) ? "" : str.substr(start, end-start+1);
}


static void parseTag(const std::string& tag, std::string& tagName, std::map<std::string, std::string>& attributes) {
    std::istringstream stream(tag);
    stream >> tagName;

    std::string attrPair;
    while (stream >> attrPair) {
        size_t eq = attrPair.find('=');
        if (eq != std::string::npos && eq + 1 < attrPair.length()) {
            std::string key = attrPair.substr(0, eq);
            std::string value = attrPair.substr(eq + 1);

            // Remove quotes
            if (!value.empty() && value.front() == '\"') {
                value = value.substr(1, value.length() - 2);
            }
            attributes[trim(key)] = trim(value);
        }
    }
}


void parseXML(const std::string& xml, SAXParserEventHandler& handler) {
    size_t i = 0;
    while (i < xml.size()) {
        if (xml[i] == '<') {
            if (xml[i + 1] == '/') {
                // End tag
                size_t end = xml.find('>', i);
                std::string tagName = xml.substr(i + 2, end - i - 2);
                handler.endElement(trim(tagName));
                i = end + 1;
            } else {
                // Start tag
                size_t end = xml.find('>', i);
                std::string tagContent = xml.substr(i + 1, end - i - 1);
                std::string tagName;
                std::map<std::string, std::string> attributes;
                parseTag(tagContent, tagName, attributes);
                handler.startElement(tagName, attributes);
                i = end + 1;
            }
        } else {
            // Characters
            size_t end = xml.find('<', i);
            std::string data = xml.substr(i, end - i);
            if (!isWhitespace(data)) {
                handler.characters(data);
            }
            i = end;
        }
    }
}
    
