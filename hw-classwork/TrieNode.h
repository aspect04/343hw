
#ifndef TRIENODE_H
#define TRIENODE_H
#include <map>
using namespace std;

class TrieNode {

public:
    TrieNode(char s, bool isWord) {
        this->data = s;
        this->end = isWord;
    }
    ~TrieNode();
    void insert(string word) {
        while (true) {
            if (word.size() > 1) {
                new TrieNode(word[0], false);
            }
            else {new TrieNode(word[0], true);}
        }
    }
    bool search(string word);
    void deleteWord(string word);
private:
    TrieNode* parent;
    map<char, TrieNode*> children;
    char data;
    bool end;

};

#endif //TRIENODE_H
