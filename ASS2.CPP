#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }

    Node(int f, Node* l, Node* r) {
        ch = '\0';
        freq = f;
        left = l;
        right = r;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr) {
        codes[root->ch] = code.empty() ? "0" : code;
        return;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

void deleteTree(Node* root) {
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "Input text is empty.\n";
        return 0;
    }

    map<char, int> freq;

    for (char ch : text)
        freq[ch]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto x : freq)
        pq.push(new Node(x.first, x.second));

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node(
            left->freq + right->freq, left, right
        );

        pq.push(parent);
    }

    Node* root = pq.top();

    map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "\nCharacter\tFrequency\tCode\n";

    for (auto x : freq) {
        if (x.first == ' ')
            cout << "[space]";
        else
            cout << x.first;

        cout << "\t\t" << x.second
             << "\t\t" << codes[x.first] << '\n';
    }

    string encoded = "";

    for (char ch : text)
        encoded += codes[ch];

    cout << "\nEncoded text: " << encoded << '\n';
    cout << "Original size: " << text.size() * 8 << " bits\n";
    cout << "Encoded size: " << encoded.size() << " bits\n";
    deleteTree(root);

    return 0;
}