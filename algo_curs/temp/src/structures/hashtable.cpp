#include <iostream>

using namespace std;

struct HashNode {
    string key;
    string value;
    bool flag= true;
    HashNode* next;
    HashNode(string k, string v) : key(k), value(v), next(nullptr) {}
};