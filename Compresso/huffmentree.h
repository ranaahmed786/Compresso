#ifndef HUFFMENTREE_H
#define HUFFMENTREE_H
#include<queue>
#include<string>
#include<unordered_map>
using namespace std;
class HuffmenTree
{
    struct Node {
        unsigned char data;
        int freq;
        Node* left;
        Node* right;

        Node(unsigned char ch, int freq) : data(ch), freq(freq), left(nullptr), right(nullptr) {}
        Node(Node* l, Node* r) : data('\0'), freq(l->freq + r->freq), left(l), right(r) {}
    };

    Node*root;
    //private wrapper for code generation recursively
    void generateCodes(Node* node,string currCode,unordered_map<unsigned char,string> codes);

public:
    HuffmenTree();
    void makeTree(const unordered_map<unsigned char,int> & info);
    unordered_map<unsigned char,string> getCodes();
};

#endif // HUFFMENTREE_H
