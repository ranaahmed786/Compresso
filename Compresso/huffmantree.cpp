#include "huffmantree.h"
HuffmenTree::HuffmenTree() :root(nullptr) {}
void HuffmenTree::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Public destructor
HuffmenTree::~HuffmenTree() {
    deleteTree(root);
    root = nullptr;
}
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

void HuffmenTree::generateCodes(Node* node, string currCode, unordered_map<unsigned char, string>& codes) {
    if (node == nullptr) return;
    else if (node->left == nullptr && node->right == nullptr) {
        codes[node->data] = currCode;
    }
    else {
        generateCodes(node->left, currCode + "0", codes);
        generateCodes(node->right, currCode + "1", codes);
    }
}
void HuffmenTree::getHuffCodes(unordered_map<unsigned char, string>& codes) {
    generateCodes(root, "", codes);
}
void HuffmenTree::getHuffCanonicalCodes(vector<pair<unsigned char, int>>& codeLenghts, unordered_map<unsigned char, string>& codes) {
    generateCodes(root, "", codes);
    for (const auto& each : codes) {
        codeLenghts.emplace_back(each.first, each.second.length());
    }
    auto Comparator = [](const auto& a, const auto& b) {
        if (a.second != b.second) {
            return a.second < b.second;
        }
        else {
            return a.first < b.first;
        }
    };
    sort(codeLenghts.begin(), codeLenghts.end(), Comparator);
    codes.clear();
    int currentCode = 0;  // Start at 0
    int currentLength = 0; // Track the current code length
    for (const auto& entry : codeLenghts) {
        unsigned char symbol = entry.first;
        int length = entry.second;  // Desired code length
        // Handle length increase
        if (length > currentLength) {
            currentCode <<= (length - currentLength);  // Pad with zeros
            currentLength = length;
        }
        // Convert currentCode to binary string of 'length' bits
        string canonicalCode;
        for (int i = length - 1; i >= 0; i--) {  // MSB to LSB
            canonicalCode.push_back((currentCode & (1 << i)) ? '1' : '0');
        }
        codes[symbol] = canonicalCode;
        currentCode++;  // Prepare for next symbol
    }
}

