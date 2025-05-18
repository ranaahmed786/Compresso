#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include<queue>
#include<string>
#include<unordered_map>
#include<algorithm>
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

    Node* root;
    //private wrapper for code generation recursively
    void generateCodes(Node* node, string currCode, unordered_map<unsigned char, string>& codes);

public:
    HuffmenTree();
    ~HuffmenTree();
    void deleteTree(Node* node);
    void makeTree(const unordered_map<unsigned char, int>& info);
    void getHuffCanonicalCodes(vector<pair<unsigned char, int>>& codeLenghts, unordered_map<unsigned char, string>& codes);
    void getHuffCodes(unordered_map<unsigned char, string>& codes);
    void getHuffCanonicalCodes(vector<pair<unsigned char, int>>& codeLenghts, unordered_map<unsigned char, string>& codes ,bool codesLengthsSorted);
};

#endif // HUFFMANTREE_H
