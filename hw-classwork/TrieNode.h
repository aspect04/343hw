
#ifndef TRIENODE_H
#define TRIENODE_H
#include <map>

class TrieNode {
    map<char, TrieNode*> children;
    bool end;

};

#endif //TRIENODE_H
