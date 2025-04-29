#include "huffmentree.h"
HuffmenTree::HuffmenTree():root(nullptr) {}

void HuffmenTree::makeTree(const unordered_map<unsigned char, int>& freqMap) {
    struct Compare {
        bool operator()(Node* a, Node* b) {
            return a->freq > b->freq; // Min heap based on frequency
        }
    };

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& [data, freq] : freqMap) {
        pq.push(new Node(data, freq));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node(left, right);
        pq.push(parent);
    }
    root = pq.top();
}

void HuffmenTree::generateCodes(Node* node,string currCode,unordered_map<unsigned char,string> &codes){
    if(node==nullptr) return;
    else if (node->left==nullptr&&node->right==nullptr){
        codes[node->data]=currCode;
    }
    else{
        generateCodes(node->left,currCode+"0",codes);
        generateCodes(node->right,currCode+"1",codes);
    }
}

unordered_map<unsigned char,string> HuffmenTree::getCodes(){
    unordered_map<unsigned char , string> codes;
    generateCodes(root,"",codes);
    return codes;
}

